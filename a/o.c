char what_a_o_c[] = "@(#) $Id: o.c,v 1.27 1993/02/19 17:27:37 atw Exp $";
#include "f.h"
extern I rsh(A,I,I *);
Z dp(a)A a;{I k,d=0;if(QF(a))R -1;if(a->t<Et)R 0;DO(a->n,if((k=1+dp(a->p[i]))>d)d=k)R d;}
Z C *i2f(t,d,s,n)F *d;I *s;{DO(n,*d++=*s++)R(C*)d;}
Z dr(a,f)A a;I f;{XA;A z,*ap=(A*)a->p,w;if(!an||at!=Et||fsy(a))R ic(a);
 w=*ap; Q(QF(w),9)if(!ar)R ic(w);{XW;I i=an,n,t;C *p;
 if(f){Q(ar>1,7)V0 n=*wd;}else{Q(ar+wr>MAXR,13)mv(ad+ar,wd,wr);}
 for(;--i;){Q(!QA(a=ap[i])||(t=a->t)>Et,9)if(wt!=t&&a->n)if(f&&!n)wt=t;else{Q(wt>Ft||t>Ft,6)wt=Ft;}
  if(wr!=a->r){Q(!f||wr>1||a->r,7)*a->d=1;}Q(cm(wd+f,a->d+f,wr-f),11)if(f)n+=*a->d;}
 W(ga(wt,f?wr:ar+wr,f?n*tr(wr-1,wd+1):an*wn,f?wd:ad))if(f)*z->d=n;p=(C*)z->p;
 DO(an,a=ap[i];p=(*(a->t==wt?tmv:i2f))(wt,p,a->p,a->n))R(I)z;}}
H1(dis){R dr(a,0);}H1(raz){R dr(a,1);}H1(dep){R(I)gi(dp(a));}   Z t,v;
H2(pen){A z,*p;I1{XW;I t=wt,d[9],*ap=a->p,an=a->n,j=an==1?*ap:0,k=*wd,n;C *wp=(C*)w->p;Q(!wr,7)
 DO(an,Q(ap[i]<0,9))
 n=tr(wr-1,wd+1);mv(d+1,wd+1,wr-1);if(j&&k!=(an=k/j)*j)++an;W(j?gv(Et,an):gd(Et,a))*--Y=zr(z),p=(A*)z->p;
 for(;an--;wp+=T(wn),k-=*d)*p++=gc(wt,wr,wn=n*(*d=j?j:*ap++,*d=*d>k?k:*d),d,wp);R ++Y,(I)z;}}
G0(C,lag){C *p=r+T(n);I j=T(v),k=v*-*a;for(;r<p;w+=j)r=tmv(t,r,w,k);}
H2(prt){A z;I0{I d[9],j=*a->p,k=*w->d,r=w->r;if(!r)R j==1?rsh(w,1,a->p):(q=7,0);
 mv(d+2,w->d+1,r-1);if(j>0){d[1]=j,*d=k/j;Q(k!=*d*j,8)R rsh(w,r+1,d);}
 d[1]=-j,*d=k+j+1;Q(*d<0,8)W(ga(t=w->t,r+1,*d*d[1]*(v=tr(r-1,d+2)),d))C2(lag)}}
H1(pct){A z;I i=0,j=0,k=0,n=a->n,*p;I1 W(a->c==1?(A)ic(a):gv(It,n))
 if(n){Q(a->r>1,7)Q(!*a->p,9)for(p=z->p;++i<n;)
  if(a->p[i])p[j++]=i-k,k=i;p[j++]=n-k;z->n=*z->d=j;}R(I)z;}

Z gC(t,r,n,d,p){A z=ga(t,r,n,d);p?tmv(t,z->p,p,n):zer(t,z->p,n);R(I)z;}
Z I raw(r,i)I r,i;{R i<0?(-i>r?r:-i):i>r?0:r-i;}
I rk(f,r,a,w)I f; A r,a,w;{A z,*p;XA;C *pp,*ap,*wp;I wt,wr,wn,*wd,n,t,i,j,k,d[9],rw,ra,
 ri,ir,iw,ia,ii,e=!w&&f==MP(9),h=QP(f)&&!e;Q(!QA(r),9)
 if(!w)mv(d,ad,r),ir=tr(ra,ad),ad+=ra;
 else{wt=w->t,wr=w->r,wd=w->d;wr-=rw=raw(wr,r->p[r->n>1]),
  ri=r->n>2?r->p[2]:9;Q(ri<0,9)if(ri>ra)ri=ra;if(ri>rw)ri=rw;mv(d,ad,ra-=ri);
  ia=tr(ra,ad),mv(d+ra,wd,rw),iw=tr(rw-=ri,wd);Q(cm(ad+=ra,wd+=rw,ri),11)
  ii=tr(ri,ad),ra+=rw+ri,ir=ia*iw*ii,wn=tr(wr,wd+=ri),ad+=ri;
  if(h&&ir>iw&&(f==MP(21)||f==MP(25)||f==MP(26)||f==MP(32)||f==MP(33)))h=0;}
 an=tr(ar,ad);
 if(h){g=0;if(!(r=(A)fa(f,gC(at,ar,an,ad,a->n?a->p:0),w?gC(wt,wr,wn,wd,w->n?w->p:0):0)))R 0;
  mv(d+ra,r->d,j=r->r);if((j+=ra)>MAXR)R q=13,(I)r;n=r->n;t=r->t;
  if(ir<2)R mv(r->d,d,r->r=j),r->n*=ir,(I)r;dc(r);if(g==rsh)R rsh(w?w:a,j,d);
  if(!g){h=0;goto L;}if(at=((A)Y[w?-2:-1])->t,w)wt=((A)Y[-1])->t;
  if(at!=a->t&&!(a=at?ep_cf(1):ci(1)))R 0;if(w&&wt!=w->t&&!(w=wt?ep_cf(2):ci(2)))R 0;
  OF(i,ir,n)W(ga(t,j,i,d))pp=(C*)z->p;}
 else{L:W(ga(Et,ra,ir,d))*--Y=zr(z),p=(A*)z->p;}
 if(!w)for(ap=(C*)a->p;ir--;ap+=Tt(at,an))
  if(h)(*g)(pp,ap,an),pp+=T(n);else a=gc(at,ar,an,ad,ap),*p++=e?a:(A)fa(f,a,0);
 else for(i=0;i<ia;++i)for(j=0;j<iw;++j)for(k=0;k<ii;++k){
  ap=(C*)a->p+Tt(at,(i*ii+k)*an);wp=(C*)w->p+Tt(wt,(j*ii+k)*wn);
  if(h){(*g)(pp,ap,wp,n),pp+=T(n);if(q==1)*--Y=(I)z,err(q,Y[1]),++Y;}
  else *p++=(A)fa(f,gc(at,ar,an,ad,ap),gc(wt,wr,wn,wd,wp));}
 if(h)R(I)z;if(!e)z=(A)dis(r=z),dc(r);R ++Y,(I)z;}

ea(f,a,w)A a,w;{A z,*p;I at=a->t,k=a->r?Tt(at,1):0,wt,j=0;C *ap=(C*)a->p,*wp;
 if(w)if(wt=w->t,wp=(C*)w->p,j=w->r?Tt(wt,1):0,k&&j){Q(a->r!=w->r,7)
  Q(cm(a->d,w->d,a->r),8)}      W(gd(Et,j?w:a))*--Y=zr(z),p=(A*)z->p;
 DO(z->n,if(at<Et||(a=*(A*)ap,QF(a)))a=gc(at,0,1,0,ap);else ic(a);ap+=k;
   if(w){if(wt<Et||(w=*(A*)wp,QF(w)))w=gc(wt,0,1,0,wp);else ic(w);wp+=j;}
   *p++=(A)fa(f,a,w))   R ++Y,(I)z;}

extern F sqrt(),sin(),cos(),tan(),asin(),acos(),atan(),sinh(),cosh(),tanh(),asinh(),acosh(),atanh();
H2(cir){R ds(a,w,17);}F pif(i,x)F x;{switch(i){default:Q(1,9);
CS(0,R sqrt(1-x*x))CS(4,R sqrt(1+x*x))CS(-4,R sqrt(-1+x*x))CS(8,R sqrt(-1-x*x))CS(-8,R -sqrt(-1-x*x))
CS(1,R sin(x))CS(2,R cos(x))CS(3,R tan(x))CS(-1,R asin(x))CS(-2,R cos(x))CS(-3,R atan(x))
CS(5,R sinh(x))CS(6,R cosh(x))CS(7,R tanh(x))CS(-5,R asinh(x))CS(-6,R acosh(x))CS(-7,R atanh(x))}}
