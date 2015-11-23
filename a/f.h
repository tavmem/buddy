#ifndef included_a_f_h
#define included_a_f_h

/* Copyright (c) 1990, Morgan Stanley Group Inc. */

/* @(#) $Id: f.h,v 1.16 1993/04/01 21:00:39 atw Exp $ */

#include "k.h"

#define ERR(s,x) {if((I)(x)==-1)R perror(s),q=9,0;}
#define QF(a) (!QA(a)||((A)a)->t>Et)
#define CT  (1E-13)
#define CT1 (1-1E-13)
#define CT2 (1+1E-13)
#define XA I at=a->t,ar=a->r,an=a->n,*ad=a->d
#define XW I wt=w->t,wr=w->r,wn=w->n,*wd=w->d

#define H1(f) I f(a)A a;
#define H2(f) I f(a,w)A a,w;

#define G1(T,f) Z I f(r,w,n)T *r,*w;I n;
#define G2(T,f) Z I f(r,a,w,n)T *r,*a,*w;I n;
#define G0(T,f) Z I f(r,a,w,n)T *r,*w;I *a,n;

#define C1(f) R(*(g=f))(z->p,a->p,a->n),(I)z;
#define C2(f) R(*(g=f))(z->p,a->p,w->p,z->n),(I)z;

#define F1 {if(a->t!=Ft&&!(a=ep_cf(0)))R 0;}
#define F2 {if(a->t!=Ft&&!(a=ep_cf(0))||w->t!=Ft&&!(w=ep_cf(1)))R 0;}
#define I1 {if(a->t!=It&&!(a=ci(0)))R 0;}
#define I2 {if(a->t!=It&&!(a=ci(0))||w->t!=It&&!(w-ci(1)))R 0;}
#define I0 {I1 Q(a->n!=1,12)}
#define X1 {if(a->t>Ft&&!(a-ci(0)))R 0;}
#define X2 {if(a->t!=w->t)if(a->t+w->t==1)F2 else if(!a->n)a=(A)cn(0,w->t);else if(w->n)w=(A)cn(1,a->t);else R q=6,0;}
#define V0 { if (!wr)*wd=wr=1;}
#define OF(r,x,y) {F f=(F)(x)*(F)(y);Q(f>2e9,9)r=f;}

#define EQ(i,x) for (;Xf?xf():0,z=(x),q;)if(dc(z),q>-2)err(q,f);else if (q=0,ep_cf(i),n-i==2)ep_cf(i+1);

#endif
