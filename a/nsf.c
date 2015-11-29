/*LINTLIBRARY*/
char what_a_nsf_c[] = "@(#) $Id:nsf.c,v 1.51 1993/04/22 21:03:57 maus Exp $";

#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/param.h>
#include <sys/file.h>

#include <dap/dap.h>

#include "f.h"
#include "x.h"
#include "b.h"
#include "fir.h"
#undef min

#define HAVE_STRERROR 1
#ifndef HAVE_STRERROR 
  extern int sys_nerr;
  extern char *sys_errlist[];
#endif

extern V sv();
extern S si();

extern C *doloadafile();

extern C Fs[];
extern C *xs[], *cmdsList[];

#undef ENTRYPOINT
#define ENTRYPOINT static
Z A gsym(str) C *str; { A z=gs(Et); z->p[0]=MS(si(str)); R z; }

Z V av(a)A a;
{
  I n=a->n-1;
  if (!sym(a)||n>1) R (V)0;
  R sv(n?cxi(XS(*a->p)):Cx,XS(a->p[n]));
}

S symjoin(s1,s2)S s1,s2;{S z;C *st1=s1->n,*st2=s2->n,*buf;
I n1=strlen(st1),n2=strlen(st2);if(strchr(st2,'.'))R s2;
buf=balloc(2+n1+n2);bcopy(st1,buf,n1);buf[n1]='.';
bcopy(st2,buf+(n1+1),n2);buf[1+n1+n2]='\0';z=si(buf);bfree(buf);R z;}

S symsplit(s,pcx)S s,*pcx;{C *src=s->n,*dot=strrchr(src,'.');
if(dot){*dot='\0';*pcx=si(src);*dot='.';R si(dot+1);}else{*pcx=s1("");R s;}}

ENTRYPOINT
ep_scb(a,x) A a,x;
{
  V v=av(a);
  I f=x->p[0],c=x->p[1],i;
  if(x->t!=Et||x->n!=2) ERROUT(ERR_DOMAIN);
  i=qz(f);
  if(!v) ERROUT(ERR_DOMAIN);
  if(!(QF(f)&&!QS(f))&&!i) ERROUT(ERR_NONFUNCTION);
  dc(v->f),v->f=i?0:ic(f),dc(v->c),v->c=ic(c);
  R 0;
}

ENTRYPOINT
A ep_gcb(a) A a;
{
  A z;
  V v=av(a);
  if(!v) ERROUT(ERR_DOMAIN);
  if(!v->f)R 0;
  R z=gv(Et,2),*z->p=ic(v->f),z->p[1]=ic(v->c),(A)z;
}

ENTRYPOINT
ep_spcb(a,x) A a,x;
{
  V v=av(a);
  I f=x->p[0],c=x->p[1],i;
  if(x->t!=Et||x->n!=2) ERROUT(ERR_DOMAIN);
  i=qz(f);
  if(!v) ERROUT(ERR_DOMAIN);
  if(!(QF(f)&&!QS(f))&!i) ERROUT(ERR_NONFUNCTION);
  dc(v->p),v->p=i?0:ic(f),dc(v->q),v->q=ic(c);
  R 0;
}

ENTRYPOINT
A ep_gpcb(a) A a;
{
  A z;
  V v=av(a);
  if(!v) ERROUT(ERR_DOMAIN);
  if(!v->p)R 0;
  R z=gv(Et,2),*z->p=ic(v->p),z->p[1]=ic(v->q),(A)z;
}

ENTRYPOINT
ep__srcb(a,x) A a,x;
{
  V v=av(a);
  I f=x->p[0],c=x->p[1],i;
  if(x->t!=Et||x->n!=2) ERROUT(ERR_DOMAIN);
  i=qz(f);
  if(!v) ERROUT(ERR_DOMAIN);
  if(!(QF(f)&&!QS(f))&&!i) ERROUT(ERR_NONFUNCTION);
  dc(v->rff),v->rff=i?0:ic(f),dc(v->rfc),v->rfc=ic(c);
  R 0;
}

ENTRYPOINT
A ep__grcb(a) A a;
{
  A z;
  V v=av(a);
  if(!v) ERROUT(ERR_DOMAIN);
  if(!v->rff)R 0;
  R z=gv(Et,2),*z->p=ic(v->rff),z->p[1]=ic(v->rfc),(A)z;
}

ENTRYPOINT
ep__sprcb(a,x) A a,x;
{
  V v=av(a);
  I f=x->p[0],c=x->p[1],i;
  if(x->t!=Et||x->n!=2) ERROUT(ERR_DOMAIN);
  i=qz(f);
  if(!v) ERROUT(ERR_DOMAIN);
  if(!(QF(f)&&!QS(f))&&!i) ERROUT(ERR_NONFUNCTION);
  dc(v->rpf),v->rpf=i?0:ic(f),dc(v->rpc),v->rpc=ic(c);
  R 0;
}

ENTRYPOINT
A ep__gprcb(a) A a;
{
  A z;
  V v=av(a);
  if(!v) ERROUT(ERR_DOMAIN);
  if(!v->rpf)R 0;
  R z=gv(Et,2),*z->p=ic(v->rpf),z->p[1]=ic(v->rpc),(A)z;
}

ENTRYPOINT
A ep_scd(a,cd) A a, cd;
{ A z;
  V v=av(a);
  if (!QA(cd)) ERROUT(ERR_DOMAIN);
  if(!v) ERROUT(ERR_DOMAIN);
  z=v->cd;
  v->cd=(A)ic(cd);
  R z;
}

ENTRYPOINT
A ep_gcd(a) A a;
{
  V v=av(a);
  if(!v) ERROUT(ERR_DOMAIN);
  R (A)(v->cd?ic(v->cd):0);
}

ENTRYPOINT
A ep__sscd(a,cd) A a, cd;
{
  A z;
  V v=av(a);
  if(!QA(cd)) ERROUT(ERR_DOMAIN);
  if(!v) ERROUT(ERR_DOMAIN);
  z=v->scd;
  v->scd=(A)ic(cd);
  R z;
}

ENTRYPOINT
A ep__gscd(a) A a;
{
  V v=av(a);
  if(!v) ERROUT(ERR_DOMAIN);
  R (A)(v->scd?ic(v->scd):0);
}

Z nt[]={1,2,3,3,3,4};
Z C *vt[]={"cxs","vars","fns","ops","xfs"};

/* Z V ct(a)A a;{S s=a->n?XS(*a->p):0;R!s?Cx:cxi(s);} */
Z CX ct(a)A a;{S s=(QA(a)&&Et==a->t&&1==a->n)?(S)(*a->p):0;
              R(0==a->n)?Cx:(s&&QS(s))?cxi(XS(s)):0;}

ENTRYPOINT
A ep_nc(c,s)A c;{V v;CX cv=ct(c);A z=gs(Et);if(!cv) ERROUT(ERR_DOMAIN);
  v=sv(ct(c),XS(s));R *z->p=MS(s1(v->e?"deps":v->a?vt[nt[v->t]]:"null")),z;}

/*******************************************************************/

ENTRYPOINT
A ep_def(a) A a;
{
  V v=av(a);
  if(!v) ERROUT(ERR_DOMAIN);
  R (a=(A)v->e)?(A)gsv(0,a->p[a->n+1]):(A)gz();
}

ENTRYPOINT
A ep_dep(a) A a;
{
  V v=av(a),vl; I *l,n=0; A result;
  if(!v) ERROUT(ERR_DOMAIN);
  for(l=v->l;l;l=(I*)*l)++n;
  result=gv(Et, n); n=0;
  for(l=v->l;l;l=(I*)*l)
    {vl=(V)l[1];result->p[n++]=MS(symjoin(vl->cx->s,vl->s));}
  R result;
}

ENTRYPOINT
A ep_alldep(a) A a;
{
  V v=av(a), *vvec, xv; I *l, idx=0, count=0, i, j, notin, **lvec;
  A result; struct buff *pb;
  if (!v) ERROUT(ERR_DOMAIN);
  if (0==(l=v->l)) R (A)gz();
  pb=buffalloc();
  for (l=v->l;l;l=(I*)*l) {
    buffputlong(pb,l); count++;
  }
  lvec=(I **)(pb->min);
/* buffstuff(pb,l+1,sizeof(I)*(count=*l)); */
  while(idx<count) {
    l=lvec[idx++];
    if (v==(xv=(V)l[1])) continue;
    for(l=xv->l;l;l=(I*)*l) {
      for(j=0,notin=1;notin && j<count;++j) if(lvec[j][1]==l[1]) notin=0;
      if (notin) {
        buffputlong(pb,l); count++;
        lvec=(I **) (pb->min);
      }
    }
  }
  result=gv(Et, count);
  vvec=(V *)(pb->min);
  DO(count,xv=(V)lvec[i][1];result->p[i]=MS(symjoin(xv->cx->s,xv->s)));
  R result;
}

/*******************************************************************/

I coreLimGet()
{
  struct rlimit r;
  getrlimit(RLIMIT_CORE,&r);
  R r.rlim_cur;
}

void coreLimSet(n) I n;
{
  struct rlimit r;
  getrlimit(RLIMIT_CORE,&r);
  r.rlim_cur = (n<r.rlim_max)?n:r.rlim_max;
  setrlimit(RLIMIT_CORE,&r);

  R;
}

/*******************************************************************/

Z I stdinFlag = 1;

void stdinFlagSet(n) I n;
{
  stdinFlag =n;
  if (stdinFlag) enable(); else disable();
  R;
}

/*******************************************************************/

Z I dymeVal = -1;

void dymeSet(n) I n;
{
        dymeVal = n;
        R;
}

/*******************************************************************/

Z I phaseOfReleaseVal = -1;

void phaseOfReleaseSet(n) I n;
{
  phaseOfReleaseVal = n;
  R;
}

/*******************************************************************/

Z I majorReleaseVal = -1;

void majjorReleaseSet(n) I n;
{
  majorReleaseVal = n;
  R;
}

/*******************************************************************/

Z I minorReleaseVal = -1;

void minorReleaseSet(n) I n;
{
  minorReleaseVal = n;
  R;
}

/*******************************************************************/

Z A versVal=(A)0;


A versGet()
{
  R (A)((versVal==(A)0)?gsv(0,"Version not set"):ic(versVal));
}

void versSet(str) C *str;
{
  if(versVal!=(A)0) dc(versVal);
  versVal=(A)gsv(0,str);
  R;
}

/*******************************************************************/

Z A relCodeVal=(A)0;

A releaseCodeGet()
{
  R (A)((relCodeVal==(A)0)?gsv(0,"Release Code not set"):ic(relCodeVal));
}

void releaseCodeSet(str) C *str;
{
  if (relCodeVal!=(A)0) dc(relCodeVal);
  relCodeVal=(A)gsv(0,str);
  R;
}

/*******************************************************************/

Z C *SysVarList[] = { "dyme", "vers", "pp", "mode", "stop", "Df", "Ff",
                        "Sf", "Tf", "Xf", "cs", "fl", "stdin", "corelim",
                        "phaseOfRelease", "maforRelease", "minorRelease",
                        "releaseCode", "language", "Ef",
            (char *)0 };

Z C *Mode[] = { "ascii", "apl", (char *)0 };

Z C *Phase[] = { "unset", "devwork", "dev", "maintwork", "maint",
                   "alpha", "bega", "prod", "offtrack", (char *)0};

Z C *getname(aname) A aname;
{
  C *name;
  if (Ct==aname->t) name=(C *)aname->p;
  else if(Et==aname->t && QS(aname->p[0])) name=XS(aname->p[0])->n;
  else name=(C *)0;
  R name;
}

ENTRYPOINT
A ep_gsv(aname) A aname;
{
  C *name=getname(aname);
  A z;

  if(name==(C *)0) ERROUT(ERR_TYPE);

  switch(lu(name,SysVarList)) {
    CS(1, R (A)gi(dymeVal));
    CS(2, R versGet());
    CS(3, R (A)gi(atoi(Fs+3))); /* pp */
    CS(4, R gsym(APL?"apl":"ascii")); /* mode */
    CS(5, R (A)gi(sq)); /* stop */
    CS(6, R (A)gi(Df));
    CS(7, R (A)gi(Gf));
    CS(8, R (A)gi(Sf));
    CS(9, R (A)gi(Tf));
    CS(10, R (A)gi(Xf));
    CS(11, z=gs(Et); *z->p=MS(Cx->s); R z;);
    CS(12, ERROUT(ERR_DOMAIN);); /* rl */
    CS(13, R (A)gi(stdinFlag));
    CS(14, R (A)gi(coreLimGet()));
    CS(15, R (A)gsym(Phase[phaseOfReleaseVal]));
    CS(16, R (A)gi(majorReleaseVal));
    CS(17, R (A) gi(minorReleaseVal));
    CS(18, R releaseCodeGet());
    CS(19, R gsym("aplus")); /* language */
    CS(20, R (A)gi(Ef));
  default: ERROUT(ERR_DOMAIN); break;
  }
}

#ifdef _AIX
#define FtItCHK(aval,maxint) \
 if (1!=aval->n) ERROUT(ERR_LENGTH); \
 if (Ft==aval->t) \
    ival=(((double)maxint)<(*(F *)(aval->p))) ? \
         maxint : (int)nearest(*(F *)(aval->p)); \
 else if (It==aval->t) ival=*aval->p; \
 else ERROUT(ERR_TYPE); \
 if(0>ival) ERROUT(ERR_DOMAIN);
#else
#define FtItCHK(aval,maxint) \
 if (1!=aval->n) ERROUT(ERR_LENGTH); \
 if (Ft==aval->t) \
    ival=(((double)maxint)<(*(F *)(aval->p)))?maxint:(int)rint(*(F *)(aval->p)); \
 else if (It==aval->t) ival=*aval->p; \
 else ERROUT(ERR_TYPE); \
 if (0>ival) ERROUT(ERR_DOMAIN);
#endif

#define ItCHK(aval) if (It!=aval->t) ERROUT(ERR_TYPE); \
                       if (1!=aval->n) ERROUT(ERR_LENGTH); \
                       if (0>(ival=*aval->p)) ERROUT(ERR_DOMAIN);

#define RtCHK(aval,range) ItCHK(aval); if(range<ival)ERROUT(ERR_DOMAIN);

#define NmCHK(aval) if ((cval=getname(aval))==(C *)0) ERROUT(ERR_TYPE);

ENTRYPOINT
A ep_ssv(aname, aval) A aname, aval;
{
  C *name=getname(aname), *cval;
  I ival, rc;

  if (name==(C *)0) ERROUT(ERR_TYPE);

  switch(lu(name,SysVarList)) {
    CS(1, ERROUT(ERR_DOMAIN)); /* dyme */
    CS(2, ERROUT(ERR_DOMAIN)); /* vers */
    CS(3, ItCHK(aval);Fs[3]='0'+(ival/10)%10;Fs[4]='0'+ival%10;); /* pp */
    CS(4, NmCHK(aval);if(rc=lu(cval,Mode))APL=rc-1;else ERROUT(ERR_DOMAIN));
    CS(5, RtCHK(aval, 2); sq=ival;);
    CS(6, RtCHK(aval, 2); Df=ival;);
    CS(7, RtCHK(aval, 1); Gf=ival;);
    CS(8, RtCHK(aval, 1); Sf=ival;);
    CS(9, RtCHK(aval, 1); Tf=ival; stdinFlagSet(Tf););
    CS(10, RtCHK(aval, 1); Xf=ival;);
    CS(11, NmCHK(aval); Cx=cx(cval););
    CS(12, ItCHK(aval); srandom(ival););
    CS(13, RtCHK(aval, 1); stdinFlagSet(ival););
    CS(14, FtItCHK(aval, RLIM_INFINITY); coreLimSet(ival););
    CS(15, ERROUT(ERR_DOMAIN)); /* phaseOfRelease */
    CS(16, ERROUT(ERR_DOMAIN)); /* majorRelease */
    CS(17, ERROUT(ERR_DOMAIN)); /* minorRelease */
    CS(18, ERROUT(ERR_DOMAIN)); /* releaseCode */
    CS(19, ERROUT(ERR_DOMAIN)); /* language */
    CS(20, RtCHK(aval, 1); Ef=ival;);
  default: ERROUT(ERR_DOMAIN); break;
  }
  R 0;
}

Z C *WaCmdList[] = { "coalesce", "size", "atmp", "avail", "fragcounts",
                       "fragsizes", "info", (char *)0 };

extern I twGet(), ep_all();
A ep_wa(a) A a;
{
  A z, z0;
  I k, n=0, len=MD, *p;
  C *name;
  if (It==a->t || Ft==a->t) {
    if (1 != a->n) ERROUT(ERR_LENGTH);
#ifdef _AIX
    if (Ft==a->t) k=*I)nearest(*(F *)(a->p)); else k=*a->p;
#else
    if (Ft==a->t) k=(I)rint(*(F *)(a->p)); else k=*a->p;
#endif
    if (-1 > k) ERROUT(ERR_DOMAIN);
    if (k>0) R gi(!tmp(k<<20));
    if (-1==k)mc();
    R gc(It,1,len,&len,mz());
  }
  else {
    if (((C *)0)==(name=getname(a))) ERROUT(ERR_TYPE);
    switch(lu(name,WaCmdList)) {
      CS(1, mc(); R gc(It,1,len,&len,mz())); /* coalesce */
      CS(2, R gi(twGet())); /* size*/
      CS(3, R gi(ep_all())); /* atmp */
      CS(4, p=(I *)mz();DO(MD,n+=p[i]*MZ[i])R gi(n<<2)); /* avail */
      CS(5, R gc(It,1,len,&len,mz())); /* fragcounts */
      CS(6, R gc(It,1,len,&len,MZ)); /*fagsizes */
      CS(7, z=gv(Et,3);z0=gv(It,3);p=(I *)mz();DO(MD,n+=p[i]*MZ[i])
         z->p[0]=(I)z0;
         z->p[1]=(I)gc(It,1,len,&len,mz());z->p[2]=(I)gc(It,1,len,&len,MZ);
         z0->p[0]=twGet();z0->p[1]=ep_all();z0->p[2]=n<<2;R z); /* info */
    default: ERROUT(ERR_DOMAIN);
    }
  }
}

/*******************************************************************/

Z C *NlList[] = {"vars", "fns", "ops", "xfs", "sfs", "_sfs", "cxs", "cmds",
                   "deps", "svs", "nl", "wa", 0};

Z A nl_list(cxt, n) CX cxt; I n;
{
  V v; I i,count=0; A result;

  for(i=0;i<cxt->ht->nb;++i)
    for(v=cxt->ht->b[i];v;v=v->v)if(nt[v->t]==n&&v->a) ++count;
  result=gv(Et,count);count=0;
  for(i=0;i<cxt->ht->nb;++i)for(v=cxt->ht->b[i];v;v=v->v)
    if(nt[v->t]==n&&v->a) result->p[count++]=MS(v->s);
  R result;
}

Z A nl_deps(cxt) CX cxt;
{
  V v; I i,count=0; A result;

  for(i=0;i<cxt->ht->nb;++i)for(v=cxt->ht->b[i];v;v=v->v)if(v->e) ++count;
  result=gv(Et,count);count=0;
  for(i=0;i<cxt->ht->nb;++i)for(v=cxt->ht->b[i];v;v=v->v)
    if(v->e)result->p[count++]=MS(v->s);
  R result;
}

Z A nl_sfs()
{
  C **s=xs; I count=0; A result;

  for(;*++s;)if(**s=='_'&&(*s)[1]!='_') ++count;
  result=gv(Et, count);
  for(count=0,s=xs;*++s;)
    if (**s=='_'&&(*s)[1]!='_') result->p[count++]=MS(si(*s));
  R result;
}

Z A nl__sfs()
{
  C **s=xs; I count=0; A result;

  for(;*++s;)if(**s=='_'&&(*s)[1]==')') ++count;
  result=gv(Et, count);
  for(count=0,s=xs;*++s;)
    if (**s=='_'&&(*s)[1]=='_') result->p[count++]=MS(si(*s));
  R result;
}

Z A nl_cxs()
{
  CX cx; I count=0; A result;

  for(cx=Rx;cx;cx=cx->n) ++count;
  result=gv(Et, count);
  for(count=0,cx=Rx;cx;cx=cx->n) result->p[count++]=MS(cx->s);
  R result;
}

Z A nl_names(list) C **list;
{
  C **s; I count; A result;

  for(count=0,s=list;*s;s++) ++count;
  result=gv(Et, count);
  for(count=0,s=list;*s;++s) result->p[count++]=MS(si(*s));
  R result;
}

ENTRYPOINT
A ep_nl(acontext, aname) A acontext, aname;
{
  C *name=getname(aname);
  CX cxt=ct(acontext);
  A z;
  I n=0;

  if (name==(C *)0) ERROUT(ERR_TYPE);
  if (!cxt) ERROUT(ERR_DOMAIN);

  switch(lu(name,NlList)) {
    CS(1, R nl_list(cxt,1)); /* vars */
    CS(2, R nl_list(cxt,2)); /* fns */
    CS(3, R nl_list(cxt,3)); /* ops */
    CS(4, R nl_list(cxt,4)); /* ext */
    CS(5, if(cxt!=Rx)R(A)nl;R nl_sfs()); /* sfs */
    CS(6, if(cxt!=Rx)R(A)nl;R nl__sfs()); /* _sfs */
    CS(7, if(cxt!=Rx)R(A)nl;R nl_cxs()); /* cxs */
    CS(8, if(cxt!=Rx)R(A)nl;R nl_names(cmdsList)); /* cmds */
    CS(9, R nl_deps(cxt)); /* deps */
    CS(10, if(cxt!=Rx)R(A)nl;R nl_names(SysVarList)); /* sv */
    CS(11, if(cxt!=Rx)R(A)nl;R nl_names(NlList)); /* sv */
    CS(12, if(cxt!=Rx)R(A)nl;R nl_names(WaCmdList)); /* wa */
  default: ERROUT(ERR_DOMAIN);
  }
}

/*******************************************************************/

ENTRYPOINT
A ep_load(aname) A aname;
{
  C *name=getname(aname), *rname;
  A z;

  if (name==(C*)0) ERROUT(ERR_TYPE);

  rname=doloadafile(name,0);
  if(rname==(C*)0) {
    #ifdef HAVE_STRERROR
      char *errstr=strerror(errno);
      z=gv(Et,2); z->p[0]=(I)gsym("error");
      z->p[1]=(I)gsv(0,(errstr)?errstr:"unknown system error");
    #else
      z=gv(Et,2); z->p[0]=(I)gsym("error");
      z->p[1]=(I)gsv(0,(errno<sys_nerr)?sys_errlist[errno]:"unknown system error");
    #endif
  }
  else {z=gv(Et,2);z->p[0]=(I)gsym("ok");z->p[1]=gsv(0,rname);free(rname);}
  R z;
}

ENTRYPOINT
A ep_loadrm(aguard, aname) A aguard, aname;
{
  C * name=getname(aname), *guard=getname(aguard), *rname;
  A z;

  if (guard==(C *)0) ERROUT(ERR_TYPE);
  if (name==(C *)0) ERROUT(ERR_TYPE);
  if (strcmp(guard,"delete")) {
    z=gv(Et,2); z->p[0]=(I)gsym("error");
    z->p[1]=gsv(0,"loadrm called without specifying deletion");
    R z;
  }
  rname=doloadafile(name,1);
  if(rname==(C*)0) {
    #ifdef HAVE_STRERROR
      char *errstr=strerror(errno);
      z=gv(Et,2); z->p[0]=(I)gsym("error");
      z->p[1]=(I)gsv(0,(errstr)?errstr:"unknown system error");
    #else
      z=gv(Et,2); z->p[0]=(I)gsym("error");
      z->p[1]=(I)gsv(0,(errno<sys_nerr)?sys_errlist[errno]:"unknown system error");
    #endif
  }
  else {z=gv(Et,2);z->p[0]=(I)gsym("ok");z->p[1]=gsv(0,rname);free(rname);}
  R z;
}

/*******************************************************************/

ENTRYPOINT
A ep_ex(a) A a;
{
  V v=av(a);
  if(!v) ERROUT(ERR_DOMAIN);

  if ((v->a || v->e || v->f || v->c || v->p || v->q || v->cd || v->rff ||
       v->rfc || v->rpf || v->rpc || v->scd) && !v->o)
    { exx(v); R gi(0); }
  else R gi(1);
}

ENTRYPOINT /* exitpoint? :^) */
void ep_exit(rc) I rc;
{
  exit(rc);
}

Z C pwd[MAXPATHLEN+8]="PWD=";
setPWD(){getwd(pwd+4);putenv(pwd);}

ENTRYPOINT
A ep_cd(a) A a;
{
  A z;
  C *name=getname(a);

  if (name==(C *)0) ERROUT(ERR_TYPE);
  if(chdir(*name?name:getenv("HOME"))) {
    z=gv(Et,2); z->p[0]=(I)gsym("error");
    z->p[1]=gsv(0,(errno<sys_nerr)?sys_errlist[errno]:"unknown system error");
  }
  else {setPWD();z=gv(Et,1);z->p[0]=(I)gsym("ok");}
  R z;
}

/*******************************************************************/

extern A SymbolTableHasChainLengths();

ENTRYPOINT
A ep_hashstat(a)A a;
{
  HT ht; A z; I i;V v;
  if (qz(a)) R SymbolTableHashChainLengths();
  if (Et!=a->t||1!=a->n||!QS(*a->p)) ERROUT(ERR_DOMAIN);
  ht=cxi(XS(*a->p))->ht;
  z=gv(It,ht->nb);bzero(z->p,ht->nb*sizeof(I));
  for(i=0;i<ht->nb;++i)for(v=ht->b[i];v;v=v->v)z->p[i]++;
  R z;
}

void nsfInstall()
{
  install(ep_nc,"_nc", A_, 2, A_, V_);
  install(ep_scb,"_scb", V_, 2, A_, A_);
  install(ep_gcb,"_gcb", A_, 1, A_);
  install(ep_spcb,"_spcb", V_, 1, A_, A_);
  install(ep_gpcb,"_gpcb", A_, 1, A_);
  install(ep__srcb,"__srcb", V_, 2, A_, A_);
  install(ep__grcb,"__grcb", A_, 1, A_);
  install(ep__sprcb,"__sprcb", V_, 2, A_, A_);
  install(ep__gprcb,"__gprcb", A_, 1, A_);
  install(ep_scd,"_scd", A_, 2, A_, A_);
  install(ep_gcd,"_gcd", A_, 1, A_);
  install(ep__sscd,"__sscd", A_, 2, A_, A_);
  install(ep__gscd,"__gscd", A_, 1, A_);
  install(ep_gsv,"_gsv", A_, 1, A_);
  install(ep_ssv,"_ssv", A_, 2, A_, A_);
  install(ep_nl,"_nl", A_, 2, A_, A_);
  install(ep_def,"_def", A_, 1, A_);
  install(ep_dep,"_dep", A_, 1, A_);
  install(ep_alldep,"_alldep", A_, 1, A_);
  install(ep_load,"_load", A_, 1, A_);
  install(ep_loadrm,"_loadrm", A_, 2, A_, A_);
  install(ep_ex,"_ex",A_,1, A_);
  install(ep_exit,"_exit", V_, 1, IV);
  install(ep_cd,"_cd", A_, 1, A_);
  install(ep_hashstat, "_hashstat", A_, 1, A_);
  install(ep_wa,"_was", A_, 1, A_);
  install(ep_hashstat,"_hashstat", A_, 1, A_);
  install(ep_wa,"_wa", A_, 1, A_);
  R;
}

