char what_a_m_c[] = "@(#) $Id: m.c,v 1.45 1993/04/23 15:49:28 atw Exp $";
#include "f.h"
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

extern void coreLimSet();
Z qw;Z sigi(){q=1;}Z sigc(){if(qw)wait(0);}
Z sigv(){qs="segv";err(-1,0);}Z sigb(){qs="bus";err(-1,0);}
Z sigf(){q=9;}matherr(){R 1;}

#if defined(_AIX) || defined(linux)
Z unsigned k1=0X40000000,k2=0x100000;
nan(){}
map(f,i){I junk=0, rc, *p;read(f,&junk,4);
  p=(I *)mmap(0,lseek(f,0,SEEK_END),PROT_READ|(1?PROT_WRITE:0),i&27?MAP_PRIVATE:MAP_SHARED,f,0);
  if(i)p[0]=junk;close(f);R (I)p;}
#else
Z unsigned k1=0x40000000,k2=0x100000;
nan(){ieee_handler("set","invalid",sigf);/*ieee_handler("set","division",sigf);*/}
map(f,i){I p=(I)mmap(0,lseek(f,0,2),PROT_READ|(i?PROT_WRITE:0),i&2?MAP_PRIVATE:MAP_SHARED,f,0);close(f);R p;}
#endif

syst(s)C*s;{I r;qw=0,r=system(s),qw=1,r;if(r==-1)H("%ld\n",r);R r;}
Z struct stat b;gwd(s)C *s;{Z C r[99];Z dev_t d;Z ino_t i;stat(".",&b);
 if(d!=b.st_dev||i!=b.st_ino)d=b.st_dev,i=b.st_ino,qw=0,getcwd(r,99),qw=1;strcpy(s,r);}
sgi(){coreLimSet(0);/*signal(SIGCHLD,sigc);*/signal(SIGPIPE,SIG_IGN);
 signal(SIGINT,sigi);signal(SIGSEGV,sigv);signal(SIGBUS,sigb);nan();}
Z mchk(n,a)A a;{I t=(I)a!=-1&&!a->c&&(t=a->t)<=Ct&&n>=AH+T(a->n);
 if(!t)H("not an `a object\n");R t;}
#define MM 2000
typedef struct{I a,c,n,w;}L;Z L mt[MM];Z mm=0;lds(){}
Z L *ml(a){DO(mm,if(mt[i].a==a)R mt+i)R 0;}wr(a){L *p=ml(a);R p?p->w:0;}
im(a){L *p=ml(a);if(p)++p->c;R a;}
dm(a){L *p=ml(a);if(p&&!--p->c)munmap(a,p->n),p->a=0;}
nmap(a,i){L *p=ml(0);I n=lseek(a,0,2);Q(!mchk(n,a=map(a,i)),9)
 if(!p){if(mm==MM)R H("maplim\n"),q=9,0;p=mt+mm++;}R p->c=1,p->n=n,p->w=i,p->a=a;}
Z f[9],j,k;Z C z[]="/var/atmp/0/aXXXXXX",c[]="/var/atmp/0";

flen(f,n){R ftruncate(f,n);}
Z mkt(b)C *b;{I f=mkstemp(b);unlink(b);strcpy(b+strlen(b)-6,"xxxxxx");
 R fcntl(f,F_SETFD,1|fcntl(f,F_GETFD,0)),f;}
wi(){for(;!access(c,6);z[10]=c[10]='0'+ ++j)f[j]=mkt(z);}
#define mapf(f,o) (I)mmap(k1,k2,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_FIXED,f,0)
Z wsm(m){I p=k1,z=(k+m+j-1)/j*k2;DO(j,flen(f[i],z))
 DO(m,if(-1==mapf(f[k%j],k2*(k/j)))R -1;++k;k1+=k2)R p;}
Z mal(n){I p=(I)malloc(n);if(!p)perr("malloc");R p;}
Z tw;tmp(n){I m,p=j||k?(m=1+(n-1)/k2,n=m*k2,wsm(m)):mal(n);
 R tw+=n,p?(mb(p,n>>2),1):0;}

extern u_long MZ[];
wa(k){I j,n=0,*p;tm(0);if(k>0)R tmp(k<<20);if(k==-2)mc();p=(I*)mz();
 DO(31,j=p[i];n+=j*MZ[i];if(k!=-1)H("%d ",j))if(k!=-1)H("n%u %u: ",tw,ep_all());H("%u\n",n<<2);}

twGet(){R tw;}
ep_all(){I s=0;if(!j)R tw;DO(j,fstat(f[i],&b);s+=512*b.st_blocks)R s;}/*||*/
extern C *index(),*getenv();

Z int unloadable(s,m) C *s; I m;
{
  struct stat ss;
  if(access(s,m))R 1;
  if(stat(s,&ss))R 1;
  if(S_ISDIR(ss.st_mode))R 1;
  R 0;
}

C *pfind(v,d,f,m) C *v,*d,*f;
{
  Z C s[MAXPATHLEN];
  if(*f=='/')R unloadable(f,m)?0:f;
  for((v&&(v=getenv(v)))?d=v:0;d;) {
    if(v=index(d,':'))*s=0,strncat(s,d,v-d),d=v+1;
    else strcpy(s,d),d=0;
    strcat(s,"/"),strcat(s,f);
    if(!unloadable(s,m))R s;
  }
  R 0;
}
