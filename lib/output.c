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
 * @(#)case.c: cunit default output implementation
 * $Id: output.c,v 1.1.1.1 2004/08/20 05:30:52 zhengl Exp $
 */

#include "cunit_int.h"

CUNITEXT char *cunit_format_message(IN char *message, IN int size, IN const char *format, ...) {
    char *result;
	va_list args;
	va_start(args, format);
    result = cunit_format_messagev(message, size, format, args);
	va_end(args);
    return result;
}

CUNITEXT char *cunit_format_messagev(IN char *message, IN int size,
                                     IN const char *format, IN va_list pvar) {
#ifdef WIN32
    if (_vsnprintf(message, size-1, format, pvar) < 0) {
#else
    if (vsnprintf(message, size-1, format, pvar) < 0) {
#endif
        message[size-1] = '\0';
    }
    return message;
}

CUNITEXT void cunit_output_message(IN const char *format, ...) {
	va_list args;
	va_start(args, format);
    cunit_output_messagev(format, args);
	va_end(args);
}

static void replace_percentm(const char *inbuffer, char *outbuffer, int olen) {
    register const char *t2;
    register char *t1, ch;
    if (!outbuffer || !inbuffer)
        return;
    olen--;
    for (t1 = outbuffer; (ch = *inbuffer) && t1-outbuffer < olen ; ++inbuffer)
        if (inbuffer[0] == '%' && inbuffer[1] == 'm')
            for (++inbuffer, t2 = (errno > 10000)
                 ? strerror(errno)
                 : strerror(errno);
                 (t2 && t1-outbuffer < olen) && (*t1 = *t2++);
                 t1++);
        else *t1++ = ch;
    *t1 = '\0';
}

CUNITEXT void cunit_output_messagev(IN const char *oformat, IN va_list pvar) {
#define FMT_BUFLEN 2*4096 + 2*10
    char fmt_cpy[FMT_BUFLEN], format[FMT_BUFLEN + 1];
    int serrno = errno;

    if (!oformat)
        return;
    format[0] = '\0';
    replace_percentm(oformat, format + strlen(format), sizeof(format) - strlen(format));
#ifdef WIN32
    if (_vsnprintf(fmt_cpy, FMT_BUFLEN-1, format, pvar) < 0) {
#else
    if (vsnprintf(fmt_cpy, FMT_BUFLEN-1, format, pvar) < 0) {
#endif
        fmt_cpy[FMT_BUFLEN-1] = '\0';
    }
#ifdef _MSC_VER
    /*
     * Output to the debug window.
     */
    OutputDebugStringA(fmt_cpy);
#else
#endif
    fprintf(stdout, "%s", fmt_cpy);
    errno = serrno; /* restore errno, just in case...? */
    return;
}
