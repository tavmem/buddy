char what_a_s_c[] = "@(#) $Id: s.c,v 1.31 1993/04/16 03:19:22 atw Exp $";
#include "f.h"
#define DD(f,u,v,x) Z f(r,a,w,n)u *r;v *a,*w;I n;{u *t=r+n;I i=aw!=1,j=aw!=2;for(;r<t;a+=i,w+=j)*r++= x;}
#define Di(x,f) DD(f,I,I,*a x *w)
#define Df(x,f) DD(f,F,F,*a x *w)
#define Dx(x,f) DD(f,I,F,*a x *w)
extern F pif(),floor(),log(),exp(),pow();I aw;Z(*f)(),t,u,v;
Z F fl(x)F x;{F y=floor(.5+x);R y=x>CT*(y>1?y:y<-1?-y:1.0)?y-1:y;}
Z F frm(x,y)F x,y;{F z;R!y?x:(z=fl(x/y))==-fl(-x/y)?0.0:x-z*y;}
rm(a,b){I r;R a<b&&a>=0?a:!b?a:(r=a%b,b<0&&r>0||r<0&&b>0?r+b:r);}
DD(pi,F,F,pif((int)*a,*w))
DD(i6,I,I,rm(*w,*a))DD(f6,F,F,frm(*w,*a))DD(h2,I,F,!ne(a,w))DD(h3,I,F,ne(a,w))
DD(lg,F,F,log(*w)/log(*a))G2(F,ex){I k=aw!=1,j=aw!=2;if(!k&&*a>0){F t=log(*a);
 DO(n,*r++=exp(t**w++))R;}DO(n,*r++=*a>0?exp(*w*log(*a)):pow(*a,*w);a+=k;w+=j)}
/*DD(ex,F,F,*a>0?exp(*w*log(Ia)):pow(*a,*w))*/
Dx(<(*w>0?CT1:CT2)*,h0)Dx(>(*w>0?CT2:CT1)*,h1)Dx(<=(*w>0?CT2:CT1)*,h4)Dx(>=(*w>0?CT1:CT2)*,h5)
Di(>*w?*a:,i2)Df(>*w?*a:,f2)Di(<*w?*a:,i3)Df(<*w?*a:,f3)
DD(c0,I,C,*a==*w)DD(c1,I,C,*a!=*w)DD(e0,I,I,!mt(*a,*w))DD(e1,I,I,!!mt(*a,*w))
Di(+,i0)Df(+,f0)Di(*,i1)Df(*,f1)Di(-,i4)Df(-,f4)Di(/,i5)Df(/,f5)
Di(<,j0)Di(>,j1)Di(==,j2)Di(!=,j3)Di(<=,j4)Di(>=,j5)Di(&,z0)Di(|,z1)
I(*df[][2])()={z0,0,z1,0,i0,f0,i1,f1,i2,f2,i3,f3,i4,f4,i5,f5,i6,f6,
 j0,h0,j1,h1,j2,h2,j3,h3,j4,h4,j5,h5,0,ex,0,lg,0,pi};
#define X0 Q((j=wt>Ft)&&w->n&&i!=11&&i!=12,6)
/* if(z->c==1&&t==wt)ic(z) can't reuse when possible error */
#define FF !j?df[i][wt]:i&1?(wt==Et?e0:c0):wt==Et?e1:e1
ds(a,w,i)A a,w;{A z;I t,wt,j=0;if(i==7||i>14)F2 else if(i<2)I2 else X2 wt=w->t;X0
 if(aw=a->n==1&&(w->n!=1||w->r>=a->r))z=w;else if(w->n==1)aw-2,z=a;
  else{Q(a->r!=w->r,7)Q(cm(a->d,w->d,a->r),8)z=a->c>1?w:a;}
 t=i<9?wt:i<15?It:Ft; W(gd(t,z))C2(FF)}
os(a,w,i)A a,w;{A z;I j=0,n;i-=50;if(i>14||i==7)F2 else X2{XA;XW,(*f)(),t,r=ar+wr;C *p,*ap;X0 Q(r>MAXR,13)
 OF(n,wn,an)W(ga(t=i<9||i>14?wt:It,wr+ar,n,ad))mv(z->d+ar,wd,wr);p=(C*)z->p;f=FF;
 aw=1,ap=(C*)a->p;DO(an,(*f)(p,ap,w->p,wn);ap+=Tt(at,1);p+=T(wn))R(I)z;}}
Z II[]={1,0,0,1,~0x7FFFFFFF,0x7FFFFFFF};Z F FI[]={0,0.0,1,-Inf,Inf};
#define IP(f,x,y) G2(F,f){I k=v;F *ap=a,*wp=w,s,t;DO(u,DO(k,a=ap;w=wp++;t=x;DO(aw,y;++a;w+=k)*r++=t)ap+=aw;wp-=k)}
IP(x2,FI[2],t+=*a**w)IP(x4,FI[4],if(t<(s=*a+*w))t=s)IP(x5,FI[5],if(t>(s=*a+*w))t=s)
G2(F,dot){F *t=a+aw,s=0.0;for(;a<t;)s+=*a++**w++;*r=s;}
Z F m2(r,x,y,l,n)F *r,*x,*y;{F *p=x+l,*q=y+1,a,b,c,d;a=b=c=d=0;
 DO(l,a+=*x**y;b+=*x++**q;c+=*p**y;y+=n;d+=*p++**q;q+=n)
 *r=a,r[1]=b,r[n]=c,r[n+1]=d;}
Z F m1(r,x,y,l,n)F *r,*x,*y;{F *q=y+1,a,b;a=b=0;
 DO(l,a+=*x**y;y+=n;b+=*x++**q;q+=n)*r=a,r[1]=b;}
Z F m0(r,x,y,l,n)F *r,*x,*y;{F *p=x+l,a,c;a=c=0;
 DO(l,a+=*x++**y;c+=*p++**y;y+=n)*r=a,r[n]=c;}
G2(F,mmu){I m=u,l=aw;n=v; DO(m>>1,DO(n>>1,m2(r,a,w,l,n);w+=2;r+=2)
  if(n&1)m0(r++,a,w++,l,n);w-=n;a+=2*l;r+=n)
 if(m&1){DO(n>>1,m1(r,a,w,l,n);w+=2;r+=2)if(n&1){*r=0;DO(l,*r+=*a++**w;w+=n)}}}
is(a,w,i)A a,w;{A z;i-=64;F2{XA;XW,r,n;aw=*wd;Q(!ar||!wr,7)Q(ad[--ar]!=aw,8)
 if(i==2&&!ar&&wr==1){W(gs(Ft))C2(dot)}  u=tr(ar,ad),v=tr(--wr,++wd),r=ar+wr;
 Q(r>MAXR,13)OF(n,u,v)W(ga(wt,r,n,ad))mv(z->d+ar,wd,wr);C2(i==2?mmu:i==4?x4:x5)}}
#define RG(q,f,x,y) Z f(r,w,n)q *r,*w;{q s=x,*t=w+n;for(;w<t;++w)y;*r=s;}
RG(I,b0,1,if(!*w)R *r=0)                RG(I,b1,0,if(*w)R *r=1)
RG(I,r0,0,s+= *w)RG(F,q0,0.0,s+= *w)     RG(I,r1,1,s*= *w)RG(F,q1,1.0,s*= *w)
RG(I,r2,II[4],if(s<*w)s= *w)RG(F,q2,FI[4],if(s<*w)s= *w)
RG(I,r3,II[5],if(s>*w)s= *w)RG(F,q3,FI[5],if(s>*w)s= *w)
I(*fr[][2])()={b0,0,b1,0,r0,q0,r1,q1,r2,q2,r3,q3};
G1(I,s0){*r= *w++;(*f)(r+1,r,w,n-1);}   G1(F,s1){*r= *w++;(*f)(r+1,r,w,n-1);}
G1(C,s3){I k=T(n=v);tmv(t,r,w,n);DO(u-1,(*f)(r+k,r,w+=k,n);r+=k)}
G1(C,rr){I k=T(n=v);tmv(t,r,w,n);DO(u-1,(*f)(r,r,w+=k,n))}
rs(a,i)A a;{A z;i-=46;if(i<2)I1 else X1{XA;if(ar){u=*ad++;if(!u&&(i==4||i==5))at=Ft;--ar;}
 if(!ar){W(gs(at))C1(fr[i][at])}W(ga(at,ar,v=tr(ar,ad),ad))
 if(!u)R trp(at,z->p,at?(I*)(FI+i):II+i,v),(I)z;f=df[i][t=at],aw=0;C1(rr)}}
sc(a,i)A a;{A z;i-=40;if(i<2)I1 else X1{XA;if(!ar||!an)R ic(a);
 W(ga(at,ar,an,ad))f=df[i][at],aw=0;C1(ar>1?(t=at,u= *ad,v=tr(ar-1,ad+1),s3):at?s1:s0)}}
G2(I,p0){I *p=r,s;DO(n,*p++=*w++)DO(u-1,s=*(a+=v);p=r;DO(n,*p++=*p*s+*w++))}
G2(F,p1){F *p=r,s;DO(n,*p++=*w++)DO(u-1,s=*(a+=v);p=r;DO(n,*p++=*p*s+*w++))}
H2(ncd){A z;I n=a->n;if(a->t||w->t||0>tr1(n==1?-*w->d:n,a->p))F2{XW;Q(!wr--||a->r>1,7)u=*wd++;
 Q(n!=1&&n!=u,8)v=n>1;W(ga(wt,wr,tr(wr,wd),wd))if(!u)R zr(z);C2(wt?p1:p0)}}
G2(I,o0){I s;DO(v,s=*w++;r+=n;a+=u;DO(u,r-=v;*r=rm(s,*--a);s=*a?(s-*r)/ *a:0)r++)}
G2(F,o1){F s;DO(v,s=*w++;r+=n;a+=u;DO(u,r-=v;*r=frm(s,*--a);s=*a?(s-*r)/ *a:0.0)r++)}
H2(dcd){A z;if(a->t||w->t)F2{XW;u=a->n,v=wn;Q(a->r!=1,7)W(ga(wt,wr+1,u*v,wd-1))*z->d=u;if(!u)R(I)z;C2(wt?o1:o0)}}
#define MF(u,v,x) {u *r=(u*)z->p,*t=r+a->n;v *w=(v*)a->p;for(;r<t;++w)*r++= x; R(I)z;}
#define MT(T) if(T&&a->c==1)++(z=a)->c;else W(gd(T?a->t:It,a))
H1(neg){A z;F1 MT(1)MF(F,F,-*w)}
H1(aab){A z;F1 MT(1)MF(F,F,*w<0?-*w:*w)}
H1(sgn){A z;X1 MT(0)if(a->t==It)MF(I,I,*w<0?01:*w>0)else MF(I,F,*w<0?01:*w>0)}
H1(not){A z;I1 MT(1)MF(I,I,!*w)}
H1(cln){A z;F1 MT(1)MF(F,F,-fl(-*w))}   H1(rec){A z;F1 MT(1)MF(F,F,1/ *w)}
H1(aln){A z;F1 MT(1)MF(F,F,log(*w))}    H1(aen){A z;F1 MT(1)MF(F,F,exp(*w))}
H1(pit){A z;F1 MT(1)MF(F,F,3.14159265358979323846**w)}
H2(sqr){A z;F s;F1 if(!w->r&&2==*w->p){MT(1)MF(F,F,*w**w)}R ds(a,w,15);}
Z H1(fli){A z;MT(0)MF(I,F,*w<-CT?(I)(*w*CT1)-1:(I)(*w*CT2))}
H1(flr){A z;F1 if(z=(A)fli(a),!q)R(I)z;q=0,dc(z);MT(1)MF(F,F,fl(*w))}
Z rnd(n){I d=random();unsigned long r=(unsigned)0x80000000%n;R r>d?rnd(n):d%n;}
H1(ran){A z;I1 MT(1)DO(a->n,if(a->p[i]<1){q=9;break;}z->p[i]=rnd(a->p[i]))R(I)z;}
H2(dea){A z;I h,j,k,*p,*t,m,n;I2 m= *a->p,n= *w->p;
 Q(a->n!=1||w->n!=1||m<0||m>n,9)
 if(m>n/8){W(gv(It,n))p=z->p;DO(n,p[i]=i)
  for(t=p+m;p<t;*p++=j)j=p[k=rnd(n--)],p[k]= *p;R z->n=*z->d=m,(I)z;}
 W(gv(It,m))if(!m)R(I)z;p=z->p,t=tm(2*m)-1,j=1<<(0xff&(h=*t));DO(j--,t[i]=-1)DO(m,k=j&(m=rnd(n));
  for(;t[k]!=-1;)k=j&(t[k]==m?(m=rnd(n)):++k);t[k]=*p++=m)R *t=j,(I)z;}
