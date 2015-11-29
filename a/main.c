/*LINTLIBRARY*/
char what_atw_a_main_c[]="@(#) $Id: main.c,v 1.3 1992/09/04 16:44:31 dff Exp $";
#include <string.h>
#include <stdio.h>
#include <errno.h>
extern long strtol();  /* should be declared in a strtol.h */
extern void pr();
extern int ai();
#include <dap/args.h>
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

       if (argsfirst(argc, argv) != 0)
       {
              Warn("%t usage: argument list is empty\n");
              isinvalid = 1;
       }

       while ((c = argsgetopt(argc, argv, optlist)) != -1)
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
Z A gst(I x,C* s){A r=(A)gsv(x,s);r->r=1;return r;}
void argvInstall(argc, argv, offset)
I argc;
C **argv;
I offset;
{
  A aobj; V v; I i=0;

  if (argc < offset) { argv += argc; argc = 0; }
  else { argv += offset; argc -= offset; }
  aobj = gv(Et, argc);
  while (argc--) aobj->p[i++] = (I)gst(0, *argv++);
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

