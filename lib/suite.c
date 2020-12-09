/*
 * ZETALOG's Personal COPYRIGHT
 *
 * Copyright (c) 2003
 *    ZETALOG - "Lv ZHENG".  All rights reserved.
 *    Author: Lv "Zetalog" Zheng
 *    Internet: zetalog@hzcnc.com
 *
 * This COPYRIGHT used to protect Personal Intelligence Rights.
 * Redistribution and use in source and binary forms with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the Lv "Zetalog" ZHENG.
 * 3. Neither the name of this software nor the names of its developers may
 *    be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 4. Permission of redistribution and/or reuse of souce code partially only
 *    granted to the developer(s) in the companies ZETALOG worked.
 * 5. Any modification of this software should be published to ZETALOG unless
 *    the above copyright notice is no longer declaimed.
 *
 * THIS SOFTWARE IS PROVIDED BY THE ZETALOG AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE ZETALOG OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * @(#)suite.c: cunit test suite implementation
 * $Id: suite.c,v 1.1.1.1 2004/08/20 05:30:52 zhengl Exp $
 */

#include "cunit_int.h"

/*
 * suite constructor.
 */
CUNITEXP TestSuite CUNITAPI cunit_new_suite(IN const char *name) {
    TestSuite suite = malloc(sizeof (cunit_suite_t));
    if (suite) {
        /* initialize test suite */
        memset(suite, 0, sizeof (cunit_suite_t));
        suite->runner = (CaseRunner)cunit_run_suite;
        suite->counter = (CaseCounter)cunit_count_suite;
        suite->destroyer = (CaseDestroyer)cunit_delete_suite;
        /* create default test vector */
        suite->count = 0;
        suite->tests = (Test *)malloc(sizeof (Test) *CUNIT_DEFAULT_TESTS);
        if (suite->tests)
            suite->size = CUNIT_DEFAULT_TESTS;
        /* clone test name if any */
        if (name)
            suite->name = strdup(name);
    }
    return suite;
}

/*
 * add a test.
 */
CUNITEXP void CUNITAPI cunit_add_test(IN TestSuite suite, IN Test test) {
    if (suite) {
        if (suite->count < suite->size) {
            /* unused block exists */
            suite->tests[suite->count] = test;
            suite->count++;
        } else {
            /* extends vector */
            Test *tests = (Test *)malloc(sizeof (Test)*(suite->size+CUNIT_VECTOR_INCREMENT));
            if (!tests) {
                cunit_fatal_error("Memory allocation failed!");
                return;
            } else {
                /* copy old vector */
                if (suite->tests)
                    memcpy(tests, suite->tests, sizeof (Test)*suite->size);
                suite->size += CUNIT_VECTOR_INCREMENT;
                /* release old vector */
                if (suite->tests)   /* need not this? */
                    free(suite->tests);
                suite->tests = tests;
                /* readd element */
                cunit_add_test(suite, test);
            }
        }
    }
}

/*
 * suite runner.
 */
CUNITEXT void cunit_run_suite(TestSuite suite, TestResult result) {
    Test test;
    int index;

    /* sanity check */
    if (suite == NULL)
        cunit_fatal_error("Can not run null suite object!");
    for (index  = 0; index < suite->count; index++) {
        /* break if runner should be stopped */
        if (cunit_should_stop(result))
            break;
        /* fetch and run test */
        test = suite->tests[index];
        if (test && test->runner)
            test->runner(test, result);
    }
}

/*
 * suite counter.
 */
CUNITEXT int cunit_count_suite(TestSuite suite) {
    Test test;
    int count = 0, index;

    /* as counter may be called seperately, do not raise fatal error */
    if (!suite)
        return 0;
    for (index  = 0; index < suite->count; index++) {
        test = suite->tests[index];
        /* call test counter */
        if (test) {
            if (test->counter)
                count += test->counter(test);
            else if (test->runner)
                count += 1;
        }
    }
    return count;
}

/*
 * suite destructor.
 */
CUNITEXT void cunit_delete_suite(TestSuite suite) {
    if (suite) {
        if (suite->tests) {
            /* destroy maintained tests */
            int index;
            for (index = 0; index < suite->count; index++)
                suite->tests[index]->destroyer(suite->tests[index]);
            free(suite->tests);
        }
        /* destroy test name */
        if (suite->name)
            free(suite->name);
        free(suite);
    }
}
