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
 * @(#)console.c: cunit console runner implementation
 * $Id: console.c,v 1.1.1.1 2004/08/20 05:30:52 zhengl Exp $
 */

#include "cunit_int.h"
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>

/*=========================================================================
 * Data structure definitions
 *=======================================================================*/
typedef struct _cunit_printer_t *ResultPrinter;
typedef struct _cunit_printer_t {
    cunit_listener_t;
    int success;
} cunit_printer_t;

/*=========================================================================
 * Local function definitions
 *=======================================================================*/
static void pause_runner(IN int wait);
static TestResult run_scope(IN TestRunner runner, IN Test test, IN int wait);
static void print_result(IN TestResult result, IN double run_seconds,
                         IN unsigned short run_millisec);

/*=========================================================================
 * Callback definitions
 *=======================================================================*/
static TestResult CUNITCBK run_console(IN TestRunner runner, IN Test test);
static void CUNITCBK add_error(IN TestListener listener, IN Test test, IN Throwable error);
static void CUNITCBK add_failure(IN TestListener listener, IN Test test, IN Throwable error);
static void CUNITCBK start_test(IN TestListener listener, IN Test test);
static void CUNITCBK end_test(IN TestListener listener, IN Test test);

/*=========================================================================
 * Default variables
 *=======================================================================*/
/* default listener */
static cunit_printer_t _listener_imp = {
    {
      add_error,
      add_failure,
      start_test,
      end_test,
    },
    TRUE,
};
TestListener _default_listener = (TestListener)&_listener_imp;

/* default runner */
static cunit_runner_t _runner_imp = {
    run_console,
};
TestRunner _default_runner = (TestRunner)&_runner_imp;

/*
 * listener end_test callback.
 */
static void CUNITCBK end_test(IN TestListener listener, IN Test test) {
    if (((ResultPrinter)listener)->success == TRUE) {
        cunit_output_message("Success\n");
    }
}

/*
 * listener start_test callback.
 */
static void CUNITCBK start_test(IN TestListener listener, IN Test test) {
    unsigned int index;

    cunit_output_message("%s:", test->name);
    for (index = 0; index < (41 - strlen(test->name)); index++)
        cunit_output_message(".");
    ((ResultPrinter)listener)->success = TRUE;
}

/*
 * listener add_error callback.
 */
static void CUNITCBK add_error(IN TestListener listener, IN Test test, IN Throwable error) {
    cunit_output_message("..Error\n");
    cunit_output_message("%s(%d), %s\n", error->file, error->line, error->message);
    ((ResultPrinter)listener)->success = FALSE;
}

/*
 * listener add_failure callback.
 */
static void CUNITCBK add_failure(IN TestListener listener, IN Test test, IN Throwable failure) {
    cunit_output_message("..Error\n");
    cunit_output_message("%s(%d), %s\n", failure->file, failure->line, failure->message);
    ((ResultPrinter)listener)->success = FALSE;
}

/*
 * runner callback.
 */
static TestResult CUNITCBK run_console(IN TestRunner runner, IN Test test) {
    return run_scope(runner, test, FALSE);
}

/*
 * console result printer.
 */
CUNITEXT void print_result(IN TestResult result, IN double run_seconds, IN unsigned short run_millisec) {
    cunit_output_message("run %d cases. success %d, failure %d, error %d.\ntotal time %.0f.%hu seconds\n",
                         result->runs, result->success_count,
                         result->failure_count, result->error_count,
                         run_seconds, run_millisec);
    return;
}

/*
 * pause runner at console.
 */
static void pause_runner(IN int wait) {
    int ch;
    if (!wait) return;
    ch = getc(stdin);
}

/*
 * console runner with pauser.
 */
static TestResult run_scope(IN TestRunner runner, IN Test test, int wait) {
    struct timeb start_time, end_time;
    unsigned short run_millisec;
    double run_seconds;

    /* create TestResult object */
    TestResult result = cunit_new_result();

    /* register listener */
    cunit_register_listener(result, _default_listener);

    /* run tests, record time */
    ftime(&start_time);
    test->runner(test, result);
    ftime(&end_time);
    if (end_time.millitm > start_time.millitm) {
        run_millisec = end_time.millitm - start_time.millitm;
        run_seconds = difftime(end_time.time, start_time.time);
    } else {
        run_millisec = end_time.millitm+1000 - start_time.millitm;
        run_seconds = difftime(end_time.time, start_time.time);
    }

    /* output result */
    print_result(result, run_seconds, run_millisec);
    /* recycle resources */
    cunit_delete_result(result);
    test->destroyer(test);

    /* pause runner if needed */
    pause_runner(wait);
    return result;
}
