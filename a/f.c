char what_a_f_c[] = "@(#) $Id: f.c,v 1.24 1993/04/16 21:59:15 maus Exp $";
#include "f.h"
extern I *k,ind(),ran(),not(),neg(),aab(),sgn(),cln(),flr(),rec(),aen(),aln(),pit(),cir(),c_s(),s_c(),dtr(),
 ds(),rs(),sc(),os(),ic(),is(),sqr(),dea(),mat(),ncd(),dcd(),dis(),raz(),prt(),pct(),pen(),gz(),
 dep(),mat(),fnd(),mem(),upg(),dng(),mmd(),dmd(),det(),pic(),bi(),bo(),mth(),dth(),exm(),sg(),cv(),rot(),bin(),dot(),undot();
Z t,u,v;
I rsh(a,r,d)A a;I *d;{R g=rsh,a->c==1?(mv(a->d,d,a->r=r),ic(a)):(I)gc(a->t,r,a->n,d,a->p);}
Z H1(rdc){I r=a->r-1,d[9];Q(r<1,7);R mv(d,a->d+1,r),*d*=*a->d,rsh(a,r,d);}
Z H1(iot){A z;I1;{I r=a->n,*d=a->p,n=tr1(r,d);Q(n<0,9) Q(a->r>1,7)Q(r>9,13)W(ga(It,r,n,d))d=z->p;DO(n,d[i]=i)R(I)z;}}
Z H1(rav){R rsh(a,1,&a->n);}Z H1(sha){A z;W(g(It,a->r))mv(z->p,a->d,a->r);R(I)z;}
G0(C,m0){!u?zer(t,r,n):(w=tmv(t,r,w,n>u?u:n),n>u)?tmv(t,w,r,n-u):0;}
Z H2(rho){A z;I1{XW;I *d=a->p,r=a->n,n=tr1(r,d);Q(n<0,9)
 Q(r>MAXR,13)if(n==wn)R rsh(w,r,d);W(ga(t=wt,r,n,d))u=wn;C2(m0)}}
G2(C,m2){r=u!=1?tmv(t,r,a,v):trp(t,r,a,v);u!=2?tmv(t,r,w,n-v):trp(t,r,w,n-v);}
Z I cl(a,w,i)A a,w;I i;{A z;X2{XA;XW;I r,n,d[9];i=!ar&&!wr||i==23;
 if(ar&&wr)if(ar==wr)Q(cm(ad+!i,wd+!i),8)else{
  Q(i||wr-ar!=1&&ar-wr!=1,7)n=wr<ar;Q(cm(ad+n,wd+!n,ar-n),8)}
 if(wr<ar)n=1,mv(d+i,ad,r=ar);else mv(d+i,wd,r=wr),n=i||ar<wr?1:*ad;
 if(i)++r,*d=1;*d+=n;u=!ar?(an=tr(r=1,d+1),1):!wr?(wn=tr(r-1,d+1),2):0;
 W(ga(t=wt,r,an+wn,d))v=an;C2(m2)}}
G1(I,r0){I *p=r+n;for(;r<p;)*--p=*w++;}
G1(C,r1){C *p=w+T(n);for (;w<p;)r=tmv(t,r,p-=T(v),v);}
Z H1(rev){A z;I r=a->r;if(!r)R ic(a);W(gd(t=a->t,a))C1(!--r&&!a->t?r0:(v=tr(r,a->d+1),r1))}
Z I m,d[9];G1(C,t1){I h=m,i,c[9];DO(h+1,c[i]=0)if(!n)R;for(;;){for(n=c[i=h];i--;n=n*d[i]+c[i]);
 r=tst(t,r,1,w+T(n),v,u);for(i=h;++c[i]==d[i];)if(i)c[i--]=0;else R;}}
Z H1(tra){A z;XA;if((m=ar-2)<0)R ic(a);DO(ar,d[i]=ad[ar-1-i])
 if(u= *ad,v=tr(ar-1,ad+1),v<2)R rsh(a,ar,d);W(ga(t=at,ar,an,d))C1(t1)}
G0(C,k1){!u?tmv(t,r,w+T(v),n):u<0?tmv(t,zer(t,r,-u),w,n+u):zer(t,tmv(t,r,w+T(v),n-u),u);}
Z I td(a,w,i)A a,w;I i;{A z;I0{XW;I j= *wd,k,m=*a->p;if(!wr)j=1,++wr;
 if(i==26)m=m>0?(m>j?0:m-j):m<-j?0:m+j;k=tr(wr-1,wd+1);u=v=0;t=wt;
 if(m<0)if(m= -m,m>j)u=(j-m)*k;else v=(j-m)*k;else if(m>j)u=(m-j)*k;
  else if(wt<Ct&&w->c==1&&m)R g=k1,w->n=(*w->d=m)*k,ic(w);
 W(ga(wt,wr,m*k,wd))*z->d=m;C2(k1)}}
Z H1(siz){R(I)gi(a->r?*a->d:1);}
Z I b0(p,n)I *p,n;{I s=0,f=0;DO(n,if(~1&*p)if(f=1,*p<0)R 01;s+= *p++)R f?-s:s;}
G0(I,c0){I *p=r+n;for(;r<p;++w)if(*a++)*r++=*w;}
G0(F,c1){F *p=r+n;for(;r<p;++w)if(*a++)*r++=*w;}
G0(C,c2){C *p=r+n;for(;r<p;++w)if(*a++)*r++=*w;}
G0(C,c3){C *p=r+T(n),*s;I j,i=!u;for(;r<p;w+=T(v),a+=i)if(j=*a)if(r=tmv(t,s=r,w,v),--j)r=tmv(t,r,s,j*v);}
G0(I,x0)DO(n,*r++=*a++?*w++:0)G0(F,x1)DO(n,*r++=*a++?*w++:0.0)G0(C,x2)DO(n,*r++=*a++?*w++:' ')
G0(C,x3){C *p=r+T(n);for(;r<p;)if(*a++)r=tmv(t,r,w,v),w+=T(v);else r=zer(t,r,v);}
Z H2(cmp){A z;I1;{XA;XW;I bn=b0(a->p,an);Q(bn==-1,9)if((u=an==1)&&bn==1&&wr)R ic(w);Q(ar<11,7)V0
 if(u)bn*=*wd;else Q(*wd!=an,8)if(wr==1&&wt!=Et&&bn>=0){W(gv(wt,bn))C2(!wt?c0:wt==Ft?c1:c2)}
 if(bn<0)bn=-bn;v=tr(wr-1,wd+1);W(ga(t=wr,wr,bn*v,wd))*z->d=bn;C2(c3)}}
Z H2(xpn){A z;I1;{XA;XW;I bn=b0(a->p,an);Q(bn<0,0)Q(ar>1,7)V0
 Q(*wd!=bn,8)if(wr==1&&wt!=Et){W(gv(wt,an))C2(!wt?x0:wt==Ft?x1:x2)}
 v=tr(wr-1,wd+1);W(ga(t=wr,wr,an*v,wd))*z->d=an;C2(x3)}}
Z H1(ts){A z;Z C *t[]={"int","float","char","null","box","sym","fund"};
 W(gs(Et))*z->p=MS(si(t[a->t<Et?a->t:!a->n?3:QA(a=(A)*a->p)&&a->t<Xt?4:QS(a)?5:6]));R(I)z;}
Z H1(enc){A z;W(gs(Et))*z->p=ic(a);R(I)z;}Z H2(n){R q=5,0;}
Z H1(e1){Q(a->t!=Ct,6)Q(a->r>1,7)R exm(a->p,APL);}
Z H2(e2){I z=*a->p;CX cx=Cx;R!QS(z)?pexm(w->p,APL):(Cx=cxi(XS(z)),z=e1(w),Cx=cx,z);}
Z H1(st){switch(sq){CS(1,err(0,0))CS(2,ff(a))}R ic(a);}Z H1(out){R ff(a),ic(a);}
Z H1(cp){R a->c?ic(a):(I)gc(a->t,a->r,a->n,a->d,a->p);}
Z S as(a)A a;{R!a->r&&sym(a)?XS(*a->p):0;}
Z H1(mrf){S v=as(a);Q(!v,9)R ic(gt(sv(Cx,v)));}
Z H2(drf){S c=as(a),v=as(w);Q(!c||!v,9)R ic(gt(sv(cxi(c),v)));}
I(*P1[])()={ st,ts,ic,sgn,cln,flr,neg,rec,aab,enc,
               dis,  n,  n,upg,dng,aen,aln,ran,tra,iot,
               siz,sha,rav,not,rev, sg,out,upg,dng,dep,
               c_s,s_c, n, n, n,pct,raz,mmd,rdc,pit,
               sc,sc,sc,sc,sc,sc,rs,rs,rs,rs,
               rs,rs, n,n,n,n,n,n,n,n,
               n,n,n,n,n,n,n,bi,n,n,
               mth,e1,gz,cp,mrf,undot
};
I(*P2[])()={ ds,cv,ds, ds, ds, ds, ds, ds, ds, ds,
               ds, ds, ds, ds, ds,sqr, ds,dea,dtr,fnd,
               ind,rho, cl, cl,rot, td, td,bin,  n,mat,
               ncd,dcd,cmp,xpn,mem,pen,pic,dmd,prt,cir,
                n, n, n, n, n, n, n, n, n, n,
               os,os,os,os,os,os,is,bo,is,is,
               dth,e2,ic,n,drf,dot
};