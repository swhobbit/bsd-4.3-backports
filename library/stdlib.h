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

#include <sys/types.h>

     double atof();

     atoi();

     long atol();

     srand();

     int rand();

     long random();

     void srandom();

     char *initstate();

     char *setstate();

     char *malloc();

     free();

     char *realloc();

     char *calloc();

     char *alloca();

     void abort();

     _exit();


#ifndef exit 
#define exit() _exit()
#endif 

     char *getenv();

     int system();

     qsort();

     int abs();

	/* 
		perror() should be defined in errno.h; the file exists in
		BSD 4.3.s, but the method is missing.
	 */

	 void perror();

#endif
