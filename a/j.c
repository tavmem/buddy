char what_a_j_c[] ="@(#) #Id: j.c,v 1.13 1992/11/03 17:08:06 atw Exp $";
#include "f.h"
typedef struct {I n,*j,s;}HH;typedef(*G)();Z r,c[9],d[10],t,u,v,e;
#define J(f,t,x) Z f(p,h)HH *h;{t*s=(t*)h->s;I*j=h->j;DO(h->n,x)h->s=(I)s;}
#define K(t,u,v,x,y)    J(u,t,*s++=*(t*)p;p+=(I)j) J(v,t,*s++=*(t*)(p+*j++))\
        J(x,t,*(t*)p=*s;s+=r;p+=(I)j) J(y,t,*(t*)(p+*j++)=*s;s+=r)
K(I,i0,i1,i2,i3)        K(C,c0,c1,c2,c3)        K(F,f0,f1,f2,f3)
J(e0,I,*s++=ic(*(I*)p);p+=(I)j) J(e2,I,dc(*(I*)p);*(I*)p=ic(*s);s+=r;p+=(I)j)
J(e1,I,*s++=ic(*(I*)(p+*j++)))  J(e3,I,dc(*(I*)(p+*j));*(I*)(p+*j++)=ic(*s);s+=r)
Z(*f[][2][2])()={i0,i2,i2,i3,f0,f1,f2,f3,c0,c1,c2,c3,0,0,0,0,e0,e1,e2,e3};
J(m0,I,(*(G)s)(p,h-1);p+=(I)j)  J(m1,I,(*(G)s)(p+*j++,h-1))

#define CK(n) if((unsigned)(n)>=m)q=10;
Z t2(w)A w;{I *p=w->p,j=*p;DO(w->n-1,if(*++p!=++j)R 0)R 1;}
xin(a,m,z)A a,z;{A *w=(A*)Y+1;HH hh[9],*h=hh;C *p=(C*)a->p;
I t=a->t,ar=a->r,*ad=a->d,b=!z,l,u=0,i=0,j,k=0,n=1,d[9],y[9],*v,s=0;
 if(!m&&b)R ic(a);Q(m>ar,7)
 for(;i<ar;n*=j,++i)if(a=w[i],i>=m||qz(a))j=d[k++]=ad[i],y[i]=0;
  else {Q(!QA(a)||a->t&&!(a=ci(i+1)),5)j=a->r,mv(d+k,a->d,j),k+=j,j=a->n,y[i]=j==1?1:t2(a)?2:(u+=j,3);}
 if(b){Q(k>9,13)W(ga(t,k,n,d))}
 else{if(r=z->n!=1){Q(k!=z->r,7)Q(cm(z->d,d,k),0)}if(!m)R tst(t,p,1,z->p,r,n),1;}
 if(!n)R(I)z;l=t+2&3,j=1<<l,v=tm(u);
 do{switch(a=w[--i],m=ad[i],u=y[i]){
   CS(0,for(;i&&!y[i-1];m*=ad[--i]);n=m)                /* elide  */
   CS(1,CK(k=*a->p)p+=j*k;if(i||s)continue;n=1)         /* single */
   CS(2,n=a->n; CK(k=*a->p)p+=j*k;CK(k+n-1))            /* iota   */
   CS(3,n=a->n; if(j!=1<<l)DO(n,CK(k=a->p[i])*v++=j*k)  /* list   */
                else DO(n,CK(k=a->p[i])*v++=k<<l))}
  u=u==3,h->n=n,h->j=u?v-n:(I*)j,h++->s=s?s:(I)z->p,s=(I)(!s?f[t][!b][u]:u?m1:m0);}
 while(j*=m,i); if(q){if(b)mf(z);R 0;}  R(*(G)s)(p,h-1),(I)z;}

xr(z,a,w)A a;{I i,f=a->t==Et,n=f?a->n:1;if(f)for(i=n;i--;*--Y=ic(a->p[i]));
 *--Y=0,z=xin(z,n,w),++Y;if(f)DO(n,dc(*Y++))R(I)z;}
#define CJ Q((unsigned)(n=*a++)>=e,10)
#define CI(T,f) G0(T,f)DO(n,CJ *r++=w[n])
CI(I,j0)CI(F,j1)CI(C,j2) G0(C,j3)DO(w,CJ tmv(t,r+T(i*v),w+T(n*v),v))
H2(ind){A z; if(a->t==Et)R xr(w,a,0);{XW;I1 Q(!wr,7)e=*wd;if(wr==1&&wt<Et){W(gd(wt,a))C2(!wt?j0:wt==1?j1:j2)}
 {XA;t=wt,u=an;v=tr(--wr,++wd);W(ga(wt,ar+wr,an*v,ad))if(t==Et)zr(z);mv(z->d+ar,wd,wr);C2(j3)}}}
G0(C,r2){I j=rm(v**a,n);tmv(t,tmv(t,r,w+T(j),n-j),w,j);}
G0(C,r3){I j,k=T(1);n=u;
 DO(v,j=rm(*a++,n);tst(t,tst(t,r,v,w+k*j*v,v,n-j),v,w,v,j);r+=k;w+=k)}
H2(rot){A z;I *d=w->d,j=a->n!=1,r=j?a->r:w->r-1;I1 u=*d++,v=tr(r,d);
 if(j){Q(r!=w->r-1,7)Q(cm(a->d,d,r),8)}W(gd(t=w->t,w))if(!u)R(I)z;C2(j?r3:r2)}
Z C *h(r,w,j)C *r,*w;{I n=d[j],k=c[j];
 if(d[++j]<0)r=tst(t,r,1,w,k,n);else DO(n,r=h(r,w,j);w+=T(k))R r;}
H2(dtr){A z;I k,r=w->r,i,n=1,m=0;unsigned j;I1 Q(a->n!=r,7)DO(r+1,d[i]=-1)
 for(i=r;i--;n*=k){j=a->p[i],k=w->d[i];Q(j>9,9)
  if(d[j]<0){if(c[j]=n,d[j]=k,j>m)m=j;}else if(c[j]+=n,--r,d[j]>k)d[j]=k;}
 Q(m>=r,9)W(ga(t=w->t,r,tr(r,d),d))R h(z->p,w->p,0),(I)z;}

#define GT(T,f) Z f(b,d,s,n)T *d,*s;{d+=n*b;DO(n,if(s[i]!=d[i])R s[i]>d[i])R 0;}
#define GB(T,f) Z f(r,o,p,m,n)I *r;T *o,*p;{I b,l,h;DO(n,l=0;h=m;\
 while(l<h)if(p[i]>o[b=(l+h)>>1])l=b+1;else h=b;r[i]=l)}
GB(I,b0)GB(F,b1)GT(I,bi)GT(F,bf)GT(UC,bc)
H2(bin){A z;if(!a->t&&w->t==Ft&&w->n==1&&ci(1))w=(A)Y[1];else{q=0;X2}{XA;XW;
 if(ar==1&&at<Ct){W(ga(It,wr,wn,wd))(*(at?b1:b0))(z->p,a->p,w->p,an,wn);}
 else{I(*f)(),n,b,*r,u=ar?(--ar,*ad++):1,v=tr(ar,ad),t=at;C *p;
 Q(at>Ct,6)wr-=ar;Q(wr<0,7)Q(cm(ad,wd+wr,ar),8)W(ga(It,wr,n=tr(wr,wd),wd))
 r=z->p,p=(C*)w->p,f=!at?bi:at==Ft?bf:bc; DO(n,I l=0;I h=u;
  while(l<h)if((*f)(b=(l+h)>>1,a->p,p,v))l=b+1;else h=b;r[i]=l;p+=T(v))}
 R(I)z;}}
  