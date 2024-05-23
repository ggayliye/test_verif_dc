/**CFile***********************************************************************

  FileName    [main.c]

  PackageName [ntr]

  Synopsis    [Main program for the nanotrav program.]

  Description []

  SeeAlso     []

  Author      [Kyle G Gayliyev]

  Copyright   [Copyright (c) 1995-2004, Regents of the University of Colorado

  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

  Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  Neither the name of the University of Colorado nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.]

******************************************************************************/

#include "ntr.h"
#include "cuddInt.h"

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/

#define NTR_VERSION\
    "Nanotrav Version #0.12, Release date 2003/12/31"

#define BUFLENGTH 8192

/*---------------------------------------------------------------------------*/
/* Stucture declarations                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/

#ifndef lint
static char rcsid[] UTIL_UNUSED = "$Id: main.c,v 1.38 2004/08/13 18:28:28 fabio Exp fabio $";
#endif

static  char    buffer[BUFLENGTH];
#ifdef DD_DEBUG
extern  st_table *checkMinterms (BnetNetwork *net, DdManager *dd, st_table *previous);
#endif

/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/

/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Static function prototypes                                                */
/*---------------------------------------------------------------------------*/
/*-- Priyank: We don't need any of these--*/
/***************
static NtrOptions * mainInit ();
static void ntrReadOptions (int argc, char **argv, NtrOptions *option);
static void ntrReadOptionsFile (char *name, char ***argv, int *argc);
static char* readLine (FILE *fp);
static FILE * open_file (char *filename, const char *mode);
static int reorder (BnetNetwork *net, DdManager *dd, NtrOptions *option);
static void freeOption (NtrOptions *option);
static DdManager * startCudd (NtrOptions *option, int nvars);
static int ntrReadTree (DdManager *dd, char *treefile, int nvars);
******************/

/**AutomaticEnd***************************************************************/

/*---------------------------------------------------------------------------*/
/* Definition of exported functions                                          */
/*---------------------------------------------------------------------------*/

/**Function********************************************************************

  Synopsis    [Main program for ntr.]

  Description [Main program for ntr. Performs
  initialization. Introduces variables, builds ROBDDs for some
  functions, and prints-out the BDD structure. A sample file given to
  the 5740 class.]

  SideEffects [None]

  SeeAlso     []

******************************************************************************/
int
main(
  int  argc,
  char ** argv)
{
    NtrOptions	*option;	/* options */
    DdManager	*dd;		/* pointer to DD manager */
    int		exitval;	/* return value of Cudd_CheckZeroRef */
    int		ok;		/* overall return value from main() */
    int		result;		/* stores the return value of functions */
    int		i;		/* loop index */
    int		j;		/* loop index */
    double	*signatures;	/* array of signatures */
    int		pr;		/* verbosity level */
    int		reencoded;	/* linear transformations attempted */


    /****** Priyank's additions *******/
    DdNode *one, *zero;
    DdNode *a, *b, *c, *f, *g, *h;
    DdNode *f_b, *f_bbar;
		
    /****** Kyle's additions *******/
    DdNode *ab, *a1, *a2, *fb1, *fb2, *f_ac, *fxnFinal,*f_b1f_bbar1,*f_bXOR, *f_bbarXOR,*fgnot;
    DdNode *fg, *f_AND_g, *f_AND_g_not, *f_OR_g_not, *OR1, *OR2, *l,*k,*m, *n, *m1, *m2,*mOR, *mOR1;
	  DdNode *mOR2, *mXOR, *m2XOR, *mOR_XOR, *mOR1_XOR, *mOR2_XOR,*p1,*p2,*p3,*p4,*p1_1,*p2_1;
    DdNode *p3_1,*p4_1,*p1p2, *p3p4, *o,*q,*x, *y, *z, *w, *w_z_XOR;

   /*********************************/

    /* Initialize manager. We start with 0 variables */

    dd = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);
    /*startCudd(option,net1->ninputs);*/
    if (dd == NULL) { exit(2); }


    /************ lets do our work here *************/
    one = Cudd_ReadOne( dd );
    Cudd_Ref(one); /* referenced for the first time */

    zero = Cudd_Not( one ); /* not the same as Cudd_ReadZero */
    /* Cudd_Ref(zero);*/ 
    /* reference count increment not needed because Cudd_Not returns
       the projection */ 


/******NOTE: To comment-out/in, hold ctrl and click "/".    **********/





// /*------PROBLEM 1---------*/

//     /***** Add a new variable ***********/
//     a = Cudd_bddNewVar(dd);
//     b = Cudd_bddNewVar(dd);
//     c = Cudd_bddNewVar(dd);


// /****Problem 1; Part1. a) ROBDD for Fxn: ab+ac+bc  **/

// /*----------------Create AND Boolean fxn: ---------------*/

// /* Add: f=ab */
// f = Cudd_bddAnd(dd, a, b); 
// Cudd_Ref(f);

// /*  Add: f_ac=ac  */
// f_ac=Cudd_bddAnd(dd,a,c); 
// Cudd_Ref(f_ac);

// /* Add: h=bc  */
// h=Cudd_bddAnd(dd,b,c); 
// Cudd_Ref(h);
// /*----------------END: AND Boolean fxn---------------*/


// /*----------------Create OR Boolean fxn: ---------------*/
// k = Cudd_bddOr(dd, f, f_ac); /*k=ab+ac*/
// Cudd_Ref(k);

// l=Cudd_bddOr(dd,k,h); /*l=ab+ac+bc*/
// Cudd_Ref(l);
// /*----------------END: OR Boolean fxn---------------*/


// //FILE PRINTING for Fxn: ab+ac+bc
// const char* filename1 = "Problem1_part1.ROBDD_4_ab+ac+bc.dot";    
// FILE* outfile1 = fopen(filename1, "w");    
// Cudd_DumpDot(dd, 1, &l, NULL, NULL, outfile1);    
// fclose(outfile1);
// printf("\n********Problem1, Part1. ***********");    
// printf("\n\n => Problem1, part1 ROBDD graph is written to \nthe file: \"%s\"\n", filename1);  	
// printf("---------------------------------\n"); //Empty line



// /****Problem 1; Part1. b) Unate checking in variable "b" (positive or negative unate). Fxn: l= ab+ac+bc . **/

// //POSITIVE and NEGATIVE cofactor w.r.t "b":
// f_b = Cudd_Cofactor(dd, l, b);  /* f_b = +ve cofactor of l w.r.t. b: f_b = l|(b=1; b'=0)= a+c*/
// Cudd_Ref(f_b);    

// f_bbar = Cudd_Cofactor(dd, l, Cudd_Not(b) ); /* f_bbar = -ve cofactor of l w.r.t. b: f_bbar = l|(b=0;b'=1)= ac */
// Cudd_Ref(f_bbar);

// // END: POSITIVE and NEGATIVE cofactor



//    //CREATE AND function to be used to create UNITE functions:
//     m = Cudd_bddAnd(dd, f_b, b ); // m= f_b* b =(a+c)*b
// 	Cudd_Ref(m);

//     m2 = Cudd_bddAnd(dd, f_bbar, Cudd_Not(b) );  // m2= f_bbar* b' =(ac)*b'
// 	Cudd_Ref(m2);


//  //CREATE OR functions (In the meantime, the fxns will be positive and negative unate checking functions): 

//     mOR = Cudd_bddOr(dd, m, f_bbar ); // mOR= (a+c)*b + ac => Positive unate if f= l=mOR=ab+ac+bc;
// 	Cudd_Ref(mOR);


//     mOR1 = Cudd_bddOr(dd, m, m2 ); // mOR1= (a+c)*b + (ac)*b' => Shannon's Expansion.
// 	Cudd_Ref(mOR1);

//     mOR2 = Cudd_bddOr(dd, m2, f_b ); // mOR2= (ac)*b'+ a+c => Negative unate if f= l=mOR2=ab+ac+bc;
// 	Cudd_Ref(mOR2);

//   //END: CREATE OR functions //
  
     
//     printf("\n"); //empty line
//     if(mOR==mOR1) // Checks if (a+c)*b + ac (Positive unate fxn) = (a+c)*b + (ac)*b'(Shannon's Expansion)
//     { 

//         printf(" => Function of [Positive Unate in variable \"b\"] is equal to Shannons Expansion,mOR = mOR1.\nTherefore, it is (ab+ac+bc) a POSITIVe UNATE in \"b\".\n") ;

//      }
//      else
//      {
//         printf(" => Function of [Positive Unate in variable \"b\"] is NOT equal to Shannon's Expansion, mOR != mOR1.\nTherefore, it is (ab+ac+bc) NOT a positive unate in \"b\".\n") ;
        

//      }
   
//     if(mOR2==mOR1) // Checks if ab+ac+bc (Negative unate) = (a+c)*b + (ac)*b'(Shannon's Expansion)
//     { 

//         printf("\n => Function of [Negative Unate in variable \"b\"] is equal to Shannons Expansion, mOR2 = mOR1.\nTherefore, it is (ab+ac+bc) a negative unate in \"b\".\n") ;

//      }
//      else
//      {
//         printf("\n => Function of [Negative Unate in variable \"b\"] is NOT equal to Shannon's Expansion, mOR2 = mOR1.\nTherefore, it is (ab+ac+bc) NOT a negative unate in \"b\".\n") ;
        

//      }
//         printf("\n"); //empty line
//         printf("********END: Problem1, Part1. ***********"); 
//         printf("\n"); //empty line



// /****Problem 1; part2.a) ROBDD for XOR Boolean fxn : "a XOR b XOR c" : ---------------*/

// 	a1=Cudd_bddXor(dd,a,b); //xor of a, b: a1=ab'+a'b. // if fxn name is not declared, you write "DdNode* ab=Cudd_bddXor(dd,a,b);"
// 	Cudd_Ref(a1);

// 	a2=Cudd_bddXor(dd,a1,c); //xor of a,b,c :a2="a1" XOR "c" = (ab'+a'b)* c' + (ab'+a'b)' * c = ab'c' + a'bc' +a'b'c +abc
// 	Cudd_Ref(a2);
 
//  /*----------------END: XOR Boolean fxn---------------*/

// //FILE PRINTING for Fxn: "a XOR b XOR c".
// const char* filename2 = "Problem1_part2.ROBDD_4_XORof_a,b,c.dot";    
// FILE* outfile2 = fopen(filename2, "w");    
// Cudd_DumpDot(dd, 1, &a2, NULL, NULL, outfile2);    
// fclose(outfile2); 
// printf("\n"); //empty line
// printf("\n********Problem1, Part2. ***********");    
// printf("\n\n => Problem1, part2 ROBDD graph is written to \nthe file: \"%s\"\n", filename2 ); 
// printf("---------------------------------\n"); //Empty line


// /****Problem 1; part2. b) Unate checking in variable "b" (positive or negative unate). Fxn: "a XOR b XOR c".  **/

// //POSITIVE and NEGATIVE cofactor w.r.t "b":
// f_bXOR = Cudd_Cofactor(dd, a2, b);  /* f_bXOR = +ve cofactor of l w.r.t. b: f_bXOR = a2|(b=1; b'=0)= (ab'c' + a'bc' +a'b'c +abc)|(b=1;b'=0) =a'c'+ac */
// Cudd_Ref(f_bXOR);    

// f_bbarXOR = Cudd_Cofactor(dd, a2, Cudd_Not(b) ); /* f_bbarXOR  = -ve cofactor of l w.r.t. b: f_bbarXOR  = a2|(b=0;b'=1)= (ab'c' + a'bc' +a'b'c +abc)|(b=0;b'=1) = ac'+a'c  */
// Cudd_Ref(f_bbarXOR);

// // END: POSITIVE and NEGATIVE cofactor  


//  //CREATE AND function to be used to create UNITE functions:  
//     mXOR = Cudd_bddAnd(dd, f_bXOR, b ); //Positive cofactor and "b".  mXOR= f_bXOR*b= (a'c'+ac) * b
// 	Cudd_Ref(mXOR);

//     m2XOR = Cudd_bddAnd(dd, f_bbarXOR, Cudd_Not(b) ); // Negative cofactor and "b'". m2XOR= f_bbarXOR*b' = (ac'+a'c)* b'
// 	Cudd_Ref(m2XOR);

//  //CREATE OR functions (In the meantime, positive and negative unate checking functions will be created): 
//     mOR_XOR = Cudd_bddOr(dd, mXOR, f_bbarXOR ); // mOR_XOR = mXOR+ f_bbarXOR= (a'c'+ac) * b  + (ac'+a'c)=[b+ac'+a'c] => Positive unate if mOR_XOR = a2= ab'c' + a'bc' +a'b'c +abc 
// 	Cudd_Ref(mOR_XOR);

//     mOR1_XOR = Cudd_bddOr(dd, mXOR, m2XOR ); // mOR1_XOR = mXOR+m2XOR=(a'c'+ac) * b  + (ac'+a'c)* b'= [(a'c'b+acb) + (ac'b'+a'cb')] => Shannon's Expansion.
// 	Cudd_Ref(mOR1_XOR);

//     mOR2_XOR = Cudd_bddOr(dd, m2XOR, f_bXOR ); // mOR2_XOR = m2XOR+ f_bXOR= (ac'+a'c)* b'  + (a'c'+ac) = [b+ac+a'c']  => Negative unate if mOR2_XOR=a2= ab'c' + a'bc' +a'b'c +abc 
// 	Cudd_Ref(mOR2_XOR);

//   //END: CREATE OR functions //



//     printf("\n"); //empty line
//     if(mOR_XOR==mOR1_XOR) // Checks if [b+ac'+a'c]  (Positive unate fxn) = [(a'c'b+acb) + (ac'b'+a'cb')] (Shannon's Expansion)
//     { 

//        printf(" => Function of [Positive Unate in variable \"b\"] is equal to \nShannons Expansion,mOR_XOR==mOR1_XOR.Therefore, \nit is (ab'c' + a'bc' +a'b'c +abc) a POSITIVe UNATE in \"b\".\n") ;

//      }
//      else
//      {
//         printf(" => Function of [Positive Unate in variable \"b\"] is NOT equal \nto Shannon's Expansion, mOR_XOR !=mOR1_XOR.Therefore, \nit is (ab'c' + a'bc' +a'b'c +abc) NOT a positive unate in \"b\".\n") ;

//      }

    
//     if(mOR2_XOR==mOR1_XOR)// // Checks if [b+ac+a'c'] (Negative unate fxn) = [(a'c'b+acb) + (ac'b'+a'cb')] (Shannon's Expansion)
//     { 

//        printf("\n => Function of [Negative Unate in variable \"b\"] is equal to \nShannons Expansion, mOR2_XOR==mOR1_XOR.Therefore, \nit is (ab'c'+a'bc'+a'b'c+abc) a NEGATIVE unate in \"b\".\n") ;
//      }
//      else
//      {
//         printf("\n => Function of [Negative Unate in variable \"b\"] is NOT equal \nto Shannon's Expansion, mOR2_XOR!=mOR1_XOR.Therefore, \nit is (ab'c'+a'bc'+a'b'c+abc) NOT a negative unate in \"b\".\n") ;

//      }
//         printf("\n"); //empty line
//         printf("********END: Problem1, Part2. ***********\n"); 
//         printf("********END OF Problem1***********\n"); 
//         printf("\n"); //empty line


// /////////////////////////////////////////////////////////////////





/* NOTE: TO TEST PROBLEM 3, PLEASE COMMENT OUT PROBLEM 1 ABOVE. */




/*-------------Problem 3-------------*/

/***** Add a new variable ***********/
    w = Cudd_bddNewVar(dd);
    z = Cudd_bddNewVar(dd);
	y = Cudd_bddNewVar(dd);
    x = Cudd_bddNewVar(dd);
 
 /*Create AND function combinations:*/
p1 = Cudd_bddAnd(dd, Cudd_Not(w), Cudd_Not(x)); /*  f=w'x'  */
Cudd_Ref(p1);
p1_1 = Cudd_bddAnd(dd, p1, Cudd_Not(z)); /*  f=w'x'z'  */
Cudd_Ref(p1_1);

p2 = Cudd_bddAnd(dd, w, Cudd_Not(x)); /*  f= wx'  */
Cudd_Ref(p2);
p2_1 = Cudd_bddAnd(dd, p2,z); /*  f= wx'z  */
Cudd_Ref(p2_1);

p3 = Cudd_bddAnd(dd, Cudd_Not(w), y); /*  f= w'y */
Cudd_Ref(p3);
p3_1 = Cudd_bddAnd(dd, p3, z); /*  f= w'yz  */
Cudd_Ref(p3_1);

p4 = Cudd_bddAnd(dd, w, y); /*  f= wy  */
Cudd_Ref(p4);
p4_1 = Cudd_bddAnd(dd, p4, Cudd_Not(z)); /*  f= wyz'  */
Cudd_Ref(p4_1);

/*--Create OR fucntion combinations:---------------*/
p1p2= Cudd_bddOr(dd, p1_1, p2_1); /*  p1_1+ p2_1 =w'x'z' +  wx'z  */
Cudd_Ref(p1p2);
p3p4= Cudd_bddOr(dd, p3_1, p4_1); /*  p3_1+ p4_1 =w'yz  +  wyz'  */
Cudd_Ref(p3p4);

// Function's final version :
fxnFinal = Cudd_bddOr(dd, p1p2, p3p4); /*fxnFinal= w'x'z' + wx'z + w'yz + wyz'*/
Cudd_Ref(fxnFinal);
/*----------------END: Create OR combination---------------*/



/*Problem 3, Part 1a. Constructing BDD for the fxnFinal = f=w'x'z' + wx'z + w'yz + wyz' */

//FILE PRINTING for Fxn: fxnFinal = f=w'x'z' + wx'z + w'yz + wyz' 
const char* filename3 = "Problem3_ROBDD_4_f.dot";    
FILE* outfile3 = fopen(filename3, "w");    
Cudd_DumpDot(dd, 1, &fxnFinal, NULL, NULL, outfile3);    
fclose(outfile3);
printf("\n********Problem3, Part1a, Function \"f\". ***********");        
printf("\n\n => Problem3, part1a function f ROBDD graph is written to \nthe file: \"%s\"\n", filename3);  	
printf("---------------------------------\n"); //Empty line


/*---Create fxn g: XOR of w and z : ----*/

	w_z_XOR=Cudd_bddXor(dd,w,z); //xor of w, z : w_z_XOR = w'z+wz'
	Cudd_Ref(w_z_XOR);

 /*--END: Create fxn g: XOR of w and z : ----*/



/*Problem 3, Part 1a. Constructing BDD for the function w_z_XOR = w'z+wz' */

//FILE PRINTING for Fxn:w_z_XOR = w'z+wz'
const char* filename4 = "Problem3_ROBDD_4_g.dot";    
FILE* outfile4 = fopen(filename4, "w");    
Cudd_DumpDot(dd, 1, &w_z_XOR, NULL, NULL, outfile4);    
fclose(outfile4);  
printf("\n********Problem3, Part1a, Function \"g\". ***********");     
printf("\n\n => Problem3, part1a function g ROBDD graph is written to \nthe file: \"%s\"\n", filename4);  	
printf("---------------------------------\n"); //Empty line
//DdNode* Con1=Cudd_bddLeq(dd,fb1,g); */
//DdNode* Con2=Cudd_bddLeq(dd,g,fb1); */


/*----------*/

/*Problem 3, Part 1b. Computing fg and fg' for the functions of fxnFinal = f=w'x'z' + wx'z + w'yz + wyz' and w_z_XOR =g= w'z+wz'. Printing the cofactor functions (Cudd_PrintMinterm)*/

//COMPUTE fg:
fg = Cudd_bddConstrain(dd,fxnFinal, w_z_XOR);// g'=zw+z'w'; fg = fg|(g=1; g'=0) = x'(w'z'+wz) + y(w'z+wz')= x'*(g') + y*(g)= [y]; 
Cudd_Ref(fg);

printf("    **********fg********* \n"); //Empty line
printf("\nPrinting the BDD for fg:\n");  	
Cudd_PrintDebug(dd,fg,3,3);
printf("---------------------------------\n"); //Empty line

//Print MINTERMS of fg
printf("Printing the minterms of fg:\n"); //Empty line
Cudd_PrintMinterm(dd,fg);



//COMPUTE fgnot:
fgnot = Cudd_bddConstrain(dd,fxnFinal, Cudd_Not(w_z_XOR));// g'=zw+z'w'; fgnot=fg'|(g'=1; g=0) = x'(w'z'+wz) + y(w'z+wz')= x'*(g') + y*(g)= [x']; 
Cudd_Ref(fgnot);

printf("\n    **********fgnot********* \n\n"); //Empty line
printf("Printing the BDD for fgnot\n");  	
Cudd_PrintDebug(dd,fgnot,3,3);
printf("---------------------------------\n"); //Empty line

//Print MINTERMS of fgnot
printf("Printing the minterms of fgnot:\n"); //Empty line
Cudd_PrintMinterm(dd,fgnot);
printf("**Equalance means two fxns are the same and pointer points to the same node.**\n"); //Empty line
printf("---------------------------------\n"); //Empty line
/*--------*/


// //////////////

// //USE TO TEST : FILE PRINTING for Test file
// const char* filenameTest = "ROBDD_test1.dot";    
// FILE* outfileTest = fopen(filenameTest, "w");    
// Cudd_DumpDot(dd, 1, &fgnot, NULL, NULL, outfileTest);    
// fclose(outfileTest);  
// printf("\n********TEST***********");     
// printf("\n\n => TEST is written to \nthe file: \"%s\"\n", filenameTest);  	
// printf("---------------------------------\n"); //Empty line

// ////////////////





/*Problem 3, Part 2. /*Problem 3, Test whether the bounds are satisfied for the above functions f,g,fg;*/

//Containment Check: a)Is f*g contained in fg and b)is it contained in (f+g')? Let's check.

/* Data from previous computations:
g= w_z_XOR = w'z+wz';
g'=zw+z'w'; 
f=fxnFinal =w'x'z' + wx'z + w'yz + wyz'= x'(w'z'+wz) + y(w'z+wz')
fg = fg|(g=1; g'=0) = x'(w'z'+wz) + y(w'z+wz')= x'*(g') + y*(g)= [y];
fgnot=fg'|(g'=1; g=0) = x'(w'z'+wz) + y(w'z+wz')= x'*(g') + y*(g)= [x']; 
*/

//CREATE AND function for [f*g]:
f_AND_g = Cudd_bddAnd(dd, fxnFinal, w_z_XOR); // f_AND_g = f * g= fxnFinal* w_z_XOR = (w'x'z' + wx'z + w'yz +wyz') *(w'z+wz') = [yw'z+ywz'];
Cudd_Ref(f_AND_g);

// fg is already compluted previously as : fg = fg|(g=1; g'=0) = x'(w'z'+wz) + y(w'z+wz')= x'*(g') + y*(g)= [y];

//CREATE AND function for [f*g]' :
f_AND_g_not = Cudd_Not(f_AND_g); // f_AND_g_not = (f * g)'= (fxnFinal* w_z_XOR)'=[yw'z+ywz']'=(y'+w+z')*(y'+w'+z)= [y'+wz+z'w'];
Cudd_Ref(f_AND_g_not);

//CREATE OR function for [f+g']:
f_OR_g_not = Cudd_bddOr(dd, fxnFinal, Cudd_Not(w_z_XOR)); // f_OR_g_not = f + g'= fxnFinal+ w_z_XOR'= w'x'z' + wx'z + w'yz + wyz' + zw+z'w'= [y+w'z'+wz];
Cudd_Ref(f_OR_g_not);


//Create a function for  f*g in fg containment check. 

//Create OR function for: (f*g)'+(fg) [will be used to check p'+q=1]:
OR1 = Cudd_bddOr(dd, f_AND_g_not, fg); // OR1 = (f * g)'+ f|g= f_AND_g_not+ fg= [y'+wz+z'w' + y]=1;
Cudd_Ref(OR1);

//Create a function for fg in f+g' containment check. 

//Create OR function for: (fg)' +(f+g')[will be used to check p'+q=1]:

OR2= Cudd_bddOr(dd, Cudd_Not(fg),f_OR_g_not);// OR2= (fg)'+ f_OR_g_not+  = (fg)'+(f + g')= y'+(y+w'z'+wz)= 1 ;
Cudd_Ref(OR2);

printf("---------------------------------\n"); //Empty line


if(OR1==one)  // TESTs if:p'+q=1
{
    printf("\nf_AND_g (f*g) is a generalized cofactor. (f*g) contains in fg. \n");
}
printf("---------------------------------\n"); //Empty line
if(OR2==one)
{
    printf("fg contains in the (f+g\') .\n(According to the variables I used: fg contains in the f_OR_g_not)\n");
}

printf("---------------------------------\n"); //Empty line
printf("********END OF Problem3***********\n\n"); 


/*-------------------*/


Cudd_Quit(dd);   
return 0;



	
		
	
} /* end of main */


/*---------------------------------------------------------------------------*/
/* Definition of internal functions                                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Definition of static functions                                            */
/*---------------------------------------------------------------------------*/
