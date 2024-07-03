/*-----------  file  --  XAPPLY.C ------------*/
/*                 MO: apply                  */
/*       Last modification : 03.07.2004 (BLF) */
/*--------------------------------------------*/
#include <stdio.h>
#include "refal.def"
extern REFAL refal;

st *malloc();
void (*dba)(st*)=NULL;

static void appl_() {
 st *s_st, *upst;
 linkcb *px,*pk,*pd;
#ifdef IBM_PC

/* BLF 03.07.2004 
 #ifdef QC
 int  l=stackavail();
   if (l < 500)
#else
*/
  long l=(long) &s_st;  
/*   printf("\nl=%lx",l);*/
   if( (l & 0xffffL)<200L )
/* BLF 03.07.2004 
#endif
*/
#endif
   { /* printf("\nStack overflow!");*/ goto LACK;}
   upst = refal.currst;
   if( !slins(refal.prevr,1) ) return;
   px = refal.prevr->next;
   if( (s_st=malloc(sizeof(st)))==NULL ) goto LACK;
   if( !lcre(s_st)) goto LACK;
   if( !lins(s_st->view,2)) {
     rfcanc(s_st);
     goto LACK;
   }
   pk = s_st->view->next;
   pd = pk->next;
   pk->info.codep = NULL;
   pk->tag = TAGK;
   pd->info.codep = pk;
   pd->tag = TAGD;
   s_st->dot = pd;
   rftpl(pk,refal.preva,refal.nexta);
   rftpl(s_st->store,upst->store,upst->store);
   s_st->step= ++upst->step;
/*   printf("\nEnter: %ld",upst->step); */
   s_st->stop = 0x7FFFFFFFl;
   do {
      if(dba==NULL) rfrun(s_st);     /* net prokrutki */
      else         (*dba)(s_st);    /* prokrutka vkluchena */
      if (s_st->state == 3)
      if (lincrm()) s_st->state = 1;
   } while ((s_st->state == 1) && (s_st->dot != NULL));
   rftpl(upst->store,s_st->store,s_st->store);
   upst->step= --s_st->step;
/*   printf("\nOut: %ld %lx",upst->step,upst);  */
   switch (s_st->state) {
     case 1:
	  px->info.infoc = 'N';
          rftpl (px,s_st->view,s_st->view);
          break;
     case 2:
          px->info.infoc = 'R';
          pd = s_st->dot;
          pk = pd->info.codep;
          rftpl(px,pk,pd);
          break;
     case 3:
          px->info.infoc = 'S';
          break;
   }
   rfcanc(s_st);
   free(s_st);
   return;
LACK: refal.upshot = 3; return; 
}
static char appl_0[] = { Z5  'A','P','P','L','Y','\005'};
G_L_B char apply = '\122';   static void (*appl_1)() = appl_;  

/*----------  end of file XAPPLY.C  -----------*/
