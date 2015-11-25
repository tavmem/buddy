char what_a_r_c[] = "@(#) $Id: r.c,v 1.68 1993/04/23 20:38:21 maus Exp $";
#include "k.h"
#include <dap/balloc.h>
extern I Df;Z rl(),re();Z I *t;Z y,*u,*r,Qs;Z vl(a){E e;R QL(a)||QV(a);}
Z cvl(a){R vl(a)||QE(a)&&XE(a)->f==MP(74);}
Z pvl(a){E e;R cvl(a)||QE(a)&&(e=XE(a),e->n==2&&e->f==MP(36)&&cvl(e->a[1]));}
Z rvl(a){E e;R pvl(a)||QE(a)&&(e=XE(a),e->n==1&&e->f==MP(22)&&pvl(*e->a));}
Z C *ps[]={"ws?","op?","var?","fn?","fninshed?","assign?","naked [?",
 "max # args 9","valence?",":header?","List too ling?","too many locals?"};
Z prr(i,j){extern G;if(!G)if(H("PARSE "),i==2?pa(j):0,H(": %s\n",ps[i]),Qs)
 if(QS(Qs))H("%s\n",XS(Qs)->n);else sk(),dc(Qs);for(;*r;)mf(*r--);tc(r);}
Z E mm(n){if(*++r=(I)ma(n))R(E)*r;--r,prr(0);}

unsigned long hafn(unsigned long key){R key^key>>11;}
#define HTHASH(ht,s) ((ht)->b+(((ht)->nb-1)&hafn(((unsigned)(s))>>3)))

Z unsigned Ha(key)unsigned key;{R key^key>>11;}
HT hti(nb){HT ht=(HT)malloc((2+nb)*sizeof(I));
ht->nb=nb;ht->ni=0;bzero(ht->b,nb*sizeof(I));R ht;}

CX cxi(s)S s;{CX cx,a=Rx;if(s==a->s)R a;for(;cx=a->n;a=cx)if(s==cx->s)R cx;
a->n=cx=(CX)malloc(sizeof(*cx));cx->ht=hti(HTSIZE);cx->s=s;cx->n=0;R cx;}

V vi(s,cx)S s;CX cx;{HT ht=cx->ht;V v,vh;V *bp=(V *)HTHASH(ht,s);
 for(v=*bp;v;v=v->v)if(s==v->s)R v;
 v=(V)malloc(sizeof(*v));bzero(v,sizeof(*v));v->s=s;v->cx=cx;v->z=1;++ht->ni;
 if(vh=*bp) {v->v=vh->v;vh->v=v;} else *bp=v;R v;}

CX cx(s)C *s;{R *s!='.'?cxi(si(s)):Rx;}

gz(){R nl;}qz(a)A a;{R QA(a)&&a->t==Et&&!a->n;}
#define ELSE MN(1)
ty(a){I t;if(!QL(a))R QA(a)?0:QV(a)?(t=XV(a)->t,t==5?1:t):a==MN(8)?3:a==MN(9)?2:1;
 if(0>(a=U(a)))R 0;t=Qs||*X?((A)(Qs?Qs:*X))->t-Xt:0;R!a?t:a==1&&t>1||a==2&&t==4?1:0;}
Z me(n,f,a,b,c){E e=mm(n+2);e->n=n,e->f=f,*e->a=a;if(n>1)e->a[1]=b;if(n>2)e->a[2]=c;
 R QP(a)&&(f==MN(8)&&QA(b)||f==MN(9)&&a!=MP(74))?(a=ee(e),*r=a,ef(ME(e)),a):ME(e);}
Z mr(){R *t&&*t!=';'&&*t!=')'&&*t!=']'&&*t!='}'&&*t!=ELSE;}
Z rt(g){I f,a,b,c=0;if(!mf())prr(4);switch(f= *t++){
 case MN(5):case MN(3):CS(MN(2),*++K=U(f);u=u;if(a=rt(0),q)prr(3);b=mr()?re():nl;
  if(*t==ELSE){u=++t;*K=1;c=re();}--K;R me(c?3:2,f,a,b,c))
 CS('[',prr(6))CS('(',--t;a=rl(MN(7)))CS('{',--t;a=rl(MN(1)))
 default:y=ty(a=f);} if(!y)for(;*t==';';)a=rl(a);R a;}
#define RLBLEN 999
#define rlbf bfree(b==r==rlb?0:b)
Z rl(f){E e;I rlb[RLBLEN], *b=rlb,n=0,blen=RLBLEN;
if(*t++=='[')b[n++]=f,f=MX(0);*++K=0;
 for(;*t!=']'&&*t!='}'&&*t!=')'&&*t;){
  if(n==blen) { blen*=2;
    if(b==rlb) { b=balloc(blen*sizeof(I)); bcopy(rlb,b,RLBLEN*sizeof(I));}
    else b=brealloc(b,blen*sizeof(I)); }
  if(--*K,b[n++]=*t==';'?nl:(u=t,re()),*t==';')++t; }
 if(t[-1]==';')b[n++]=nl;u=++t;--K;if(n==1&&(f==MN(7)||!t[-1])){n=*b;rlbf;R n;}
y=0;
 if(!n&&f==MN(7)){R rlbf,nl;}
 if(QP(f)&&n!=1&&n!=2)rlbf,prr(8);R e=mm(n+2),e->f=f,mv(e->a,b,e->n=n),rlbf,ME(e);}
Z rf(){I a=rt(1),f;for(;mr()&&ty(f= *t)>1;y=1)
 if(++t,a=ty(f)==2?me(1,f,a):me(2,f,a,rt(1)),y>1)prr(1);
 R *t=='{'&&(!QN(a)||MN(6)==a)?rl(a):a;}
Z vs(e)E e;{DO(e->n,if(!vl(e->a[i]))R 0)R 1;}
peak(f){E e=XE(f);R QE(f)&&e->f==MN(9)&&*e->a==MP(74);}
Z as(a){I z;E e;if(!(pvl(a)||QE(a)&&(e=XE(a),peak(e->f)||(e->f==MN(7)?vs(e):
  e->f!=MP(36)&&e->f!=MP(74)&&rvl(e->a[e->f==MX(0)?0:e->n-1])))))prr(5);
 ++t,z=me(2,MN(0),a,re());if(QV(a))XV(a)->t=y;R z;}
Z re(){I f,a,w;a=rf();if(!mr())R a;if(*t==MN(0))R as(a);if(y>1)prr(1);
 if(f=!y){f=rf();if(y!=1)prr(2,a);}w=re();if(y)prr(3);R f?me(2,f,a,w):me(1,a,w);}
Z in(s,b,r)I *b;{for(;r--;)if(b[r]==s)R 1;R 0;}
Z lk(s,f)A f;{I i;if(!f)R 0;if(f->r>1)DO(f->r,if(f->d[i]==s)R ML(i))
 for(i=f->n;--i;)if(f->p[i]==s)R ML(-i);R 0;}
Z str(t,r,b,n,p)I *t,*b,*p;{I f;if(f=t[-1]==')'&&t[-3]==';')--t;
 do if(QS(*--t)&&!in(*t,b,r)&&!in(*t,p,n)){if(n==999)prr(11);p[n++]=*t;}while(f&&*--t==';');R n;}
Z rz(b)I *b;{I i;A f;for(r=t=b;*r;++r)if(QS(*r))*r=(i=lk(*r,Qs?Qs:*X))?i:
 MV(vi(XS(*r),Cx)); R re();}
extern V sv();
f0(s){A a=(A)sv(Cx,si(s))->e;if(a)H("%x\n",a->p[a->n=1]);}
f1(s){I *l=sv(Cx,si(s))->l;for(;l;l=(I*)*l)H("%s ",((V)l[1])->s->n);NL;}
Z app(a,k)A a;{DO(a->n,if(a->p[i]==k)R)a->p[a->n]=k;a->n=++*a->d;}
Z mrg(a,w)A a,w;{A z;I n=a->n;if(w&&w->t==Et&&w->n)w=(A)*w->p;if(!w||qz(w))R(I)nl;
 z=gv(It,n+w->n),tmv(It,z->p,a->p,n),*z->d=z->n=n;
 DO(w->n,app(z,w->t?(I)(.5+((F*)w->p)[i]):w->p[i]))R(I)z;}
inv(v,i)V v;{if(v->z<2){I *l=v->l;A z=v->i;for(v->z=2;l;l=(I*)*l)inv(l[1],l[2]?i:0);
 v->z=0;if(z&&!qz(z))i=mrg(z,i),dc(z),v->i=(A)i;}}
val(v)V v;{if(v->z=1,v->i)dc(v->i),v->i=gv(It,0);}
gt(v)V v;{if(Df&&!v->z&&v->e){A i=v->i&&!v->a?(A)nl:v->i;I z;E e=(E)ma(3);
  if(v->z=2,e->f=v->e,e->n=!!i)if(qz(*e->a=(I)i))i=0;
  if(Df==2)if(pa(MV(v)),NL,i)pa(i),NL;if(z=ez(ME(e))){aset(v,ic(z),i,0);
   if(Sf&&v->rff)dc(af4(v->rff,v->rfc,z,i,0,v));dc(z);}val(v),mv(e);}
 for(;~v->a;)err(4,MV(v));R v->a;}
Z s1(v,a,i)V v;{I *l=(I*)&v->l,*n;if(a==(I)v)R;for(;n=(I*)*l;l=n)if(n[1]==a)R;*l=(I)(n=ma(3)),*n=0,n[a]=a,n[2]=i;}
Z s0(v,a)V v;{I *l=(I*)&v->l,*n;for(;n=(I*)*l;l=n)if(n[1]==a)R *l=*n,mf(n);}
Z s2(v,a,n)V v;{if(QV(a))n?s1(XV(a),v,0):s0(XV(a),v);else if(QE(a)){E e=XE(a);
 if(n>1&&e->f==MX(0)&&QV(*e->a)&&e->a[1]==ML(1))R s1(XV(*e->a),v,1);
 if(e->f==MN(0)&&e->n==2)R s2(v,e->a[1],n); DO(e->n,s2(v,e->a[i],n))}}
rmd(v)V v;{A a;if(a=(A)v->e)s2(v,*a->p,0),dc(a),v->e=0,dc(v->i),v->i=0;}
Z sad(v,a)V v;A a;{rmd(v),v->e=(I)a,s2(v,*a->p,a->r),inv(v,0);if(a->r==2)v->i=gv(It,0);}

rd(b)I *b;{I i;A z;V v;Qs=0;for(u=t=b;*t&&*t!=':';++t);if(!*t)R rz(b);
 for(r=t;*++r;);{A f;I p[999],n=1,r=b[1]=='[',*j,*k,*x=X,y=1,d=r||b[1]==':';
 if(d){if(r){if(b[3]!=']'||t!=b+4)prr(9);b[3]=b[2],b[2]=*b,b+=2;}goto L;}
 if(t[-1]=='}'){if(t==b+3)t[-1]=*b,b=t-1;else{for(j=k=t;j>b;)*--k=*(j-=2);b=k;}goto L;}
 if(t-b<4){if(t-b==3)r=*b,*b=b[1],b[1]=r;goto L;}
 if(y=*b!='('){if(b[1]!='(')prr(9);b[1]=b[3];b[3]=b[4];t[-2]=*b;}
 else{r=b[1];b[1]=b[2];b[2]=r;}y=t-b++-y;y=y==5?2:y==6?3:0;if(!y)prr(9);
L:r=t-b;if(!r)prr(9);
 if(QV(*b))v=XV(*b),Cx=v->cx,*b=MS(v->s);else if(QS(*b))v=vi(XS(*b),Cx);
 DO(r,if(!QS(b[i])&&b[i]!=')')prr(9))Qs=*b;
 if(y==3&&*XS(b[2])->n=='g')++y;u=b+1;if(r-1>MAXR)prr(7);
 for(*p=0,j=t;*++t;){if(*t==':')prr(9);if(*t==MN(0))n=str(t,j-b,b,n,p);}
 f=(A)(d?v->e:v->a); i=f&&QA(f)&&f->t>Xt?f->p[f->n]:0;
 z=ga(Xt,r,n+3,b),z->t+=y,z->n-=3,frep(z),z->p[n]=i,z->p[n+2]=(I)Cx;Qs=(I)z;
 mv(z->p,p,n),*++K=(I)z,*z->p=rz(j+1),--K;
 R d?sad(v,z):(v->t=y,set(MV(v),z)),nl;}}