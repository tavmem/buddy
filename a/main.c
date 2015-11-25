/*LINTLIBRARY*/
char what_atw_a_main_c[]="@(#) $Id: main.c,v 1.3 1992/09/04 16:44:31 dff Exp $";
#include <string.h>
#include <stdio.h>
#include <errno.h>
extern long strtol();  /* should be declared in a strtol.h */
extern void pr();
extern int ai();
#include "../dap/args.h"
#include "f.h"
extern void verSet();
extern I Tf;

/* internal macro declarations */
#define BANNER "A+"
#define COPYRIGHT \
                "Copyright (C) 1990,1991,1992 Morgan Stanley Group Inc."
#define VERSION "Arthur's"
#define DFLT_ATREE \
                "/usr/local/a+_1"

/* internal function declaration */
Z void printId();
Z I parseargs();
Z void ignore_dup();
Z void argvInstall();
Z void getm();

/* internal data declarations */
Z C *usage;
Z I _load_s;
Z I _workarea;

/* internal data definitions */
Z C *usage = "usage: a+ [-s] [-w workarea] [script [scriptargs]]/n";
Z I _load_s;
Z I _workarea;
Z I m=1;
Z C *_banner = BANNER;
Z C *_copyright = COPYRIGHT;
Z C *_version = (char *)0;

I main(argc, argv)
I argc;
C **argv;
{
       Z C *banner = BANNER;
       Z C *copyright = COPYRIGHT;
       Z C *version = VERSION;
       I i; /* the number of arguments parsed */

       printId(banner, copyright, version);
       i = parseargs(argc, argv);
       ai(_workarea);                              /* initialize */
       versSet(VERSION);
       argvInstall(argc, argv, i);                 /* set up _argv */
       if (i < argc && argv[i] && * argv[i])
               loadafile(argv[i],0);               /* load script */
       if (Tf) pr();                               /* initial prompt */
       for (;;) getm();                            /* main loop */
}

Z I argfirst(argc,argv){R 0;}

typedef void (*VPF) ();
Z FILE *_Warnfp = (FILE *)2;
Z void _DefaultWarnFunc(char *s){
  fputs(s, _Warnfp);
  /* Lexa redefines fflush in stdio.h which results in an unresolved symbol */
  #if defined(__edgfe) && defined(fflush)
  #undef fflush
  #endif
  fflush(_Warnfp);}
static VPF _WarnFunc = _DefaultWarnFunc;
#define	MAXERRSIZE	BUFSIZ

Z C *fixit(int errnum, char *s, char r[])
{
  char *z, *p = r, *cp = s, *str, ctimebuf[60];
  //static struct timeval tp;
  //static struct timezone tzp;

  while (cp && *cp != (char) NULL) {
    if (p == &r[MAXERRSIZE - 1])
      return ("bark!\n");
    if (*cp == '%')
      switch (*(cp + 1)) {

	/* quoted `%' */
      case '%':
	*p++ = *cp++;
	*p++ = *cp++;
	break;

	/* error string a la syslog(3) */
      case 'm':
	if (errnum < 1 || errnum > sys_nerr)
	  str = "unknown error";
	else
#ifdef HAVE_STRERROR
          str = strerror(errnum);
#else
	  str = sys_errlist[errnum];
#endif
	for (z = str; *z != (char) NULL &&
	     p < &r[MAXERRSIZE - 1]; *p++ = *z++);
	cp += 2;
	break;

    
	/* timestamp */
//     case 't':
//	if (gettimeofday(&tp, &tzp) < 0)
//	  str = "(time?) ";
//	else {
//         #if defined(__SUNPRO_C)
//          str = ctime_r(&tp.tv_sec,ctimebuf,sizeof(ctimebuf));
//         #else
//          /* For linux ctimebuf must be at least 26 */
//          str = ctime_r(&tp.tv_sec,ctimebuf);
//        #endif
//	  str[19] = '\0';
//	}
    

	for (z = str + 4; *z != (char) NULL &&
	     p < &r[MAXERRSIZE - 1]; *p++ = *z++);
	cp += 2;
	break;

	/* normal for _doprnt */
      default:
	*p++ = *cp++;
	break;
      }
    else
      *p++ = *cp++;
  }
  *p = (char) NULL;
  return (r);
}

void Warn(char *fmt,...){char r[MAXERRSIZE];char _ErrBuf[2 * MAXERRSIZE];
 if(_WarnFunc != (VPF) NULL) { int errnum = errno;va_list ap;
 fmt=(C*)fixit(errnum, fmt,r);
 //va_start(ap, fmt);
 (void)vsprintf(_ErrBuf, fmt, ap);
 //va_end(ap);
 (_WarnFunc) (_ErrBuf); }R;}

Z I parseargs(argc, argv)
register I argc;
register C *argv[];
{
       I isinvalid = 0;
       C *optlist = "w:s";
       I wflag = 0, sflag = 0;
       I c;
       C *ep;                   /* points to end of option argument */
       C *cp;

       if (argfirst(argc, argv) != 0)
       {
              Warn("%t usage: argument list is empty\n");
              isinvalid = 1;
       }

       while ((c = arggetopt(argc, argv, optlist)) != -1)
       {
              switch (c)
              {
              case 's':
                      if (sflag == 0)
                      {
                              sflag = 1;
                              _load_s = 0;
                      }
                      else ignore_dup(c);
                      break;
              case 'w':
                      if (wflag == 0)
                      {
                              wflag = 1;
                              _workarea = (I)strtol(args_value, &ep, 10);
                              if ((*ep != '\0') || (_workarea < 1))
                              {
                                      Warn("%t usage :'%s' is invalid workarea size\n",
                                                      args_value);
                                      isinvalid = 1;
                              }
                      }
                      else ignore_dup(c);
                      break;
              default:
                      Warn("%t usage: -%c is an unknown option\n", c);
                      isinvalid = 1;
                      break;
              }
       }

       /* check for presence of required options */

       if (isinvalid)
       {
               Exit(1, usage);
       }

       /* set up defaults as necessary */
       if (sflag == 0) _load_s = 1;
       if (wflag == 0) _workarea = 4;

       R args_index;
}

Z void ignore_dup(c)
register I c;
{
        Warn("%t usage: duplicate -%c option ignored\n", c);
}

Z A get(x,s)C *s;{A r=(A)gsv(x,s);r->r=1;R r;}
void argvInstall(argc, argv, offset)
I argc;
C **argv;
I offset;
{
  A aobj; V v; I i=0;

  if (argc < offset) { argv += argc; argc = 0; }
  else { argv += offset; argc -= offset; }
  aobj = gv(Et, argc);
  while (argc--) aobj->p[i++] = Iget(0, *argv++);
  v = vi(si("_argv"), Rx);
  if (v->a) dc(v->a);
  v->a = (I)aobj; v->t=0;
  R;
}

static void printId(void)
{
        if (_banner != (char *)(0))
                fprintf(stderr, "     %s\n", _banner);
        if (_copyright != (char *)(0))
                fprintf(stderr, "     %s\n", _copyright);
        if (_version != (char *)(0))
                fprintf(stderr, "     This version is %s\n", _version);
        fflush(stderr);
}

/* CALL OUTS GOT TO GO */
void dst(v_)V v_;{}
void xf(){}
void xup(v,d,i,p,r){} /* update variable on screen */
I vfy(v,a)V v;A a;{R a->n!=7;}
void disable (){m&=~1;}
void enable(){m|=1;}

/* MAIN LOOP BODY */
Z void getm(){I n=m;
 if(-1==select(32,&n,0,0,0)&&Tf)NL,sbi(),pr();else if (n&1)tf();}

