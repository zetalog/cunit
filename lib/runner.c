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
 * @(#)case.c: cunit test runner implementation
 * $Id: runner.c,v 1.1.1.1 2004/08/20 05:30:52 zhengl Exp $
 */

#include "cunit_int.h"

void* _runner_scope = NULL;
int _exit_code = 0;

CUNITEXT void cunit_set_runner_scope(IN void *env) {
    _runner_scope = env;
}

CUNITEXT void *cunit_get_runner_scope() {
    return _runner_scope;
}

CUNITEXT void cunit_set_exit_code(IN int code) {
    _exit_code = code;
}

CUNITEXT int cunit_get_exit_code() {
    return _exit_code;
}

/*=========================================================================
 * FUNCTION:      cunit_fatal_error()
 * TYPE:          internal error handling operation
 * OVERVIEW:      Report a fatal error indicating that the execution
 *                of erroneous code might have endangered the
 *                integrity of the CUNIT. CUNIT will be stopped. This
 *                operation should be called only the from inside the
 *                CUNIT runner scope.
 * INTERFACE:
 *   parameters:  error message string.
 *   returns:     <nothing>
 *=======================================================================*/
CUNITEXP void CUNITAPI cunit_fatal_error(IN const char* message) {
    cunit_output_message(message);
    CUNIT_EXIT(CUNIT_FATAL_ERROR);
}

/*=========================================================================
 * FUNCTION:      cunit_run_test()
 * TYPE:          test running kick off operation
 * OVERVIEW:      Run specified unit tests, collects and displays results.
 *                This function will use default TestRunner known as
 *                CuiRunner.
 * INTERFACE:
 *   parameters:  unit tests.
 *   returns:     <nothing>
 *=======================================================================*/
CUNITEXP TestResult CUNITAPI cunit_run_test(IN TestRunner runner, IN Test test) {
    TestResult result = NULL;

    if (!runner)
        runner = cunit_get_default();
    CUNIT_START {
        if (!runner)
            cunit_fatal_error("Can not run using null runner object!");
        result = runner->main(runner, test);
    } CUNIT_FINISH(code) {
        cunit_output_message("\nFatal error exit with code (%d)!\n", code);
    } CUNIT_END_FINISH

    return result;
}

CUNITEXP TestRunner CUNITAPI cunit_get_default() {
    return _default_runner;
}

CUNITEXP void CUNITAPI cunit_set_default(IN TestRunner runner) {
    _default_runner = runner;
}

/*
CUNITEXP void CUNITAPI cunit_stop_test(TestRunner runner) {
    runner->result->stop = TRUE;
}
*/

CUNITEXP int CUNITAPI cunit_count_tests(Test test) {
    if (!test)
        return 0;
    return test->counter(test);
}
