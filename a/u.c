char what_a_u_c[] = "@(#) $Id: uc.,v 1.52 1993/04/24 00:57:58 maus Exp $";
#include "s.h"
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>

/*strings not equal */
#define strneq(a,b) (*(a)!=*(b)||strcmp((a),(b))!=0)

extern F strtod();extern C*strcpy(),*index();
I *J,G;Z C *r,*s;Z *t,tb[190000];

Z ha(n)
C *n;
{
       unsigned long h= 0, c;

       while ((c= (unsigned long)*n++) != 0)
       {
               h += (h << 5) + c;
       }
       R h;
}

#define HA(n)     (ha(n))
#define HASHSHIFT (10)
#define HASHSIZE  (1<<HASHSHIFT)

Z ST[HASHSIZE];S si(n)C *n;{S s,a=(S)(ST+((HASHSIZE-1)&HA(n)));
 for(;(s=a->s)&&strneq(n,s->n);a=s);
 if((s==0)&&(s=(S)malloc(5+strlen(n))))
s->s=a->s,a->s=s,strcpy(s->n,n);R s;}

A SymbolTableHashChainLengths()
{
        A z = gv(It, HASHSIZE);
        I *p = z->p;
        I i, j;
        S a, s;

        for (i = 0; i< HASHSIZE; i++)
        {
                for (j = 0, a = (S)(ST + i); s = a->s; j++, a = s);
                p[i] = j;
        }
        R z;
}	

V sv(c,s)CX c;S s;{C *t=index(s->n,'.'),b[99];
 if(t)*t=0,strcpy(b,s->n),*t='.',c=cxi(si(b)),s=si(t+1);R vi(s,c);}
Z ispu(c){R c==':'||c==';'||c=='('||c==')'||c=='{'||c=='}'||c=='['||c==']';}
Z issp(c){R c==' '||c=='\n'||c=='\t'||c==12;}isal(c){R c>='a'&&c<='z'||c>='A'&&c<='Z'||c=='_';}
isdi(c){R c>='0'&&c<='9';}Z isan(c){R isal(c)||isdi(c);}
Z std(s,d)C **s;F *d;{C *r=*s;I i='\242'==*r||!APL&&'-'==*r,j;r+=i;
 j=strncmp(r,"Inf",3)||isal(r[3]);if(j&&!isdi(r['.'==*r]))R 0;
 if(!j)*s=r+3,*d=Inf;else for(*d=strtod(r,s);**s=='0';++*s);if(i)*d=-*d;R 1;}
C *sy(s)C *s;{for(;isan(*++s););R s;}Z C *c0(s)C *s;{for(;issp(*s);++s);R s;}
C *s1(s)C *s;{for(;isan(*++s)||*s=='l';);R s;}
C *cl(s)C *s;{for(;s=c0(s),*s=='\343';)for(;*++s&&*s!='\n';);R s;}
C *bl(s)C *s;{for(;*s&&!issp(*s);++s);R s;}
/*pt(u,t)I *u,*t;{I i;for(;u<t;)ispu(i=*u++)?H("%c",i):pa(i);H("^\n");}*/
tc(t)I *t;{for(;t>tb;)if(!ispu(*--t))dc(*t);longjmp(J,-2);}
Z C *ts[]={"wsfull","stack","undEfined","MAX args: 9","( nesting too deep"};
Z trr(q,s)C *s;{if(!G)H("TOKEN: %s %s\n",q==2?s:"",ts[q]);tc(t);}
Z brr(c){if(!G)H("TOKEN: open %c\n",c);tc(tb);}
Z rs(v,i)C *v;{I t=0;C c=*s;*s=0;if(i&&(*v=='\312'||(t=pi(v)))){
 if(c=='/'||c=='\\'||c=='.'&&!isan(s[1])){*s++=c;
  if(c=='.'&&*s&&!ispu(*s)&&!issp(*s))++s;c=*s,*s=0,t=pi(v);}if(!t)trr(2,v);}
 else{if(i==1)trr(2,v);t=MS(si(v));}R *s=c,t;}
Z rq(c){while(*++s&&((c=='"'?*s=='\\':*s==c&&s[1]==c)?(I)++s:*s!=c));R *s;}
Z acp(d,s)C *d,*s;{C *t=d;for(;*d=*s;++d,++s)if(*s=='\'')++s;R d-t;}
Z ccp(d,s)C *d,*s;{C *t=d;for(;*d=*s;++d,++s)if(*s=='\\')if(*++s=='n')*d=10;else
 if(!isdi(*s))*d=*s;else{I j=3,n=*s-'0';for(;isdi(*++s)&&--j;n=n*8+*s-'0');--s,*d=n;}R d-t;}
I gsv(i,s)C *s;{I n=strlen(s);A z=gv(Ct,n);if(!i)strcpy(z->p,s);
 else n=z->n=*z->d=i==2?ccp(z->p,s):acp(z->p,s);if(n==1)z->r=0;R(I)z;}
Z gvs(t,n,s){R(I)gc(t,n!=1,n,&n,s);}
Z rw(){A z;I n=0,y;F d[9999];C c=*s,*v=s;extern *XY;
 if(ispu(c)&&(c!=':'||s[1]!='='))R *s++;
 if(c=='&'){if(!isdi(*++s))R ML(0);n=*s++-'0';if(Y+n>=XY)trr(1);R ML(n-=X-Y);}
 if((n=c=='"')||c=='\'')R ++v,rq(c),*s=0,n=gsv(n+1,v),*s++=c,n;
 for(;*s=='`';s=cl(s)){s=s1(v=s);t[n++]=rs(v+1,0);}if(n)R gvs(Et,n,t);
 for(;std(&s,d+n);s=c0(s))if(++n==9999)trr(1);if(n){C c=*s;*s=0,y=strpbrk(v,".Ee"),*s=c;
  if(!y)DO(n,if(y=d[i]!=(t[i]=d[i])){q=0;break;})R gvs(y?Ft:It,n,y?(I*)d:t);}
 if(s=cl(s),n=isal(*s)){s=sy(v=s);n=rs(v,2);}if(*s=='.'&&isal(s[1])&&(QS(n)||!n))
  R s=sy(v=s+1),y=rs(v,2),QS(y)?MV(vi(XS(y),n?cxi(XS(n)):Rx)):trr(2,".");
 if(n)R n;if(*++s=='='||*s=='L')++s;R rs(v,1);}
Z ra(k){r=s;t=tb;if(k)*t++='{';for(;*s;++t,s=cl(s))*t=rw();if(k)*t++='}';*t=0;R rd(tb);}

Z u,c,v;tfl(){/*ioctl?*/fflush(stdout);}
pr(){q=0;DO(u+v,H("*"))H("     "),tfl();}
Z chk(){if(c)if(--s,!rq(c))R c;else --v,++s;
 for(;s=cl(s),c=*s;++s){if(c=='"'||c=='\'')if(!rq(c))R ++v;
  if(c=='{'||c=='(')++v; else if(c=='}'||c==')')--v;}
 R v<0?(v=0):v>0||s[-2]==':';}
ff(a){if(Tf&&!qz(a))paf(a,1),NL,tfl();}
Z bal(f){C c,b[999],*v=s;I i=0,j,k=0;for(;s=cl(s),c=*s;++s)switch(j=0,c){
 case'"':CS('\'',if(!rq(c))brr(c))CS(';',if(!i){if(f)R;k=1;})
 case ')':++j;case ']':++j;CS('}',
  if(!i){if(f)R;brr(*s);}else if(b[--i]!="{[("[j])brr(b[i]))
 case '(':    case '[':    CS('{',if(i==999)trr(4);b[i++]=*s)}
 if(i)brr(b[i-1]);if(f)R;R s=v,k;}
C *nx(t)C *t;{R s=t,bal(1),s;}

Z de(){I a=exm(s,APL);if(q==-1&&J)u--,longjmp(J,-1);q=0;if(a)ff(a),dc(a);tm(0);}

Z EoF;Z C sb[99999],*b=sb;sbi(){b=sb,*b=c=v=0;}
C *sj(s,j)C *s;{R strncpy(sb,s,j),sb[j]=0,sb;}
Z f1(f)FILE *f;{I n=sb+sizeof(sb)-b;
 if(EoF=!fgets(b,n,f?f:stdin)){if(f)R 0;exit(1);}
 if(v&&!b[2]&&(*b=='\375'||*b=='$'))R sbi(),0;
 R n==strlen(b)+1?(H("buffer full\n"),sbi()):(s=b,chk()?(b=s,1):0);}
Z go(){I r;for(;issp(*--s););s[1]=0;s=cl(b=sb);if(!*s)R 0;
 if((r=*s=='\373'||*s==':')||!s[1]&&(*s=='\375'||*s=='$')){if(!J)R u;
  if(r){if(!s[1])R 1;r=exm(s+1,APL);if(!r)R q=0;}--u,longjmp(J,r?r:-3);} R de(),0;}

Z C *scp(s)C *s;{R strcpy(mab(1+strlen(s)),s);}
rf(s,f)C *s;{if(s)*++K=MV(s=scp(s)),*++K=-1;
 for(;;){if(!f1(f))if(EoF||go())break;if(s)--*K;}
 if(c||v)H("%s OPEN %c\n",b,c?c:'{'),c=v=0;if(s)K-=2,mf(s);}
tf(){I r=f1(0)?0:go();if(!r)pr();R r;}
ui(){CX c=Cx;if(*X){A f=(A)*X;Cx=(CX)f->p[f->n+2];}for(*++K=0,++u,pr();!tf(););R Cx=c,--u,--K,0;}

Z C *es[]={"stop","interrupt","wsfull","stack","value","valence","type","rand",
 "length","domain","index","mismatch","nonce","maxrank","non-function","parse","maxitems","invalid"};
xrr(){if(q>0)qs=es[q];q=0;}
Z prr(i,a)A a;{q=0;i==2?H("%d",a):pa(QA(a)&&a&&a->t>=Xt?*a->d:(I)a);H(": %s\n",i<0?qs:es[i]);}
C *qs;err(i,a){q=i;if(!Ef||G&&i)longjmp(J,-3);Tf=1;stdinFlagSet(Tf);prr(i,a);ui();R 0;}
perr(s){perror(s),fflush(stdout);}

Z tok(){jmp_buf b;CX c=Cx;I *j=J,*k=K,z=setjmp(J=b)?0:ra(bal(0));R K=k,Cx=c,J=j,z;}
ez(a){jmp_buf b;I *j=J,*k=K,*x=X,*y=Y,i;CX c=Cx;if(i=setjmp(J=b)){Cx=c;
 for(J=j,K=k,X=x;Y<y;)dc(*Y++);R q?0:i!=-3?i:0;}R a=ev(a),J=j,a;}
exm(a,m)C *a;{I e,z;s=cl(a);
 if(*s=='$')R sys(s+1),nl;if(!*s)R nl;Q(Y-K<30,3)
 z=APL,APL=m,e=tok(),APL=z;
 Q(!e,15)*++K=MS(a=scp(a)),z=ez(e),mf(a),K--,ef(e);if(!z){if(!q)q=9;R 0;}
 R QE(e)&&XE(e)->f==MN(0)?(dc(z),nl):z;}
extern I Gf,Sf;pev(a){I g=G;A z;G=Gf,a=ez(a),G=g;if(!a&&!q)longjmp(J,-3);
 z=gv(Et,2);*z->p=(I)gi(q);z->p[1]=q?gsv(0,q<0?qs:es[q]):a;R q=0,(I)z;}
pexm(a,m){I g=G;A z;R G=Gf,a=exm(a,m),G=g,a?(z=gs(Et),*z->p=a):(z=gi(q),q=0),(I)z;}
/* old entrypoints pex() and ex() included for compatibility with a_79 */
/* these two functions are not used by any native A+ code              */
pex(a) {R pexm(a,APL);}
ex(c,s) CX c;C *s;{I r;CX saveCx=Cx; Cx=c; r=exm(s,APL); Cx=saveCx; R r;}

extern I dbg_tf,dbg_depth;
#define FIN ++dbg_depth;if(dbg_tf)trc(f,1);if(i=f->p[f->n])t=t2(i,1)
#define FOUT if(i)t2(t,0);if(dbg_tf)trc(f,0);--dbg_depth

af(n)I n;{jmp_buf b;A f=(A)*Y;I i,*k,t,*j,*x,z,h=f->t==Xt;E e;if(h){I *d=f->d,i;
 if(QN(*d)){EQ(1,n!=2&&n!=3?(q=5,0):(z=n>2?Y[2]:0,f->r>2?rk(d[1],d[2],Y[1],z):ea(d[1],Y[1],z)))R z;}
 for(h=i=f->r;i--;*--Y=ic(d[i]));L0:f=(A)*Y;}
 if(f->t<=Xt)q=14;else if(Y-K<30)q=3;else if(n+h!=f->r)q=5;else if(!*f->p)q=r;
 else{CX c=Cx;x=X,X=Y,j=J,k=K,*++K=(I)f;DO(f->n-1,*--Y=0)FIN;
  if(z=setjmp(J=b)){if(z==-3){FOUT;longjmp(j,-3);}}else z=ev(*f->p);
  for(;Y<X;dc(*Y++));K=k,J=j,X=x;}
 L:if(q)if(z=err(q,f),!z)goto L0;DO(h,dc(*Y++))FOUT;R z;}
H1(sg){if(qz(a))longjmp(J,-3);qs=(C*)cs(a);Q(!qs||!a->c,9)longjmp(J,q=-1);}
frep(f)A f;{strcpy(f->p[f->n+1]=(I)mab(1+strlen(r)),r);}
