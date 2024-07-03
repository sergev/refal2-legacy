/*------------------file----CGOP.C--------------------*/
/*    generation of the assembly language operators   */
/*          Last edition date : 11.11.2004 (BLF)      */
/*----------------------------------------------------*/
/* #define PRCODE */ /* BLF */
#include "refal.def"
struct linkti {
   short tagg;
   union {
      char infoc;
/*      long coden;*/
      char *codef;
   } infoo;
};
struct _TAG {
   char b1;
   char b2;
};
extern void jbyte();
extern void j3addr();
extern void gsymbol();

/*void gop (k)  char k; {
#ifdef PRCODE
 prcode(k);
#endif
   jbyte(k);
}*/
void gopn( k, n) char k, n;  {
#ifdef PRCODE
 prcode(k); printf ("  %d", (int)n );
#endif
   jbyte(k);
   jbyte(n);
}
void gopnm( k , n , m)  char k, n, m ;  {
#ifdef PRCODE
 prcode(k); printf ("  %d %d", (int) n, (int) m );
#endif
   jbyte(k);
   jbyte(n);
   jbyte(m);
}
void gopl( k, l)  char k, *l;  {
#ifdef PRCODE
 prcode(k); printf (" %lx", l );
#endif
#ifdef PDP
   jvir();  /* vyravnivanie */
#endif
   jbyte(k);
   j3addr(l);
}
void gsymbol(code) struct linkti *code; {
 struct _TAG *q;
 char *r;
 register i;
   q = (struct _TAG *) &(code->tagg);
   jbyte( q->b1 );
   jbyte( q->b2 );
   if (code->tagg == 2) {
      j3addr(code->infoo.codef);
      return;
/*      jbyte( '\0' ); jbyte( '\0' );  return; - for no LARGE IBM_PC */
   };
   r = (char *) &(code->infoo.codef);
   if (code->tagg == 0) {
      jbyte(*r);  jbyte(*(r+1));
#ifndef PDP
      jbyte( '\0' );    jbyte( '\0' );
#endif
   }
   else  for (i=0; i<LBLL;i++)  jbyte(*(r+i));
   return;
}
void gops( k, code)  char k;  struct linkti *code; {
#ifdef PRCODE
 prcode(k); prstruct(code);
#endif
#ifdef PDP
   jvir();  /* vyravnivanie */
#endif
   jbyte(k);
   gsymbol(code);
}
void ghw( h )  short h; {
struct _TAG *po;
  po = (struct _TAG *) &h;   /*  eg */
  jbyte(po->b1);
  jbyte(po->b2);
}
