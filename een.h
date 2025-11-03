/* EEN - Minimal C Test Library - 0.3.0
 *
 * Copyright (c) 2014-2021 Lewis Van Winkle
 * Copyright (c) 2025 Bradley Jones
 *
 * http://CodePlea.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgement in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution. */

/* EEN - Wee unit testing for C
 *
 * Example:
 *
 *      void test1()
 *      {
 *        lok('a' == 'a');
 *      }
 *
 *      void test2()
 *      {
 *        lequal(5, 6);
 *        lfequal(5.5, 5.6);
 *      }
 *
 *      int main()
 *      {
 *        lrun("test1", test1);
 *        lrun("test2", test2);
 *        lresults();
 *        return lfails != 0;
 *      }
 *
 * Hints:
 *      All functions and variables start with the letter 'l'. */

#ifndef __EEN_H__
#define __EEN_H__

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

/* How far apart can floats be before we consider them unequal. */
#ifndef LTEST_FLOAT_TOLERANCE
#define LTEST_FLOAT_TOLERANCE 0.001
#endif

/* Track the number of passes, fails.
 * NB this is made for all tests to be in one file. */
static size_t ltests = 0;
static size_t lfails = 0;

/* Display the test results.
 * Since C90 lacks the %zu format specifier for printf(), we need to
 * cast the rest results to an unsigned long before displaying
 * them. */
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#define lresults() do {\
    if (lfails == 0) {\
        printf("ALL TESTS PASSED (%zu/%zu)\n", ltests, ltests);\
    } else {\
        printf("SOME TESTS FAILED (%zu/%zu)\n", ltests-lfails, ltests);\
    }\
} while (0)
#else
#define lresults() do {\
    if (lfails == 0) {\
        printf("ALL TESTS PASSED (%lu/%lu)\n",\
		 (unsigned long)ltests, (unsigned long)ltests);\
    } else {\
      printf("SOME TESTS FAILED (%lu/%lu)\n",\
	     (unsigned long)ltests-lfails, (unsigned long)ltests);\
    }\
} while (0)
#endif

/* Run a test. Name can be any string to print out; test is the
 * function name to call. */
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#define lrun(name, test) do {			\
    const size_t ts = ltests;\
    const size_t fs = lfails;\
    const clock_t start = clock();\
    printf("\t%s:\n", name);\
    test();\
    printf("\t -- pass: %-20zu fail: %-20zu time: %ldms\n",\
            (ltests-ts)-(lfails-fs), lfails-fs,\
            (long)((clock() - start) * 1000 / CLOCKS_PER_SEC));\
} while (0)
#else
#define lrun(name, test) do {\
    const size_t ts = ltests;\
    const size_t fs = lfails;\
    const clock_t start = clock();\
    printf("\t%s:\n", name);\
    test();\
    printf("\t -- pass: %-20lu fail: %-20lu time: %ldms\n",\
	   (unsigned long)((ltests-ts)-(lfails-fs)), (unsigned long)lfails-fs,\
	   (long)((clock() - start) * 1000 / CLOCKS_PER_SEC));\
} while (0)
#endif

/* Assert a true statement. */
#define lok(test) do {\
    ++ltests;\
    if (!(test)) {\
        ++lfails;\
        printf("%s:%d error \n", __FILE__, __LINE__);\
    }} while (0)

/* Prototype to assert equal. */
#define lequal_base(equality, a, b, format) do {\
    ++ltests;\
    if (!(equality)) {\
        ++lfails;\
        printf("%s:%d ("format " != " format")\n", __FILE__, __LINE__, (a), (b));\
    }} while (0)

/* Assert two integers are equal. */
#define lequal(a, b)\
    lequal_base((a) == (b), a, b, "%d")

/* Assert two floats are equal (within LTEST_FLOAT_TOLERANCE). */
#define lfequal(a, b)\
    lequal_base(fabs((double)(a)-(double)(b)) <= LTEST_FLOAT_TOLERANCE\
     && fabs((double)(a)-(double)(b)) == fabs((double)(a)-(double)(b)),\
		(double)(a), (double)(b), "%f")

/* Assert two strings are equal. */
#define lsequal(a, b)\
    lequal_base(strcmp(a, b) == 0, a, b, "%s")

#endif /*__EEN_H__*/
