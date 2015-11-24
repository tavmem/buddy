#include "f.h"
dot(){}
undot(){}
dbg(){}
trc(){}
I dbg_tf,dbg_depth;
pck(i,a)A a;{I z;I t=a->t;R t==Et&&(z=a->p[i],!QF(z))?ic(z):(I)gc(t,0.1,0,(C*)a->p+T(i));}
Z pchk(n,a)A a;{Q(a->r>1,7)Q(a->t!=Et||fsy(a),6)Q((unsigned)n>=a->n,10)R(I)(a->p+n);}
Z pick(a,d,b)A a;I *b;{I *p;R!d?(I)a:(p=(I*)pchk(*b,a))?pick(*p,d-1,b+1):0;}
Z ass(a)A a;{A s=(A)*a->p,d=(A)a->p[1];R a->t==Et&&a->n==2&&QA(s)&&QA(d)&&
 sym(s)&&s->n==d->n&&s->r<2&&d->r<2&&d->t==Et&&!fsy(d);}
Z spck(s,a)A a;{A w=(A)*a->p;Q(!ass(a),9)DO(w->n,if(w->p[i]==s)R i)R q=10,0;}
Z spick(a,w)A a,w;{I i;Q(a->r,7)R i=spck(*a->p,w),q?0:pck(i,w->p[1]);}
H2(pic){if(sym(a))R spick(a,w);I1 if(a->r)R(a=(A)pick(w,a->n,a->p))?ic(a):0;
 Q(w->r!=1,7)Q((unsigned)*a->p>=w->n,10)R pck(*a->p,w);}
Z pk0(v,d,b)I *b;{R!d?v:(v=pchk(*b,un(v)))?pk0(v,d-1,b+1):0;}
pka(p,v)A p,*v;{if(sym(p)){Z b[2]={1};b[1]=spck(*p->p,*v);R q?0:pk0(v,2,b);}
 Q(p->r>1,7)Q(p->t,6)R pk0(v,p->n,p->p);}

/*
H2 (pk){unsigned j,d,k;A p;Q(a->t!=Et,6)Q(a->r>1,7)DO(a->n,p=a->p[i];
 Q(p->t||w->t!=Et,6)Q(p->r>1||p->n!=w->r,7)k=0;
 DO(p->n,j=p->p[i];d=w->d[i];Q(j>=d,10)k=k*d+j)w=w->p[k])
 R ic(w);}

 if(z=(I*)v,p)if(!sym(p)){if(z=(I*)pk0(v,p->n,p->p),!z)R 0;}
  else{*b=1,b[1]=spck(*p->p,*z);if(q)R 0;z=(I*)pk0(v,2,b);}

*/