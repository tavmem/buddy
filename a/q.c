/*
      $cd /u/orth/domino

      cc -c domino.c -o domino.o

      $load domino_a

      $load domino_s

      'domino.o' _dyld ('_dmd'  ;'dmd'  ;0 0 0;
                        '_mmd'  ;'mmd'  ;  0 0)

*/

#include <stdio.h>
#include <math.h>
#include <strings.h>
#include "k.h"

extern I  q;
extern C *qs;

#define Ma(i,j)         *((F *)a->p+n*i+j)
#define Mb(t,i,j)       *((t *)b->p+p*i+j)
#define Mh(i,j)         *((F *)h->p+2*i+j)
#define Mz(i,j)         *((F *)z->p+p*i+j)

#define vector(t,a,k)   *((t *)a->p+k)
#define Vc(k)           *((F *)c->p+k)
#define Vfactor(k)      *((F *)factor->p+k)
#define Vtvec(k)        *((F *)tvec->p+k)

#define index(n,k)      *((I *)n->p+k)
#define Ipp(k)          *((I *)pp->p+k)
#define Ipq(k)          *((I *)pq->p+k)

#define DOMAIN_ERROR 9
#define LENGTH_ERROR 8
#define RANK_ERROR   7

/*
For text errors indicating where an error message originates from, use:

#define DOMAIN_ERROR  -1
#define LENGTH_ERROR  -1
#define RANK_ERROR    -1
*/

A        dmd(), mmd();
static A ls_c();

/*
 ------------ The dyadic case.
*/

A dmd(b,a)
     A b, a;
{
  int result_rank;
  int m, n, p;
  A   z;

  if ( (It != a->t && Ft != a->t) || (It !=b->t && Ft != b->t) ) {
    qs = "error no. 1";
    q = DOMAIN_ERROR;
    return(0);
  }

  if (2 < a->r || 2 < b->r ) {
    qs = "error no. 2";
    q = RANK_ERROR;
    return(0);
  }

  if ( 0 == a->r ) result_rank = 0;
  else result_rank = a->r - 1;
  if ( 0 != b->r ) result_rank += b->r - 1;

  if (2 == a->r ) {
    m = a->d[0]; n= a->d[1];
  }
  else {
    n = 1;
    if ( 1 == a->r ) {
      m = a->d[0];
    }
    else {
      m = 1;
    }
  }

  if ( m < n ) {
    qs = "error no. 3";
    q = DOMAIN_ERROR;
    return(0);
  }

  if ( 2 == b->r ) {
    if ( m != b->d[0] ) {
      qs = "error no. 4";
      q = LENGTH_ERROR;
      return(0);
    }
    p = b->d[1];
  }
  else {
    p = 1;
    if ( ( 1 == b->r && m != b->d[0] ) || ( 0 == b->r && m != 1 ) ) {
      qs = "error no. 5";
      q = LENGTH_ERROR;
      return(0);
    }
  }

  z = ls_c(a,b,m,n,p,0);

  if ( 0 == z ) return(0);

  z->r = result_rank;
  if ( 1 <= result_rank ) z->d[0] = n;
  if ( 2 == result_rank ) z->d[1] = p;

  return(z);
}

/*
 ------------ The monadic case.
*/

A mmd( a )
     A a;
{
  int result_rank;
  int m, n, p;
  A   z;

  if ( It != a->t && Ft != a->t ) {
    qs = "error no. 6";
    q = DOMAIN_ERROR;
    return(0);
  }

  if (2 < a->r ) {
    qs = "error no. 7";
    q = RANK_ERROR;
    return(0);
  }

  result_rank = a->r;

  if ( 2 == a->r ) {
    m = a->d[0];
    n = a->d[1];
  }
  else if ( 1 == a->r ) {
    m = a->d[0];
    n = 1;
  }
  else {
    m = 1;
    n = 1;
  }

  if ( m < n ) {
    qs = "error no. 8";
    q = DOMAIN_ERROR;
    return(0);
  }

  p = m;

  z = ls_c(a,0,m,n,p,1);

  if ( 0 == z ) return(0);

  z->r = result_rank;
  if ( 1 <= result_rank ) z->d[0] = n;
  if ( 2 == result_rank ) z->d[1] = p;

  return(z);
}

/* ------------ The least squares computation.
  Here's the beef.  This program is an amalgamation of two of Mike Jenkin's
  models for Domino:  one is the primitive that appeared in APLSV and VSAPL,
  while the other is for the generalized inverse version
  that appeared in the original APL2.  This program reflect the current state
  of Domino in APL2 (as of 7/12/91), except that the complex arithmetic sections
  are missing.
*/

static A ls_c(a0,b,m,n,p,monadic)
     A   a0, b;
     int m, n, p, monadic;
/*
  m,n,p     :  scalars set by the driver
  a0        :  the right argument, a matrix of shape m,n
  b         :  the left argument in the dyadic case, a matrix of shape m,p
  z         :  the result, a matrix of shape n,p
  monadic   :  a flag used to signal generation fo the identity matrix
*/
{
  I    i,j, i0, j0, d[MAXR], l, pi, pj;
  F    eps, mv, mmv, s, sa, st, t, tolerance, t0, t1, t2, t3, t4, t5, v;
  A    a, c, factor, h, pp, pq, tvec, z;
/*
  Make a copy of a0 because it will be modified.  Remember that a0 can be
  either integer of real, and always copy to real.
*/
  a = ga(Ft, a0->r, a0->n, a0->d );

  switch( a0->t ) {
  case It:
    for ( i = 0; i < a0->n; ++i )
      vector(F,a,i) = vector(I,a0,i);
    break;
  case Ft:
    for ( i = 0 ; i < a0->n ; ++i )
      vector(F,a,i) = vector(F,a0,i);
    break;
  };
/*
  Initialize the temps and the result.
*/
  d[0] = m;
  pq = ga(It, 1, d[0], d );
  for ( i = 0 ; i < m ; ++i ) Ipq(i) = i;

  c = ga(Ft, 1, d[0], d );

  d[0] = n;
  pp = ga(It, 1, d[0], d );
  for ( i = 0 ; i < n ; ++i ) Ipp(i) = i;

  factor = ga(Ft, 1, d[0], d );

  d[1] = 2;
  h = ga(Ft, 2, d[0]*d[1], d );

  d[1] = p;
  z = ga(Ft, 2, d[0]*d[1], d );

  if ( n <= m ) d[0] = m;
  tvec = ga(Ft, 1, d[0], d );
/*
  tolerance : APL uses 1e-16. Jenkin's original paper uses 16e-13.
*/
  mmv=0.;
  for ( i = 0 ; i < m ; ++i ) {
    t0 = 0.0;
    for ( j = 0 ; j < n ; ++j ) {
      sa = Ma(i,j);
      if ( 0 > sa ) sa = - sa;
      t0 = t0 + sa;
    }
    if ( mmv < t0 ) mmv = t0;
  }
  tolerance = 1e-16;
  eps = tolerance*mmv;
/*
   Here is the scaling from the APLSV/VSAPL model:
*/
  for ( i = 0 ; i < m ; ++i ) {
    Vtvec(i)=0.0;
    for ( j = 0 ; j < n ; ++j ) {
      t1 = Ma(i,j);
      if ( 0 > t1 ) t1 = -t1;
      if ( Vtvec(i)<t1 ) Vtvec(i) = t1;
    }
  }

  for ( j = 0 ; j < n ; ++j ) {
    Vfactor(j) = 0.0;
    for ( i = 0 ; i < m ; ++i ) {
      sa = Ma(i,j);
      if ( 0 > sa ) sa = -sa;
      t2 = sa / Vtvec(i);
      if ( Vfactor(j)<t2 ) Vfactor(j) = t2;
    }
    sa = 1.0 / Vfactor(j);
    Vfactor(j) = sa;
  }

  for ( i = 0 ; i < m ; ++i ) {
    for ( j = 0 ; j < n ; ++j ) {
      Ma(i,j) = Ma(i,j)*Vfactor(j);
    }
  }
/*
  Apply the Householder transformations to zero out the matrix a below
  the diagonal.

  This is the BIG loop.
*/
  for ( j = 0 ; j < n ; ++j ) {

    mmv = 0.0;
    pj = 0;
    for ( j0 = j ; j0 < n ; ++j0 ) {
      mv = 0.0; 
      for ( i0 = j ; i0 < m; ++i0 ) {
        t3 = Ma(i0,j0);
        if ( 0 > t3 ) t3 = -t3;
        if ( mv < t3 ) {
          mv = t3;
        }
      }

      if ( mmv < mv ) {
        mmv = mv;
        pj = j0;
      }
    }
    if( eps >= mmv ) {
      qs = "error no. 9";
      q = DOMAIN_ERROR;        /* There is no rank deficient case. */
      dc(a); dc(c); dc(factor); dc(h); dc(pp); dc(pq); dc(tvec); dc(z);
      return(0);
    }
    if ( j != pj ) {
      i = Ipp(pj);
      Ipp(pj) = Ipp(j);
      Ipp(j) = i;

      for ( i = 0 ; i < m ; ++i ) {
        s        = Ma(i,pj);
        Ma(i,pj) = Ma(i,j);
        Ma(i,j)  = s;
      }
    }
/*
  The followint row interchange is from the APLSV/VSAPL model.
*/
    t = 0.0;
    pi = 0;
    for ( i0 = j; i0 < m ; ++i0 ) {
      t4 = Ma(i0,j);
      if ( 0 > t4 ) t4 = -t4;
      if ( t < t4 ) {
        t = t4;
        pi = i0;
      }
    }
    if ( j != pi ) {

      Ipq(j) = Ipq(pi);

      for ( j0 = j ; j < n ; ++j0 ) {
        s         = Ma(j,j0);
        Ma(j,j0)  = Ma(pi,j0);
        Ma(pi,j0) = s;
      }
    }
/*
  Now do the i-th transformation (in place).
*/
    t = 0.0;
    for ( i0 = j ; i0 < m ; ++i0 ) {
      t5 = Ma(i0,j);
      if ( 0 > t5 ) t5 = -t5;
    }
    v = 0.0;
    for ( i0 = j ; i0 < m ; ++i0 ) {
      s = Ma(i0,j) / t;
      v = v + s*s;
    }
    v = t*sqrt(v);
    if ( Ma(j,j) < 0 ) v = -v;
/*
  Save the essential values and ajust the kiagonal element.
*/
    Mh(j,0) = v;
    Mh(j,1) = Ma(j,j);
    Ma(j,j) = -v;
/*
  Apply the transformation (in place).
*/
    for ( j0 = j + 1 ; j0 < n ; ++j0 ) {

      Vtvec(j0) = Ma(j,j0);

      Ma(j,j0) = Mh(j,1) * Ma(j,j0);

      for ( i0 = j + 1 ; i0 < m ; ++i0 ) {
        Ma(j,j0) = Ma(j,j0) + Ma(i0,j) * Ma(i0,j0);
      }
    }
    s = Mh(j,0) + Mh(j,1);
    for ( j0 = j + 1 ; j0 < n ; ++j0 ) {
      t = (Vtvec(j0) - Ma(j,j0)) / s;
      for ( i0 = j + 1 ; i0 < m ; ++i0 ){
        Ma(i0,j0) = Ma(i0,j0) - Ma(i0,j) * t;
      }
    }
  }
/*
  Build the solutions.

  First apply the same transformations to the righthand side oas were applied
  to a, one column at a time.

  The formation of the victor c shows why we process each column of the righthand
  side separately, for otherwise in he monadic casse we would have to form very
  large identity matrices when the argument matrix had many rows.
  As with the argument a, the argument b might be integer and we always copy
  to a real vector c.  The vector c should be created at the top of the loop in C.
*/
  for (i = 0 ; i < n ; ++i )
    for ( j = 0; j < p ; ++j ) Mz(i,j) = 0.0;
/*
  The next loop is the outer loop for the solution builder.
*/
  for ( l = 0 ; l < p ; ++l ) {

    if ( monadic ) {
      for ( i = 0 ; i < m ; ++i ) Vc(i) = 0.0;
      Vc(l) = 1.0;
    }
    else {
      switch ( b->t ) {
      case It:
        for ( i = 0 ; i < m ; ++i ) Vc(i) = Mb(I,i,l);
        break;
      case Ft:
        for ( i = 0 ; i < m ; ++i ) Vc(i) = Mb(F,i,l);
        break;
      }
    }
 
    for ( j = 0 ; j < n ; ++j ) {

      if ( j != Ipq(j) ) {
        s          = Vc(j);
        Vc(j)      = Vc(Ipq(j));
        Vc(Ipq(j)) = s;
      }
/*
  Apply the transformation (in place).
*/
      st = Vc(j);
      Vc(j) = Mh(j,1) * Vc(j);
      for ( i0 = j + 1 ; i0 < m ; ++i0 ) {
        Vc(j) = Vc(j) + Ma(i0,j) * Vc(i0);
      };
      Vc(j) = -Vc(j) / Mh(j,0);

      s = Mh(j,0) + Mh(j,1);

      t = (st-Vc(j)) / s;

      for ( i0 = j+ 1 ; i0 < m ; ++i0 ) {
        Vc(i0) = Vc(i0) = Ma(i0,j) * t;
      }
    }
/*
  Backsolve the n-by-n triangular system.
*/
    for ( j = n - 1 ; 0 <= j ; --j ) {
      s = 0.0;
      for ( j0 = j ; j0 < n ; ++j0 ) {
        s = s + Ma(j,j0) * Mz(Ipp(j0),l);
      }
      Mz(Ipp(j),l) = (Vc(j)-s) / Ma(j,j);
    }
  }
/*
  Adjust for APLSV/VSAPL scaling.
*/
  for ( i = 0; i < n ; ++i )
    for ( j = 0 ; j < p ; ++j ) {
      Mz(i,j) = Ma(i,j) * Vfactor(i);
    }
/*
  Remove the temps.
*/
  dc(a); dc(c); dc(factor); dc(h); dc(pp); dc(pq); dc(tvec);

  return(z);
}
