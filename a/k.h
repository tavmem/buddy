#ifndef included_a_k_h
#define included_a_k_h

/* Copyright (c) 1990,1991,1992,1993 Morgan Stanley Group Inc. */

/* @(#) $Id: k.h,v 1.31 1993/04/01 22:31:20 jmb Exp $ */

#include <stdio.h>
#include "u.h"

#define MAXR 9
#define AH 56
#define Inf 1e400
typedef struct a *A;
typedef union{I *i;F *f;C *c;A *a;}P;
struct a{I c,t,r,n,d[MAXR],i,p[1];};
typedef struct _s{struct _s *s;C n[4];}*S;
#define CX_USED
typedef struct _ht{unsigned nb,ni;struct _v *b[1];}*HT;
typedef struct _cx{HT ht;S s;struct _cx *n;}*CX;
typedef struct _v{I a;S s; struct _v *v;CX cx;I t,*l,e,r,o,f,c;
                  void *attr;I z,p,q;A cd;I rff,rfc,rpf,rpc;A scd,i;}*V;
#define HTSIZE       (1<<9)
typedef struct e{I n,f,a[2];}*E;

#ifdef __cplusplus

typedef I (*PFI)();

extern "C" CX Rx,Cx;
extern "C" int install(PFI f,C *s,I t,I n,I t0,I t1,I t2,I t3,I t4,I t5,I t6,I t7);
extern "C" V vi(S s,CX cx);
extern "C" CX cxi(S s);
extern "C" S si(C *n);
extern "C" CX cx*C *s);
extern "C" A ga(I t;I r,I n,I *d);
extern "C" A gs(I t);
extern "C" A gv(I t,I n);
extern "C" A gm(I t,I r,I c);
extern "C" A gi(I i);
extern "C" A gf(F f);
extern "C" A gsv(I x, C *s);
extern "C" A gn(I n);
extern "C" A gd(I t,A a);
extern "C" A gc(I t,I r,I n,I *d,I *p);
extern "C" int gz( void );

extern "C" A grc(A av_, int r_, intc_); 

extern "C" C *qs;
extern "C" C *tst(I t,I *d,I j,I *s,I k,I n);
extern "C" C *tmv(I t,I *d,I *s,I n);
extern "C" C *trp(I t,I d,I s,I n);
extern "C" C *zer(i t,I d,I n);

extern "C" I ic(A a);
extern "C" I dc(A a);
extern "C" A ci(I i);
extern "C" A ep_cf(I i);
extern "C" A ld1(A a);
extern "C" I ev(I z);
extern "C" I ee(E e);
extern "C" A ez(I);
extern "C" I fa(I f,I a,I w);
extern "C" I *tm(I n);
extern "C" void tf ( void );
extern "C" I *ma(I n);
extern "C" void mf(I *);
//extern "C" I tr(I r,I *d);
extern "C" APL,*Y,*X,*K,*J,sq,q(*g)();
extern "C" I Df,Gf,Sf,Tf,Xf,Ef;
extern "C" A nl;
extern "C" I aset( V v_, A d_, A i_, A p_ );
extern "C" A af4( A, A, A, A, A, V );
extern "C" A gt( V v) );
extern "C" A un( A *p );

#else
extern CX Rx,Cx;
extern V vi();
extern CX cxi(), cx();
extern C *qs,*tst(),*tmv(),*trp(),*zer();
extern A ci(),ep_cf(),ga(),gv(),gs(),gc(),dg(),gi(),gf(),gm(),ld1(),un();
extern I gsv(),ev(),ee(),fa(),APL,*Y,*X,*K,*J,sq,q,(*g)(),Itm(),*ma(),nl;    // *k,tr()
extern I Df,Gf,Sf,Tf,Xf,Ef;
#endif

#define T(x) ((x)<<(t+2&3))
#define Tt(t,x) ((x)<<(t+2&3))
#define Q(x,n) {if(x)R q=n,0;}
#define W(x) {z=(A)(x);}
#define It 0L
#define Ft 1L
#define Ct 2L
#define Et 4L
#define Xt 8L
#define M 7
#define U(a) ((I)(a)<<3)
#define QA(a) (0==((I)(a)&M))
#define QV(a) (1==((I)(a)&M))
#define QS(a) (2==((I)(a)&M))
#define QE(a) (3==((I)(a)&M))
#define QN(a) (4==((I)(a)&M))
#define QL(a) (5==((I)(a)&M))
#define QP(a) (6==((I)(a)&M))
#define QX(a) (7==((I)(a)&M))
#define MV(a) (1|(I)(a))
#define MS(a) (2|(I)(a))
#define ME(a) (3|(I)(a))
#define MN(a) (4|(I)(a))
#define ML(a) (5|(I)(a))
#define MP(a) (6|(I)(a))
#define MX(a) (7|(I)(a))
#define XS(a) ((S)((I)(a)&~M))
#define XV(a) ((V)((I)(a)&~M))
#define XE(a) ((E)((I)(a)&~M))

#endif
