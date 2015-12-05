char what_a_p_c[] = "@(#) $Id: p.c,v 1.32 1993/04/22 20:22:38 maus Exp $";

#include <math.h>
#include "s.h"
#include "fir.h"
#undef min
#undef max
#define iszero(x) (x==0.0)

#define PC putchar
Z C *ns[]={":=","else","if","while","do","case","time","","@","each",0};
Z C *ps[]={"&","?","+","*","max","min","-","%","|","<",
             ">","=","~=","<=",">=","^","log","rand","flip","iota",
             "*","rho",",","~","rot","take","drop","upg","dng","==",
             "pack","unpack","/","\\","in","bag","pick","mdiv","!","pi",
             "&\\","?\\","+\\","*\\","max\\","min\\","&/","?/","+/","*/",
             "max/","min/", "+.","*.","max.","min.","-.","%.","|.","<.",
             ">.","=.","~=.","<=.",">=.", "^.","+.*","beam","max.+","min.+",
             "form","eval","where","of","ref","dot",0};
Z C *n0[]={"\373","else","if","while","do","case","time","","@","\241",0};
Z C *p0[]={"^","\251","+","\253","\323","\304","-","\337","|","<",
             ">","=","\250","\244","\246","*","\360","?","\364","\311",
             "#","\322",",","~","\367","\331","\325","\350","\347","\275",
             "^\\","\251\\","+\\","\253\\","\323\\","\304\\","^/","\251/","+/","\259/",
             "\323/","\304/","\312.+","\312.\253","\312.\323","\312.\304","\312.-","\312.\337","312.|","\312.<",
             "\312.>","312.=","\312.\250","\312.\244","\312.\246","\312.*","+.\253","\350","\323.+","\304.+",
             "\356","\342","\335","\333","%","\326",0};
extern C *xs[],*xd[],*index(),*nx(),*cl();
lu(s,t)C *s,*t[];{I i=0;for(;t[i];)if(!strcmp(s,t[i++]))R i;R 0;}
Z C*pp(a){R QS(a)?XS(a)->n:(QN(a)?(APL?n0:ns):QP(a)?(APL?p0:ps):xs)[U(a)];}
Z C*ppd(a){R QS(a)?XS(a)->n:(QN(a)?(APL?n0:ns):QP(a)?(APL?p0:ps):xd)[U(a)];}
pi(s)C *s;{I i;if(i=lu(s,APL?n0:ns))R MN(i-1);if(i=lu(s,APL?p0:ps))R MP(i-1);
 if(*s=='_')if(i=lu(s,xs))R MX(i-1);R 0;}
Z C*fn(s,n)C *s;{for(;--n;)s=1+nx(s);R s;}
Z C*ss(q,s)C *q,*s;{I n=strlen(s);for(;strncmp(q,s,n);)++q;R q;}
Z C*sb(q)C *q;{I i=0;C c;for(;c=*q++,i||c!='{';)i+=(c=='(')-(c==')');R q;}
sik(){I *p=K,s;for(;*p;--p);for(++p;p<=K;)if(QV(s=*p++))H("%ld[ %ld]\n",s&~M,-*p++);
 else{C c,*t,*q,*r;if(QS(s))q=(C*)(s&~M);else{A f=(A)s;q=1+index(f->p[f->n+1],':');
  H("%s.%s: ",((CX)f->p[f->n+2])->s->n,XS(*f->d)->n);}
  for(;p<=K&&*p>-9999&*p<6;++p,s=0)
   q=cl(0>*p?fn(QS(s)&&*q!='{'?q:sb(q),-*p):ss(q,ns[*p]));
  t=nx(q);r=index(q,'\n');if(r&&r<t)t=r;c=*t,*t=0,H("%s\n",q),*t=c;}}

sk(){I *p=K,s,i=0;for(;*p;--p);for(;p++<K;)s=*p,
 s<0&&s>-999?H("%ld ",-s):s>0&&s<6?H("%s ",n0[s]):(i?H("]\n"):0,i=!QS(s),
  H(i?"%s[":"%s\n",!i||QV(s)?(C*)(s&~M):XS(*((A)s)->d)->n));if(i)H("]\n");}

#define BRK {if(q==1)R 0;}
Z u;Z in(){NL;DO(2*u,PC(' '))}
pv(v)V v;{H(" %s",v->s->n);}

pa(v)V v;{paf(v,0);}

Z C b[30];C Fs[]=" %.10g";
Z bd(){I i=0;for(;b[i]&&b[i]!='.'&&b[i]!='e';++i);R i;}
Z h(s)C *s;{if(APL&&b[1]=='-')b[1]='\242';strncpy(s,b,strlen(b));}

Z C *iin[]={""," INf"," -Inf"," Na", " 0"};
Z inf(x)F x;{R /*x==-999999999?3:*/iszero(x)?4:finite(x)?0:isnan(x)?3:x>0?1:2;}
Z mfmt(b,s,x)C *b,*s;F x;{I i=inf(x);R i?strlen(strcpy(b,iin[i])):SH(x);}
Z dfmt(b,s,m,n,x)C *b,*s;F x;{I k,l,j=inf(x);if(!j)R(I)sprintf(b,s,m,n,x);
 if(4==j)R(I)sprintf(b,s,m,n,0.0);
 k=strlen(iin[j]);l=' '==*s;DO(m+l,b[i]=' ')strncpy(' '==*s?b:b+m-k,iin[j],k);}

A mj(a)A a;{P p;I m=0,j=a->t?2:1,l,k;C *s=a->t?Fs:" %d";p.i=a->p;DO(a->n,if(!a->t)k=SH(p.i[i]);
 else{l=mfmt(b,s,p.f[i]);k=l-bd();if(k>j)j=k<10?k:10;k=l-k;}if(k>m)m=k)R m+=3+--j,gf((F)m+(F)j/10);}

H1(mth){A z;XA;P p;C *s=at?Fs:" %d",*d;I j=0,k,m=0,n,l;if(at==Ct)R ic(a);
 if(at==Et){Q(ar||(a=(A)*a->p,!QF(a)),6)R gsv(0,!QA(a)?pp(a):a->t==Xt?"*derived*":(C*)a->p[a->n+1]);}
 p.i=a->p;n=ar?ad[--ar]:1;
 if(ar)DO(an,BRK if(at){l=mfmt(b,s,p.f[i]);k=bd();if(k>j)j=k;k=l-k;}
                 else   k=SH(p.i[i]);if(k>m)m=k)
 else DO(an,BRK m+=at?mfmt(b,s,p.f[i]):SH(p.i[i]))
 m+=j;W(ga(Ct,ar+1,ar?an*m:m,ad))z->d[ar]=ar?m*n:m;zr(z);d=(C*)z->p;
 if(ar)DO(an,at?(mfmt(b,s,*p.f++),h(d+j-bd())):h(d+m-SH(*p.i++));d+=m)
 else DO(an,k=at?mfmt(b,s,*p.f++):SH(*p.i++);h(d);d+=k) R(I)z;}

paf(a,f)A a;{I t;CX cx;BRK switch(M&(I)a){
 case 4:if(U(a)>9)goto L;case 2:case 6:CS(7,H(" %s",(f)?ppd(a):pp(a)))
 CS(1,L:cx=XV(a)->cx;if(Cx==cx)pv(XV(a));else{if(cx!=Rx)pv(cx);H(".%s",XV(a)->s->n);})
 CS(3,paf(XE(a)->f,f);H("... "))
 CS(5,t=U(a);(a=(A)*X)&&t>-a->n&&t<a->r?paf(t<0?a->p[-t]:a->d[t],f):H(" &"))
 case 0: if(!a)R;t=a->t;
 if(t>Et)R H("%s",t>Xt?(u?XS(*a->d)->n:(C*)a->p[a->n+1]):"*derived fn*");
 {I an=a->n,r=a->r,j=t==Et,n,k,d[9],*p;C *s;
  if(!an)R;if(!j){if(t!=Ct)dc(a=(A)mth(a));if(q)R 0;s=(C*)a->p,an=a->n,r=a->r;}
   else{p=a->p;if(r<2&&sym(a)){DO(an,H(" `%s",XS(*p++)->n))R;}}
  if(r>1)for(mv(d,a->d,r),n=d[k=r-1];--k;)d[k]*=d[k+1];else n=r?an:1;
  for(;;){if(j)DO(n,H("< ");++u;paf(*p++,f);--u;if(i<n-1||an>n)in())
    else DO(n,BRK PC(*s++))
   if(!(an-=n))R;for(k=r;--k&&!(an%d[k]);)in();}}}}

H2(dth){A z;if(sym(w))F1 else F2{Z f[99],g[99],h[99];XW;I n=a->n,u,v,j=0,k=n!=1,*r;
 F x,*p=(F*)a->p;C *s;if(!wr)u=v=wr=1;else u=tr(wr-1,wd),v=wd[wr-1];Q(n!=v&&k,8)
 Q(n>99,12)DO(n,x=p[i];if(f[i]=x<0)x=-x;j+=g[i]=x;h[i]=.5+10*(x-g[i]);)
 W(ga(Ct,wr,u*(j=k?j:j*v),wd))z->d[wr-1]=j,s=(C*)z->p;for(p=(F*)(r=w->p);u--;)DO(v,
  if(j=k?i:0,wt==Et)sprintf(s,f[j]?" %-*s":"%*s",g[j]-f[j],XS(*r++)->n);
  else dfmt(s,f[j]?" %- *.*e":"%*.*f",g[j]-f[j],h[j],*p++);s+=g[j])R(I)z;}}
