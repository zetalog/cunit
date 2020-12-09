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
 * @(#)cuint_result.h: cunit test result collector inteface
 * $Id: cunit_result.h,v 1.1.1.1 2004/08/20 05:30:52 zhengl Exp $
 */

#ifndef __CUNIT_RESULT_H_INCLUDE__
#define __CUNIT_RESULT_H_INCLUDE__

typedef struct _cunit_result_t {
    /* failure collector */
    Throwable *failures;
    int failure_count;
    int failure_size;

    /* error collector */
    Throwable *errors;
    int error_count;
    int error_size;

    /* registered listeners */
    TestListener *listeners;
    int listener_count;
    int listener_size;

    /* run tests */
    int runs;
    /* succeeded test count */
    int success_count;
    /* run seconds */
    double run_seconds;
    /* milli-seconds precision */
    unsigned short run_millitm;

    /* runner stopped */
    int stop;
} cunit_result_t;

CUNITEXT TestResult cunit_new_result();
CUNITEXT int cunit_should_stop(TestResult result);
CUNITEXT void cunit_add_failure(IN TestResult result, IN Test test, IN Throwable failure);
CUNITEXT void cunit_add_error(IN TestResult result, IN Test test, IN Throwable error);
CUNITEXT void cunit_delete_result(IN TestResult result);
CUNITEXT void cunit_start_test(IN TestResult result, IN Test test);
CUNITEXT void cunit_end_test(IN TestResult result, IN Test test);
CUNITEXT void cunit_register_listener(IN TestResult result, IN TestListener listener);

#endif /* __CUNIT_RESULT_H_INCLUDE__ */
