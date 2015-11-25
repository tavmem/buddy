char what_a_n_c[] = "@(#) $Id: n.c,v 1.36 1993/04/24 00:56:56 maus Exp $";
#include "f.h"
#include "x.h"
#include <stdio.h>
#include <malloc.h>
#include <sys/time.h>
#include <sys/resource.h>
typedef struct{I u,s,e;}B;Z B t0;Z A ta;Z tn,td[2]={0,4},**tp,tj;Z e0;
Z tr(t)struct timeval t;{R t.tv_sec*1000+10*(t.tv_usec/10000);}
Z B ti(){Z struct rusage r;Z struct timeval tp;Z struct timezone tzp;B t;
 gettimeofday(&tp,&tzp),getrusage(RUSAGE_SELF,&r);
 R t.u=tr(r.ru_utime),t.s=tr(r.ru_stime),t.e=tr(tp)-e0,t;}
te(){e0=ti().e;}
Z B tz(x,y)B x,y;{B t;R t.u=x.u-y.u,t.s=x.s-y.s,t.e=x.e-y.e,t;}
Z tw(z,t)B *z,t;{z->u+=t.u,z->s+=t.s,z->e+=t.e;}
t2(n,i){B t;I*p=((A)ta->p[1])->p;if(i)++p[4*n];t0=tz(t=ti(),t0);
 R p+=4*tn+1,*p+=t0.u,p[1]+=t0.s,p[2]+=t0.e,t0=t,i=tn,tn=n,i;}
Z gt(t)B t;{A z=gv(It,3);R(*(B*)z->p)=t,(I)z;}
Z H1(t1){I n=a->n;A z;if(tj){DO(tj,if(tp[i])*tp[i]=0)dc(ta),ta=0;}
 if(tj=n){extern V sv();V v;*td=++n,z=(A)zr(ga(It,2,n*4+tj,td));
  tp=(I**)z->p+(z->n=n*4);ta=gv(Et,2),*ta->p=ic(a),ta->p[1]=(I)z;
  DO(tj,if(v=sv(Cx,XS(a->p[i])),z=(A)(v->e?v->e:v->a))*(tp[i]=z->p+z->n)=i+1)}
 R t0=ti(),ic(a);}

#define N(f) Z f(e)E e;
Z ni(a)A a;{I i;for(*--Y=(I)a;a->n!=1||a->t&&!(a=ci(0));a=(A)*Y)err(9,MN(*K));R i=*a->p,dc(*Y++),i;}
N(xpr){I z=nl,n=e->n;++K;DO(n,*K=010i;dc(z);z=ev(e->a[i]))R --K,z;}
N(xif){I z;*++K=2;z=ni(ev(*e->a))?ev(e->a[1]):e->n>2?(*K=1,ev(e->a[2])):nl;R --K,z;}
N(xwh){I z;*++K=3;for(*--Y=z=nl;ni(ev(*e->a));*Y=ev(e->a[1]),dc(z),z=*Y);R --K,++Y,z;}
Z set(a,i)A *a;{if((*a)->c!=1||(*a)->t!=It||(*a)->n)dc(*a),*a=gi(i);else *(*a)->p=i;}
N(xdo){I v=*e->a,i,z=nl,f=1;A *a;if(e->n==1)R pev(v);
 {E e;if(QE(v)&&(e=XE(v),e->f==MP(15)&&e->n==1))v=*e->a,f=0;}
 i=ni(ev(v));*++K=4;if(QE(v)&&MN(0)==XE(v)->f)v=*XE(v)->a;
 if(a=(A*)(QV(v)?&XV(v)->a:QL(v)?X+U(v):0))set(a,f?0:i-1);
 for(v=0;v<i;)if(dc(z),z=ev(e->a[1]),++v,a)set(a,f?v:i-1-v);if(!f)set(a,i);R --K,z;}
Z H2(in){I n=a->r?*a->d:1;for(*--Y=ic(w),*--Y=(I)a;a=(A)fnd(*Y,Y[1]),q;)err(q,MP(19));
 dc(*Y++),dc(*Y++),dc(a);DO(a->n,if(n>a->p[i])R 1)R 0;}
N(xca){I *p,z;*++K=5,z=ev(*e->a),e=XE(e->a[1]),p=e->a;++K;
 DO(e->n/2,*K=-1-2*i;if(in(ev(*p++),z))break;++p)R --*K,dc(z),z=p<e->a+e->n?ev(*p):nl,K-=2,z;}
N(xti){B t;A a;if(!e->n)R ta?(t2(0,0),ic(ta)):gt(ti());a=(A)*e->a;
R QA(a)&&sym(a)||nl==(I)a?t1(a):(t=ti(),dc(ev(a)),gt(tz(ti(),t)));}
N(xli){A z;I n=e->n;W(gv(Et,n));*--Y=zr(z);for(;n--;)z->p[n]=ev(e->a[n]);R ++Y,(I)z;}

Z mx(o,f,g){A z;I d[3];*d=MN(o),d[1]=f,d[2]=g;R(I)ga(Xt,g?3:2,0L,d);}
N(rk){R mx(8,ev(*e->a),ev(e->a[1]));}
N(ea){A a=(A)ev(*e->a);if(QF(a))R mx(9,a,0L);
 R a->n==1&&a->t==Et&&QF(*a->p)&&QS(*a->p)?(dc(a),ic(*a->p)):(I)a;}
extern xis();I(*PN[])()={xis,xpr,xif,xwh,xdo,xca,xti,xli,rk,ea};
#define XI 10000
C *xs[XI]={"[]"},*xd[XI]={"??"};I xn[XI];
Z I(*xf[XI])(),xt[XI],xp[XI],xi=0,y[8];
Z C *argtypes[]={"any","int","float","char","any","int","float","string",
"anyscalar","scalar int","floatsc","charsc","any","int","float","char"};

Z C *cxtdotname(v) V v;{ C *res, *cxt=v->cx->s->n, *name=v->s->n;
  res=malloc(2+strlen(cxt)+strlen(name));sprintf(res,"%s.%s",cxt,name);R res;}

Z C *defaultdoc(s,t,n,y)C *s;I *y;{ C *z=malloc(128+strlen(s));
  strcpy(z,s);
  if(n) {
    strcat(z,"{");
    while(n--){strcat(z,argtypes[*y++]);strcat(z,";");}
    z[strlen(z)-1]='}';
  } else strcat(z,"{}");
  strcat(z," returns ");strcat(z,(8==t)?"null":argtypes[t]);R z;
}

Z C *installdoc(s,d)C *s,*d;{C *z=malloc(2+strlen(s)+strlen(d));
 strcpy(z,s);strcat(z,"\n");strcat(z,d);R z;}

xfs(){C **s=xs;for(;*++s;)if(**s=='_'&(*s)[1]!='_')H("%s ",*s);NL;}
x_fs(){C **s=xs;for(;*++s;)if(**s==')'&&(*s)[1]=='_')H("$s ",*s);NL;}

xinstall(f,s,t,n,y,d)I(*f)(),*y;C *s,*d;{I p=0,i;V v;C *nm=0;
 if(xi==XI-1)R H("too many installs\n"),0;
 xf[++xi]=f,xt[xi]=t,xn[xi]=n;if(*y==-1)R xp[xi]=-1;
 if(n<0)n= -n;if(n>8)R --xi,H("too many arguments for %s\n",s),0;
 for(i=n;i-->0;)p|=y[i]<<4*i;xp[xi]=p;
 if(*s!='_'){extern V sv();v=sv(Cx,si(s)),v->a=MX(xi),v->t=5,nm=cxtdotname(v);}
 if (d==(C *)0) d=defaultdoc(nm?nm:s,t,n,y); else d=installdoc(nm?nm:s,d);
 xs[xi]=(nm?nm:s);xd[xi]=d?d:""; R 1;}

install(f,s,t,n,t0,t1,t2,t3,t4,t5,t6,t7)I(*f)();C *s;{
 y[0]=t0,y[1]=t1,y[2]=t2,y[3]=t3,y[4]=t4,y[5]=t5,y[6]=t6,y[7]=t7;
 xinstall(f,s,t,n,y,(C *)0);}
#define RA(x) R z=(*f)x,!z&&q?0:t==A_?(z?z:nl):t==CP?gsv(0,z):t==IV?(I)gi(z):nl
PX(i,n){I t=xt[i],p=xp[i],(*f)()=xf[i],z;A a;
 Q(n!=xn[i]&&xn[i]>=0,5);if(p==-1)RA((Y,n));for(i=0;i<n;++i){
  switch(a=(A)Y[i],z=p*15,p>>=4,z&3){
   CS(CA,Q(Ct!=a->t,6))
   CS(IA,if(It!=a->t&&!(a=ci(i)))R 0)
   CS(FA,if(Ft!=a->t&&!(a=ep_cf(i)))R 0)}
  switch(z&12){case U_:a=(A)un(Y+i);
   CS(A_,y[i]=(I)a)
   CS(P_,y[i]=(I)a->p)
   CS(V_,Q(a->n!=1,8)y[i]=*a->p)}}
  switch(n){
  CS(0,RA(()))
  CS(1,RA((y[0])))
  CS(2,RA((y[0],y[1])))
  CS(3,RA((y[0],y[1],y[2])))
  CS(4,RA((y[0],y[1],y[2],y[3])))
  CS(5,RA((y[0],y[1],y[2],y[3],y[4])))
  CS(6,RA((y[0],y[1],y[2],y[3],y[4],y[5])))
  CS(7,RA((y[0],y[1],y[2],y[3],y[4],y[5],y[6])))
  CS(8,RA((y[0],y[1],y[2],y[3],y[4],y[5],y[6],y[7])))
}}
