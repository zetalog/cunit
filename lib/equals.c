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
 * @(#)equals.c: cunit value comparition implementation
 * $Id: equals.c,v 1.1.1.1 2004/08/20 05:30:52 zhengl Exp $
 */

#include "cunit_int.h"

#define CUNIT_MESSAGE_LENGTH    256

CUNITEXP void CUNITAPI cunit_raise_assertion(CUNIT_SOURCE_LINE_DECL, IN const char* message) {
    CUNIT_THROW(cunit_new_throwable(file, line, CUNIT_ASSERTION, message))
}

CUNITEXP void CUNITAPI cunit_equals_char(CUNIT_SOURCE_LINE_DECL,
                                         IN char expected, IN char actual) {
    char message[CUNIT_MESSAGE_LENGTH];

    if (expected != actual) {
        cunit_raise_assertion(file, line, cunit_format_message(message, CUNIT_MESSAGE_LENGTH,
                              "Value(char) '%c' does not equal '%c'.", actual, expected));
    }
}

CUNITEXP void CUNITAPI cunit_equals_short(CUNIT_SOURCE_LINE_DECL,
                                          IN short expected, IN short actual) {
    char message[CUNIT_MESSAGE_LENGTH];

    if (expected != actual) {
        cunit_raise_assertion(file, line, cunit_format_message(message, CUNIT_MESSAGE_LENGTH,
                              "Value(short) '%d' does not equal '%d'.", actual, expected));
    }
}

CUNITEXP void CUNITAPI cunit_equals_int(CUNIT_SOURCE_LINE_DECL,
                                        IN int expected, IN int actual) {
    char message[CUNIT_MESSAGE_LENGTH];

    if (expected != actual) {
        cunit_raise_assertion(file, line, cunit_format_message(message, CUNIT_MESSAGE_LENGTH,
                              "Value(int) '%d' does not equal '%d'.", actual, expected));
    }
}

CUNITEXP void CUNITAPI cunit_equals_long(CUNIT_SOURCE_LINE_DECL,
                                         IN long expected, IN long actual) {
    char message[CUNIT_MESSAGE_LENGTH];

    if (expected != actual) {
        cunit_raise_assertion(file, line, cunit_format_message(message, CUNIT_MESSAGE_LENGTH,
                              "Value(long) '%d' does not equal '%d'.", actual, expected));
    }
}

CUNITEXP void CUNITAPI cunit_equals_float(CUNIT_SOURCE_LINE_DECL,
                                          IN float expected, IN float actual) {
    char message[CUNIT_MESSAGE_LENGTH];

    if (expected != actual) {
        cunit_raise_assertion(file, line, cunit_format_message(message, CUNIT_MESSAGE_LENGTH,
                              "Value(float) '%f' does not equal '%f'.", actual, expected));
    }
}

CUNITEXP void CUNITAPI cunit_equals_double(CUNIT_SOURCE_LINE_DECL,
                                           IN double expected, IN double actual) {
    char message[CUNIT_MESSAGE_LENGTH];

    if (expected != actual) {
        cunit_raise_assertion(file, line, cunit_format_message(message, CUNIT_MESSAGE_LENGTH,
                              "Value(double) '%f' does not equal '%f'.", actual, expected));
    }
}

CUNITEXP void CUNITAPI cunit_equals_uchar(CUNIT_SOURCE_LINE_DECL,
                                          IN unsigned char expected, IN unsigned char actual) {
    char message[CUNIT_MESSAGE_LENGTH];

    if (expected != actual) {
        cunit_raise_assertion(file, line, cunit_format_message(message, CUNIT_MESSAGE_LENGTH,
                              "Value(unsigned char) '%c' does not equal '%c'.", actual, expected));
    }
}

CUNITEXP void CUNITAPI cunit_equals_ushort(CUNIT_SOURCE_LINE_DECL,
                                           IN unsigned short expected, IN unsigned short actual) {
    char message[CUNIT_MESSAGE_LENGTH];

    if (expected != actual) {
        cunit_raise_assertion(file, line, cunit_format_message(message, CUNIT_MESSAGE_LENGTH,
                              "Value(unsigned short) '%u' does not equal '%u'.", actual, expected));
    }
}

CUNITEXP void CUNITAPI cunit_equals_uint(CUNIT_SOURCE_LINE_DECL,
                                         IN unsigned int expected, IN unsigned int actual) {
    char message[CUNIT_MESSAGE_LENGTH];

    if (expected != actual) {
        cunit_raise_assertion(file, line, cunit_format_message(message, CUNIT_MESSAGE_LENGTH,
                              "Value(unsigned int) '%u' does not equal '%u'.", actual, expected));
    }
}

CUNITEXP void CUNITAPI cunit_equals_ulong(CUNIT_SOURCE_LINE_DECL,
                                          IN unsigned long expected, IN unsigned long actual) {
    char message[CUNIT_MESSAGE_LENGTH];

    if (expected != actual) {
        cunit_raise_assertion(file, line, cunit_format_message(message, CUNIT_MESSAGE_LENGTH,
                              "Value(unsigned long) '%u' does not equal '%u'.", actual, expected));
    }
}

CUNITEXP void CUNITAPI cunit_equals_pointer(CUNIT_SOURCE_LINE_DECL,
                                            IN void *expected, IN void *actual) {
    char message[CUNIT_MESSAGE_LENGTH];

    if (expected != actual) {
        cunit_raise_assertion(file, line, cunit_format_message(message, CUNIT_MESSAGE_LENGTH,
                              "Value(void *) '%p' does not equal '%p'.", actual, expected));
    }
}

CUNITEXP void CUNITAPI cunit_equals_null(CUNIT_SOURCE_LINE_DECL, IN void *object) {
    char message[CUNIT_MESSAGE_LENGTH];

    if (object != NULL) {
        cunit_raise_assertion(file, line, cunit_format_message(message, CUNIT_MESSAGE_LENGTH,
                              "Object '%p' is not NULL.", object));
    }
}

CUNITEXP void CUNITAPI cunit_equals_notnull(CUNIT_SOURCE_LINE_DECL, IN void *object) {
    char message[CUNIT_MESSAGE_LENGTH];

    if (object == NULL) {
        cunit_raise_assertion(file, line, cunit_format_message(message, CUNIT_MESSAGE_LENGTH,
                              "Object '%p' is NULL.", object));
    }
}
