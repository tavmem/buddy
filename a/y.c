char what_a_y_c[] = "@(#) $Id: y.c,v 1.137 1993/04/26 22:29:21 maus Exp $";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/param.h>
#include <sys/file.h>
#include "f.h"
extern A versGet();
extern void yInstall();
extern I *K;

I APL,Xf,Sf=1,Df=1,Gf=1,Tf=1,Ef=1;
extern C *bl(),*cl(),Fs[],*pfind();extern V sv();
Z C*fi(s,r)C*s,*r;{Z C b[MAXPATHLEN];I n=strlen(s);
 if(s[n-2]!='.'||strchr(r,s[n-1]))strcpy(b,s),s=b,s[n]='.',s[++n]=*r,s[++n]=0;R s;}

Z C*afi(s)C *s;{Z C ap[]=".:/usr/local/a+/lib:/usr/local/lib/a:/common/a:/u/a";
 C *t,*r=pfind("APATH",ap,s,R_OK);
 if(!r)t=fi(s,"+a"),r=pfind("APATH",ap,t,R_OK);
 if(!r)t=fi(s,"a"),r=pfind("APTATH",ap,t,R_OK);
 R r;}

Z C*mfi(s,i)C *s;{C *t=fi(s,"m"),j=R_OK|(i?W_OK:0),*r=pfind("MPATH",".",t,j);
 if(!r)r=pfind("MPATH",".",s,j);if(!r)perr(t);R r;}

C *doloadafile(s,u) C *s;{   /*silent version loadafile */
 C r[MAXPATHLEN],*t=afi(s);
 CX x=Cx; I m=APL,c; FILE *f;
 if(!t)R (C *)0;
 if(!(f=fopen(t,"r")))R (C *)0;
 if ('#'==fgetc(f)&&'!'==fgetc(f)) while (EOF!=(c=fgetc(f))&&'\n'!=c);
 else rewind(f);
 if(u)unlink(t);
 gwd(r),APL=1,rf(u?0:s,f),Cx=x,APL=m,fclose(f),chdir(r);R strdup(t);}

loadafile(s,u) C *s;{         /* now a cover for doloadafile */
 I rc=(I)doloadafile(s,u);
 if (0==rc)R perr(s);else free((void *) rc);
 R 0;}

ai(n){sgi();mi();wi();if(!tmp(n<<20))R 0;ki();yInstall();nsfInstall();R 1;}
mpi(s,i)C *s;{I z;C *t;Q(!s||i<0||i<2||!(t=mfi(s,i&1)),9)
 ERR(t,z=open(t,i&1?O_RDWR:O_RDONLY))R nmap(z,i);}
Z pw(f,s,n)C *s;{I t;do t=write(f,s,n);while(s+=t,t!=-1&&(n-=t));fsync(f);R t;} /* IBM write fix */
Z mo(s,z)A z;C *s;{I f,t=z->t,c,n;C r[MAXPATHLEN],*p;Q(Ct<t,6)
 s=rindex(s,'.')>rindex(s,'/')?s:fi(s,"m");
 strcpy(r,s),strcat(r,"!@#");
 ERR(s,f=open(r,O_CREAT|O_WRONLY,0666))
 if(c=z->c)z->i=z->r?*z->d:1;
 if(t=pw(f,z,n=AH+T(z->n)+(t==Ct)),c)z->c=c;
 close(f);ERR(s,t)ERR(s,t)ERR(s,rename(r,s))R 1;}
C *cs(a)A a;{I s;R a->t==Ct?(C*)a->p:a->t==Et&&QS(s=*a->p)?XS(*a->p)->n:0;}
H1(bi){R mpi(cs(a),0);}H2(bo){I n;C *s=cs(a);R !s?mpi(cs(w),*a->p):mo(s,w)?nl:0;}
Z fzr(f,n){I j=getpagesize(),k=lseek(f,0,2);n=((n+j-1)/j)*j;
 for(;n<k;n+=j)lseek(f,n,0),write(f,&f,1);}
Z items(n,z){C *s=cs(z);Z struct a a;I f,t,m,j,w=n!=-1;Q(!s,9)
 ERR(s,f=open(fi(s,"m"),w?O_RDWR:O_RDONLY))ERR(s,read(f,&a,AH))Q(!a.r,7)
 m=*a.d;j=a.i;if(m>j)j=m;if(w){t=a.t;if(n==-2)fzr(f,AH+T(a.n)+(t==Ct));else{
  a.i-n,m=n*tr(a.r-1,a.d+1);if(n<*a.d)*a.d=n,a.n=m;lseek(f,0,0);
  ERR(s,write(f,&a,AH))ERR(s,flen(f,AH+T(m)+(t==Ct)))}}R close(f),j;}
Z rd(f,s,n)C *s;{C *t=s+n;I k;for(;s<t;s+=k)PERR("",k=read(f,s,n))R 1;}
H1(ri){I0;{A z;struct a b;I d=*a->p,t;
 Q(AH!=read(d,&b,AH)||b.t>Ct||b.r>MAXR||b.n!=tr(b.r,b.d),9)
 W(gd(t=b.t,&b))R rd(d,z->p,T(b.n))?(I)z:(dc(z),0);}}
Z vf(a,b,i)C *a,*b;{A z;V v;I f,t;FILE g,*h;
 if(!isal(*a)||!b)R H("incorrect\n");v=vi(si(a),Cx);switch(i){
 case 3:if(h=popen(b,"w"))g=*stdout,*stdout=*h,pa(gt(v)),NL,*h=*stdout,pclose(h),*stdout=g;else perr("pipe?");R;
 case 2:if(!QA(z=(A)v->a)||!z||!mo(b,z))R H("can't write%s\n",a);}dc(v->a),v->a=mi(b,1);} 
Z lst(n,s)C *s;{I i;CX x=*s?cx(s):Cx;V v;
 for(i=0;i<x->ht->nb;++i)for(v=x->ht->b[i];v;v=v->v)
 if(-1==n&&v->e||v->t==n&&v->a)pv(v);NL;}
Z pcx(cx)CX cx;{H(" %s",cx->s->n);}
Z cxs(){CX cx=Rx;for(;cx=cx->n;)pcx(cx);NL;}
#define EX(a) dc(v->a),v->a=0
exx(v)V v;{R v->o?0:(EX(a),EX(f),EX(c),EX(p),EX(q),EX(cd),EX(rff),EX(rfc),
                     EX(rpf),EX(rpc),EX(scd),rmd(v),dst(v));}
Z expunge (v)V v;{if (v->o) H("%s: is bound\n",v->s->n); else exx(v);}
C *cmdsList[]={"vars","fns", "ops","xfs","si","wa", "cx",  "rl",  "load",  "cd",
               "off", "mode","cxs","ex", "pp","sfs","stop","vers","loadrm","cmds",
               "def", "dep", "Tf", "Sf", "Xf","Df", "Gf",  "deps","Ef",    "_sfs",
               "dbg", 0};
Z C *ts[]={"0 off","1 on" "2 trace"};
#define CF(i,f) CS(i,if(*s)R f=*s=='s'?2:*s=='1';H("%s\n",ts[f]);)
sys(s)C *s;{C *v;S t;C c,d,*u,*w,*x;I f=0;A a;V q;
 v=strdup(s); s=cl(u=bl(v)),c=*u,*u=0,x=cl(w=bl(s)),d=*w,*w=0;
 switch(*v){case '|':++f,*w=d;case '>':++f;case '*':++f;case '<':vf(v+1,s,f);
   free(v);R;}
 switch(lu(v,cmdsList)){CS(16,xfs())CS(30,x_fs())CS(11,exit(0))CS(13,cxs())CS(9,loadafile(s,0))
  CS(1,lst(0,s))CS(2,lst(1,s))CS(3,lst(2,s);lst(3,s);lst(4,s))CS(4,lst(5,s))
  CS(5,--K;sik();NL;++K)CS(6,wa(!*s?-1:*s=='-'?-2:atoi(s)))
  CS(7,if(*s)Cx=cx(s);else H("%s\n",Cx==Rx?".":Cx->s->n))
  CS(8,srandom(atoi(s)))CS(10,PERR(s,chdir(*s?s:getenv("HOME")));setPWD();)
  CS(12,if(*s)R APL=s[1]=='p';H(APL?"apl\n":"ascii\n");)
  CS(14,for(;*s;*w=d,w=bl(s=cl(w)),d=*w,*w=0)expunge(sv(Cx,si(s))))
  CS(15,if(!*s||!isdi(*s)||s[1]&&!isdi(s[1]))R H("%c%c\n",Fs[3],Fs[4]);Fs[3]=s[1]?*s++:'0';Fs[4]=*s)
  CF(17,sq)CS(18,H("%p\n",(a=versGet())->p);dc(a))CS(19,loadafile(s,1))
  CS(21,f0(s))CS(22,f1(s))CF(24,Sf)CF(25,Xf)CF(26,Df)CF(27,Gf)CF(29,Ef)
  CS(31,dbg(s,x))
  CS(23,Tf=0;disable()) CS(20,for(;cmdsList[f];++f)H(" %s",cmdsList[f]);NL)
  CS(28,lst(-1,s)) 
  default:*u=c,*w=d;syst(v);}free(v);R;}
Z H1(c_i){A z;Q(a->t!=Ct&&a->n,6)W(gd(It,a))DO(a->n,z->p[i]=((UC*)a->p)[i])R(I)z;}
Z H1(i_c){A z;Q(a->t!=It&&a->n,6)W(gd(Ct,a))DO(a->n,((C*)z->p)[i]=a->p[i])R(I)z;}
H1(i_f){A z;Q(a->t!=It&&a->n,6)W(gd(Ft,a))DO(a->n,((F*)z->p)[i]=a->p[i])R(I)z;}
Z H1(f_j){A z;F f;Q(a->t!=Ft&&a->n,6)W(gd(It,a))DO(a->n,z->p[i]=(f=((F*)a->p)[i])>0?f+.5:f-.5)R(I)z;}
Z H1(f_i){A z;F f;I d;Q(a->t!=Ft&&a->n,6)W(gd(It,a))DO(a->n,f=((F*)a->p)[i];
 if(d=f>0?f+.5:f-.5,(f>d?f-d:d-f)>=CT*(f>1?f:f>-1?-f:1))R(q=6,dc(z),0);z->p[i]=d)R(I)z;}
A ci(i){I z;A a=(A)Y[i];R(A)((z=f_i(a))?(dc(a),Y[i]=z):0);}
A ep_cf(i){I z;A a=(A)Y[i];R(A)((z=i_f(a))?(dc(a),Y[i]=z):0);}
H2(cv){A z;I u,t=w->t;C c;if(a->t!=Et)R ds(a,w,1);Q(!QS(*a->p),9)
 Q(t>Ct&&w->n||a->n!=1,9)c=*XS(*a->p)->n;u=c=='i'?It:c=='f'?Ft:Ct;
 R u==t?ic(w):!u?(t==Ft?f_j(w):c_i(w)):t&&w->n?(q=6,0):u==Ft?i_f(w):i_c(w);}
H1(c_s){A z;XA;C *s=(C*)a->p;I n,j;Q(a->t!=Ct,6)!ar?(*ad=1):--ar;W(ga(Et,ar,n=tr(ar,ad),ad))an=ad[ar];
 DO(n,for(j=an;j--&&s[j]==' ';);z->p[i]=MS(si(sj(s,j+1)));s+=an)R(I)z;}
H1(s_c){A z;XA;I k;int m=0;C *s;
 Q(an&&!sym(a),6)DO(an,if(m<(k-strlen(XS(a->p[i])->n)))m=k)W(ga(Ct,ar+a,an+m,ad))z->d[ar]=m;s=(C*)z->p;
 DO(an,sprintf(s,"%-*s",m,XS(a->p[i])->n);s+=m)R(I)z;}
I cn(i,t){I a=Y[i],z=(I)gd(t,a);R dc(a),Y[i]=z;}
void yInstall(){install(items,"_items",9,2,9,0);R;}
