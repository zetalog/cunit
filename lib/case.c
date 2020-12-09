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
 * @(#)case.c: cunit test case implementation
 * $Id: case.c,v 1.3 2004/10/16 11:33:30 huangy Exp $
 */

#include "cunit_int.h"

/*
 * case constructor.
 */
CUNITEXP TestCase CUNITAPI cunit_new_case(IN const char *name, IN TestCall call) {
	return cunit_new_case_ex(name, call, NULL, NULL);
}

CUNITEXP TestCase CUNITAPI cunit_new_case_ex(IN const char *name, IN TestCall call, TestCall set_up, TestCall tear_down) {
    TestCase caze = (TestCase)malloc(sizeof (cunit_case_t));
    if (caze) {
        memset((void *)caze, 0, sizeof (cunit_case_t));
        caze->runner = (CaseRunner)cunit_run_case;
        caze->counter = (CaseCounter)cunit_count_cases;
        caze->destroyer = (CaseDestroyer)cunit_delete_case;
        if (name)
            caze->name = strdup(name);
        caze->call = call;
	caze->set_up = set_up;
	caze->tear_down = tear_down;
    }
    return caze;
}

/*
 * case counter.
 */
CUNITEXT int cunit_count_cases(IN TestCase caze) {
    if (caze && caze->runner)
        /* always return 1 */
        return 1;
    else
        /* as counter may be called seperately, do not raise fatal error */
        return 0;
}

/*
 * case runner.
 */
CUNITEXT void cunit_run_case(IN TestCase caze, IN TestResult result) {
    int caught = FALSE;

    /* mark start of test case */
    cunit_start_test(result, (Test)caze);
    if (caze->set_up)
        (caze->set_up)();
    /* run case in the TRY CATCH scope */
    CUNIT_TRY {
        if (caze && caze->call) {
            /* callback case */
            (caze->call)();
        }
        else
            cunit_fatal_error("Can not run null case object!");
    } CUNIT_CATCH(e) {
        if (e->type == CUNIT_ASSERTION) {
            cunit_add_failure(result, (Test)caze, e);
        } else {
            cunit_add_error(result, (Test)caze, e);
        }
        caught = TRUE;
    } CUNIT_END_CATCH
    if (caze->tear_down)
        (caze->tear_down)();
    if (!caught) {
        result->success_count++;
    }
    /* mark end of test case */
    cunit_end_test(result, (Test)caze);
}

/*
 * case destructor.
 */
CUNITEXT void cunit_delete_case(IN TestCase caze) {
    if (caze) {
        if (((Test)caze)->name)
            free(((Test)caze)->name);
        free(caze);
    }
}
