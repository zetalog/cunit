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
 * @(#)throw.c: exception & assertion implementation
 * $Id: throw.c,v 1.1.1.1 2004/08/20 05:30:52 zhengl Exp $
 */

#include "cunit_int.h"

/*=========================================================================
 * Local variables
 *=======================================================================*/
/* CUNIT_TRY/CUNIT_CATCH throwable scope */
static cunit_scope_t _throwable_struct = {
   /* env =           */ NULL,
   /* throwable =     */ NULL,
   /* roots_count   = */ 0,
   /* outer =         */ NULL
};
ThrowableScope _throwable_scope = &_throwable_struct;

int _roots_length;
cunit_cell_t _temporary_roots[CUNIT_MAXIMUM_ROOTS];

CUNITEXP ThrowableScope CUNITAPI cunit_get_scope() {
    return _throwable_scope;
}

CUNITEXP void CUNITAPI cunit_set_scope(ThrowableScope scope) {
    _throwable_scope = scope;
}

CUNITEXP int CUNITAPI cunit_get_roots_length() {
    return _roots_length;
}

CUNITEXP void CUNITAPI cunit_set_roots_length(int length) {
    _roots_length = length;
}

CUNITEXP void CUNITAPI cunit_set_roots_cell(int index, int cell) {
    _temporary_roots[index].cell = cell;
}

CUNITEXP void CUNITAPI cunit_set_roots_pointer(int index, cell *pointer) {
    _temporary_roots[index].pointer = pointer;
}

/*
 * throwable constructor.
 */
CUNITEXT Throwable cunit_new_throwable(CUNIT_SOURCE_LINE_DECL,
                                       IN int type, IN const char *message) {
    Throwable exception = malloc(sizeof (cunit_throwable_t));
    if (exception) {
        memset(exception, 0, sizeof (cunit_throwable_t));
        exception->type = type;
        if (message)
            exception->message = strdup(message);
        if (file)
            exception->file = strdup(file);
        exception->line = line;
    }
    return exception;
}

/*
 * throwable destructor.
 */
CUNITEXP void CUNITAPI cunit_delete_throwable(IN Throwable exception) {
    if (exception) {
        /* destroy throwable message */
        if (exception->message) {
            free(exception->message);
            exception->message = NULL;
        }
        /* destroy throwable file name */
        if (exception->file) {
            free(exception->file);
            exception->file = NULL;
        }
        free(exception);
    }
}

/*
 * exception raiser
 */
CUNITEXP void CUNITAPI cunit_raise_exception(CUNIT_SOURCE_LINE_DECL,
                                             IN const char* message) {
    CUNIT_THROW(cunit_new_throwable(file, line, CUNIT_EXCEPTION, message))
}

/*
 * throwable type getter.
 */
CUNITEXP int CUNITAPI cunit_throwable_type(IN Throwable throwable) {
    if (throwable)
        return throwable->type;
    else
        return CUNIT_EXCEPTION;
}

/*
 * throwable message getter.
 */
CUNITEXP char * CUNITAPI cunit_throwable_message(IN Throwable throwable) {
    if (throwable)
        return throwable->message;
    else
        return "Throwable is null object!";
}
