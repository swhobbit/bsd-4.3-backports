#ifndef __STDLIB_H__
#define __STDLIB_H__

/*------------------------------------------------------------------- */
/*                            stdlib.h                                */
/*                                                                    */
/*            Hand rolled stdlib.h file for BSD 4.3 to use with       */
/*            its ancient (pre-GCC) C compiler (cc).                  */
/*                                                                    */
/*            Function list is from                                   */ 
/*            https://en.wikibooks.org/wiki/C_Programming/stdlib.h    */
/*                                                                    */
/*            Definitions are based on man pages for various          */
/*            functions (which exist in man pages but not include     */
/*            files.) Items on the reference web page which do        */
/*            exist in man pages on BSD 4.3 are ommitted from this    */
/*            file.                                                   */
/*                                                                    */
/*                Date: 12 Sep 2024                                   */
/*              Author: ahd@kew.com (Drew Derbyshire)                 */
/*             Address: Kendra Electronic Wonderworks                 */
/*                      Kenmore, WA                                   */
/*------------------------------------------------------------------- */

     double atof(nptr)
     char *nptr;

     atoi(nptr)
     char *nptr;

     long atol(nptr)
     char *nptr;

     srand(seed)
     int seed;

     int rand();

     long random();

     srandom(seed)
     int seed;

     char *initstate(seed, state, n)
     unsigned seed;
     char *state;
     int n;

     char *setstate(state)
     char *state;

     char *malloc(size)
     unsigned size;

     free(ptr)
     char *ptr;

     char *realloc(ptr, size)
     char *ptr;
     unsigned size;

     char *calloc(nelem, elsize)
     unsigned nelem, elsize;

     char *alloca(size)
     int size;

     void abort();

     _exit(status)
     int status;


#ifndef exit 
#define exit(status) _exit(status)
#endif 

     char *getenv(name)
     char *name;

     int system(string)
     char *string;

     qsort(base, nel, width, compar)
     char *base;
     int (*compar)();

     int abs(i)
     int i;

     typedef unsigned int size_t;

#endif
