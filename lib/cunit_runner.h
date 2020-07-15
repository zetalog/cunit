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
 * @(#)cuint_runner.h: cunit test runner inteface
 * $Id: cunit_runner.h,v 1.1.1.1 2004/08/20 05:30:52 zhengl Exp $
 */

#ifndef __CUNIT_RUNNER_H_INCLUDE__
#define __CUNIT_RUNNER_H_INCLUDE__

typedef TestResult (CUNITCBK *TestMain)(TestRunner, Test);

typedef struct _cunit_runner_t {
    TestMain main;
    //TestResult result;
} cunit_runner_t;

/*
 * This is a non-nesting use of setjmp/longjmp used solely for the purpose
 * of exiting the test runner in a clean way. By separating it out from the
 * exception mechanism above, we don't need to worry about whether or not
 * we are throwing an exception or exiting the runner in an CUNIT_CATCH block.
 */
#define CUNIT_START                                                 \
    {                                                               \
        jmp_buf __env__;                                            \
        cunit_set_runner_scope(&(__env__));                         \
        if (setjmp(__env__) == 0) {

#define CUNIT_EXIT(__code__)                                        \
        cunit_set_exit_code(__code__);                              \
        longjmp(*((jmp_buf*)cunit_get_runner_scope()),1)

#define CUNIT_FINISH(__code__)                                      \
        } else {                                                    \
            int __code__ = cunit_get_exit_code();

#define CUNIT_END_FINISH                                            \
        }                                                           \
    }

CUNITEXT void cunit_set_runner_scope(IN void *env);
CUNITEXT void *cunit_get_runner_scope();
CUNITEXT void cunit_set_exit_code(IN int code);
CUNITEXT int cunit_get_exit_code();

#define CUNIT_FATAL_ERROR           127
#define CUNIT_UNCAUGHT_EXCEPTION    128

extern TestRunner _default_runner;

#endif /* __CUNIT_RUNNER_H_INCLUDE__ */
