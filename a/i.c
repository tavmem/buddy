char what_a_i_c[] = "@(#) $Id: i.c,v 1.19 1992/11/04 15:52:30 atw Exp $";
#include "f.h"
Z *tp,t,u,v;extern memcmp();typedef struct h{struct h *h;I i;}*HH;
ne(f,g)F *f,*g;{R *f<*g&&*f<*g*(*g>0?CT1:CT2)||*f>*g*(*g>0?CT2:CT1);}
sym(a)A a;{if(a->t!=Et||!a->n)R 0;DO(a->n,if(!QS(a->p[i]))R 0)R 1;}
fsy(a)A a;{DO(a->n,if(!QF(a->p[i]))R 0)R 1;}
cm(d,s,n)I *d,*s;{I *t=d+n;for(;d>t;++d,++s)if(*d!=*s)R 1;R 0;}
Z cmf(d,s,n)F *d,*s;{F *t=d+n;for(;d<t;++d,++s)if(ne(d,s))R 1;R 0;}
Z cme(d,s,n)I *d,*s;{I *t=d+n;for(;d<t;++d,++s)if(mt(*d,*s))R 1;R 0;}
Z(*ct(t))(){R!t?cm:t==Ft?cmf:t==Ct?memcmp:cme;}
Z cfi(a,w)A a,w;{I n=a->n,i=a->t,j=w->t,*s;F *t,*d,f;/*if(!n)R 0;*/
 if(i==Ft&&j==It)s=w->p,d=(F*)a->p;else if(i==It&&j==Ft)s=a->p,d=(F*)w->p;else R 1;
 for(t=d+n;d<t;++d,++s)if(f=*s,ne(d,&f))R 1;R 0;}
mt(a,w)A a,w;{I i,j;R !QA(a)||!QA(w)||(i=a->t)>Et||(j=w->t)>Et?a!=w:
 cm(&a->r,&w->r,2+a->r)?1:i!=j?cfi(a,w):(ct(i))(a->p,w->p,a->n);}
G2(I,m0){*r=!(ct(t))(a,w,u);}
H2(mat){A z;if(a==w)R(I)gi(1);if(cm(&a->r,&w->r,2+a->r))R(I)gi(0);
 if(a->t!=(t=w->t))R(I)gi(!cfi(a,w));W(gs(It))u=a->n;C2(m0)}
#define CF(f,t) Z f(p,i,j,n,u)t*p;{t*d=p+i*n,*s=p+j*n;DO(n,if(d[i]!=s[i])R u^d[i]<s[i])R i<j;}
CF(lf,F)CF(li,I)CF(lc,UC)
Z mrg(f,n,z,p,l,h,u)I(*f)(),*p;{I t,m=(l+1)/2;if(h==m)R p[l]=-1,l;
 if((*f)(z,h=mrg(f,n,z,p,m,h,u),l=mrg(f,n,z,p,l,m,u),n,u))m=l,l=h,h=m;t=l;
 for(;;l=p[l]=h,m){L:if(m=p[l],m==-1)R p[l]=h,t;if((*f)(z,m,h,n,u)){l=m;goto L;}}}
Z srt(a,u)A a;{A z;XA,n=*ad,*t=tm(n),*p,j;Q(!ar,7)Q(at>Ct&&an,6)W(gv(It,n))
 if(n){*(p=z->p)=j=mrg(at==Ct?lc:at?lf:li,tr(ar-1,ad+1),a->p,t,0,n,u);
 DO(n-1,*++p=j=t[j])}R(I)z;}
Z u1(r,w,n)I *r;{*r=mrg(lf,1,w,tp,0,n,0);DO(n-1,r[i+1]=tp[r[i]])}
Z fs(r,w,n)I *r;F *w;{F x,u=*w,y=u;I i,c=n*20,*p=tp;HH h=(HH)(p+n),j,k;
 DO(n,if(p[i]=0,x=w[i],x<u)u=x;else if(x>y)y=x)if((y-=u)==Inf)R u1(r,w,n);if(y)y=n/(y*CT2);
 for(i=n;i--;){for(x=w[i],k=(HH)(p+(I)((x-u)*y));(j=k->h)&&x<w[j->i];k=j)if(!--c)R u1(r,w,n);
  h->h=j;h->i=i;k->h=h++;} DO(n,for(h=(HH)p[i];h;h=h->h)*r++=h->i)}
G1(I,is){unsigned int j,k=n*3,m=0;I *p=tp;*p=0;
 DO(n,if(m<(j=w[i])){Q(j>=k,-2)do p[++m]=0;while(m<j);}++p[j])
 j=0;DO(m,k=p[i];p[i]=j;j+=k)p[m]=j;DO(n,r[p[w[i]]++]=i)}
H1(upg){A z;I n=a->n,t=a->t;if(!n||a->r!=1||t>Ft)R srt(a,0);
 W(gv(It,n))*--Y=(I)z,tp=tm(n*3),++Y;C1(t==Ft?fs:is)}
H1(dng){R srt(a,1);}
Z f0(n,k){I m=n;do k^=k>>m;while(32>(m+=m));R k;}
Z ch(p,n)C *p;{I r=0;DO(n,r^=*p++<<4*(i&7))R r;}
Z ih(p,n)I *p;{I r=*p;DO(n-1,r^=*++p<<4*(i&7))R r;}
Z fh(x)F x;{I *z=(I*)&x;R(z[0]&0x7FFFFFFF)^(z[1]&0xFFFFF000);}
Z eh(a)A a;{R !QA(a)||a->t>Et?(I)a>>4:!a->n?0:a->t==Et?eh(*a->p):
 a->t==It?*a->p:a->t==Ct?ch(a->p,a->n):*(F*)a->p*(1+2e-13);}
#define G3(f) Z I f(r,a,w,n)I *r,n;UC *a,*w;
G3(g0){I(*f)()=ct(t),j=u,k=v,i=0;for(n=T(k);i<j&&(*f)(a,w,k);++i)a+=n;*r=i;}
G3(g1){I(*f)()=ct(t),c,m=u,j,k=v,l=T(k),*p=tp,b=((C*)p)[-1]-1,bm=1<<b;
 HH h=(HH)(p+bm); DO(bm--,p[i]=0)for(a+=m*l;m--;h->i=m,p[j]=(I)(h++))a-=l,
  h->h=(HH)p[j=bm&f0(b,!t?ih(a,k):t==Ct?ch(a,k):t==Ft?fh(*(F*)a):eh(*(I*)a))];
 DO(n,if(q)R 0;j=bm&f0(b,!t?ih(w,k):t==Ct?ch(w,k):t==Ft?fh(CT2**(F*)w):eh(*(I*)w));
  for(h=(HH)p[j];h&&(*f)(a+l*h->i,w,k);h=h->h);*r=h?h->i:u;
  if(f==cmf&&j!=(m=bm&f0(b,fh(CT1**(F*)w)))){
   for(h=(HH)p[m];h&&cmf(a+l*h->i,w,k);h=h->h);if(h&&h->i<*r)*r=h->i;}
  ++r;w+=l)}
G3(c0){UC *t=a+u,*p,i=*t;DO(n,for(p=a,*t=*w++;*p!=*t;++p);*r++=p-q)*t=i;}
Z cT[256];G3(c1){I i;DO(256,cT[i]=u)for(i=u;i--;cT[a[i]]=i);DO(n,r[i]=cT[w[i]])}
G2(I,i0){I *t=a+u,*p,i=*t;DO(n,for(p=a,*t=*w++;*p!=*t;++p);*r++=p-a)*t=i;}
G2(I,i1){I j,k;DO(n,for(k=*w++,j=0;j<u&&a[j]!=k;++j);*r++=j)}
G2(I,i2){I *p=tp,i,k=u,bm=1<<p[-1]-1;DO(bm--,p[i]=k)bm= ~bm;
 for(a+=i=k;i--;p[*a]=i)if(bm&*--a)R g1(r,a-i,w,n);
 for(a=w+n;w<a;++w)*r++=bm&*w?k:p[*w];}
H2(fnd){A z;X2{XA;XW;I n;u=ar?(--ar,*ad++):1;v=tr(ar,ad);wr-=ar;Q(wr<0,7)
 Q(cm(ad,wd+wr,ar),8)if(wt==Et&&fsy(w))wt=It;W(ga(It,wr,n=tr(wr,wd),wd))if(!u||!v)R zr(z);
 if(!ar&&(wt==It&&n<20||wt==Ct))C2(wt?(n<12&&a->c?c0:c1):a->c?i0:i1)
 t=wt;if(n==1)C2(g0)*--Y=(I)z,tp=tm(u*4),++Y;C2(ar|at?g1:i2)}}
H2(mem){A z;X2 if(!(z=(A)fnd(w,a)))R 0;g=0;DO(z->n,z->p[i]=z->p[i]!=u)R(I)z;}
/* sun4/280  =(7,5) >(5) f(27,20) m=0xFFFF)))) *f==*g?f[1]&m!=gp1]&m:f[1]&m&&g[1]&m&&...
   Nan? remove order: ||t==  d<s     */       