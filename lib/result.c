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
 * @(#)case.c: cunit test result implementation
 * $Id: result.c,v 1.1.1.1 2004/08/20 05:30:52 zhengl Exp $
 */

#include "cunit_int.h"
#include <stdio.h>

CUNITEXT int cunit_should_stop(TestResult result) {
    return result->stop;
}

/*
 * result contructor.
 */
CUNITEXT TestResult cunit_new_result() {
    TestResult result = malloc(sizeof (struct _cunit_result_t));

    if (result) {
        memset(result, 0, sizeof (struct _cunit_result_t));

        result->success_count = 0;
        result->runs = 0;

        /* initialize Failure vector */
        result->failure_count = 0;
        result->failures = (Throwable *)malloc(sizeof (Throwable)*CUNIT_DEFAULT_FAILURE);
        if (result->failures)
            result->failure_size = CUNIT_DEFAULT_FAILURE;

        /* initialize Error vector */
        result->error_count = 0;
        result->errors = (Throwable *)malloc(sizeof (Throwable)*CUNIT_DEFAULT_ERROR);
        if (result->errors)
            result->error_size = CUNIT_DEFAULT_ERROR;

        /* initialize TestListener vector */
        result->listener_count = 0;
        result->listeners = (TestListener *)malloc(sizeof (TestListener)*CUNIT_DEFAULT_LISTENER);
        if (result->listeners)
            result->listener_size = CUNIT_DEFAULT_LISTENER;

        result->stop = FALSE;
    } else
        cunit_fatal_error("Memory allocation failure!");
    return result;
}

CUNITEXT void cunit_register_listener(IN TestResult result, IN TestListener listener) {
    if (result) {
        if (result->listener_count < result->listener_size) {
            result->listeners[result->listener_count] = listener;
            result->listener_count++;
        } else {
            TestListener *listeners = (TestListener *)malloc(sizeof (TestListener)*(result->listener_size+CUNIT_VECTOR_INCREMENT));
            if (!listeners) {
                cunit_fatal_error("Memory allocation failed!");
            } else {
                if (result->listeners)
                    memcpy(listeners, result->listeners, sizeof (TestListener)*result->listener_size);
                result->listener_size += CUNIT_VECTOR_INCREMENT;
                if (result->listeners)
                    free(result->listeners);
                result->listeners = listeners;
                cunit_register_listener(result, listener);
            }
        }
    }
}

CUNITEXT void cunit_add_failure(IN TestResult result, IN Test test, IN Throwable failure) {
    if (result) {
        if (result->failure_count < result->failure_size) {
            int index;

            result->failures[result->failure_count] = failure;
            result->failure_count++;

            for (index = 0; index < result->listener_count; index++) {
                TestListener listener = result->listeners[index];
                if (listener && listener->add_failure)
                    listener->add_failure(listener, test, failure);
            }
        } else {
            Throwable *failures = (Throwable *)malloc(sizeof (Throwable)*(result->failure_size+CUNIT_VECTOR_INCREMENT));
            if (!failures) {
                cunit_fatal_error("Memory allocation failed!");
            } else {
                if (result->failures)
                    memcpy(failures, result->failures, sizeof (Throwable)*result->failure_size);
                result->failure_size += CUNIT_VECTOR_INCREMENT;
                if (result->failures)
                    free(result->failures);
                result->failures = failures;
                cunit_add_failure(result, test, failure);
            }
        }
    }
}

CUNITEXT void cunit_add_error(IN TestResult result, IN Test test, IN Throwable error) {
    if (result) {
        if (result->error_count < result->error_size) {
            int index;

            result->errors[result->error_count] = error;
            result->error_count++;

            for (index = 0; index < result->listener_count; index++) {
                TestListener listener = result->listeners[index];
                if (listener && listener->add_error)
                    listener->add_error(listener, test, error);
            }
        } else {
            Throwable *errors = (Throwable *)malloc(sizeof (Throwable)*(result->error_size+CUNIT_VECTOR_INCREMENT));
            if (!errors) {
                cunit_fatal_error("Memory allocation failed!");
            } else {
                if (result->errors)
                    memcpy(errors, result->errors, sizeof (Throwable)*result->error_size);
                result->error_size += CUNIT_VECTOR_INCREMENT;
                if (result->errors)
                    free(result->errors);
                result->errors = errors;
                cunit_add_error(result, test, error);
            }
        }
    }
}

CUNITEXT void cunit_start_test(IN TestResult result, IN Test test) {
    int count = 0;
    int index;

    if (test)
        count = test->counter(test);
    result->runs += count;

    for (index = 0; index < result->listener_count; index++) {
        TestListener listener = result->listeners[index];
        if (listener && listener->start_test)
            listener->start_test(listener, test);
    }
}

CUNITEXT void cunit_end_test(IN TestResult result, IN Test test) {
    int index;

    for (index = 0; index < result->listener_count; index++) {
        TestListener listener = result->listeners[index];
        if (listener && listener->end_test)
            listener->end_test(listener, test);
    }
}

/*
 * result destructor.
 */
CUNITEXT void cunit_delete_result(IN TestResult result) {
    int index;

    if (result) {
        if (result->errors) {
            for (index = 0; index < result->error_count; index++)
                cunit_delete_throwable(result->errors[index]);
            free(result->errors);
        }
        if (result->failures) {
            for (index = 0; index < result->failure_count; index++)
                cunit_delete_throwable(result->failures[index]);
            free(result->failures);
        }
        if (result->listeners) {
            /*
             * Do not destroy listener here.
             * Listeners should be maintained by runner implementation
             * as it may be permanent.
             */
            free(result->listeners);
        }
        free(result);
    }
}
