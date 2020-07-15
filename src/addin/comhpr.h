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
 * @(#)cunit_com.h: cunit addin com helper header
 * $Id: comhpr.h,v 1.1.1.1 2004/08/20 05:30:52 zhengl Exp $
 */

#ifndef STRICT
#define STRICT
#endif

/* WIN32, get ole2 from windows.h */
#define INC_OLE2

/*=========================================================================
 * Include Files
 *=======================================================================*/
#include <windows.h>
#include <windowsx.h>
#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>
#include <tchar.h>

#define ResultFromShort(i)  ResultFromScode(MAKE_HRESULT(SEVERITY_SUCCESS, 0, (USHORT)(i)))

/*
 * Following are stolen from atlconv.h for SDK implementations.
 */
/*=========================================================================
 * Macro definitions
 *=======================================================================*/
#define USES_CONVERSION int _convert; _convert; UINT _acp = CP_ACP; _acp; LPCWSTR _lpw; _lpw; LPCSTR _lpa; _lpa

LPWSTR WINAPI A2WHelper(LPWSTR lpw, LPCSTR lpa, int nChars);
LPSTR WINAPI W2AHelper(LPSTR lpa, LPCWSTR lpw, int nChars);

#define W2A(lpw) (                                                  \
	((_lpw = lpw) == NULL) ? NULL : (                               \
		_convert = (lstrlenW(_lpw)+1)*2,                            \
		W2AHelper((LPSTR) alloca(_convert), _lpw, _convert)))
#define A2W(lpa) (\
	((_lpa = lpa) == NULL) ? NULL : (\
		_convert = (lstrlenA(_lpa)+1),\
		A2WHelper((LPWSTR) alloca(_convert*2), _lpa, _convert)))

#define A2CW(lpa) ((LPCWSTR)A2W(lpa))
#define W2CA(lpw) ((LPCSTR)W2A(lpw))

#if defined(_UNICODE)
    /* in these cases the default (TCHAR) is the same as OLECHAR */
	inline size_t ocslen(LPCOLESTR x) { return lstrlenW(x); }
	inline OLECHAR* ocscpy(LPOLESTR dest, LPCOLESTR src) { return lstrcpyW(dest, src); }
	inline OLECHAR* ocscat(LPOLESTR dest, LPCOLESTR src) { return lstrcatW(dest, src); }
	inline LPCOLESTR T2COLE(LPCTSTR lp) { return lp; }
	inline LPCTSTR OLE2CT(LPCOLESTR lp) { return lp; }
	inline LPOLESTR T2OLE(LPTSTR lp) { return lp; }
	inline LPTSTR OLE2T(LPOLESTR lp) { return lp; }
	inline LPOLESTR CharNextO(LPCOLESTR lp) {return CharNextW(lp);}
#elif defined(OLE2ANSI)
    /* in these cases the default (TCHAR) is the same as OLECHAR */
	inline size_t ocslen(LPCOLESTR x) { return lstrlen(x); }
	inline OLECHAR* ocscpy(LPOLESTR dest, LPCOLESTR src) { return lstrcpy(dest, src); }
	inline OLECHAR* ocscat(LPOLESTR dest, LPCOLESTR src) { return ocscpy(dest+ocslen(dest), src); }
	inline LPCOLESTR T2COLE(LPCTSTR lp) { return lp; }
	inline LPCTSTR OLE2CT(LPCOLESTR lp) { return lp; }
	inline LPOLESTR T2OLE(LPTSTR lp) { return lp; }
	inline LPTSTR OLE2T(LPOLESTR lp) { return lp; }
	inline LPOLESTR CharNextO(LPCOLESTR lp) {return CharNext(lp);}
#else
	inline size_t ocslen(LPCOLESTR x) { return lstrlenW(x); }
	/* lstrcpyW doesn't work on Win95, so we do this */
	inline OLECHAR* ocscpy(LPOLESTR dest, LPCOLESTR src)
	{return (LPOLESTR) memcpy(dest, src, (lstrlenW(src)+1)*sizeof(WCHAR));}
	inline OLECHAR* ocscat(LPOLESTR dest, LPCOLESTR src) { return ocscpy(dest+ocslen(dest), src); }
	/* CharNextW doesn't work on Win95 so we use this */
	#define T2COLE(lpa) A2CW(lpa)
	#define T2OLE(lpa) A2W(lpa)
	#define OLE2CT(lpo) W2CA(lpo)
	#define OLE2T(lpo) W2A(lpo)
	inline LPOLESTR CharNextO(LPCOLESTR lp) {return (LPOLESTR) ((*lp) ? (lp+1) : lp);}
#endif

inline BSTR OLE2BSTR(LPCOLESTR lp) {return ::SysAllocString(lp);}

#define THREADFLAGS_APARTMENT 0x1
#define THREADFLAGS_BOTH 0x2
#define AUTPRXFLAG 0x4

#define ODS(sz) OutputDebugStringA(sz)

#define HRCALL(a, errmsg) \
do { \
    hr = (a); \
    if (FAILED(hr)) { \
        dprintf( "%s:%d  HRCALL Failed: %s\n  0x%.8x = %s\n", \
                __FILE__, __LINE__, errmsg, hr, #a ); \
        goto clean; \
    } \
} while (0)

/*
 * Helper function that put output in stdout and debug window
 * in Visual Studio
 */
inline void dprintf(char * format, ...) {
    static char buf[1024];
    va_list args;
    va_start(args, format);
    vsprintf(buf, format, args);
    va_end(args);
    OutputDebugStringA(buf);
    printf("%s", buf);
}

HRESULT WINAPI ModuleRegisterClass(HINSTANCE hInstance, const CLSID& clsid, LPCTSTR lpszProgID,
                                   LPCTSTR lpszVerIndProgID, UINT nDescID, DWORD dwFlags);
HRESULT WINAPI ModuleUnregisterClass(HINSTANCE hInstance, const CLSID& clsid,
                                     LPCTSTR lpszProgID, LPCTSTR lpszVerIndProgID);
WINAPI ModuleRegisterTypeLib(HINSTANCE hInstance, LPCOLESTR lpszIndex);
WINAPI ModuleUnRegisterTypeLib(HINSTANCE hInstance, LPCOLESTR lpszIndex);
LONG RegSetKeyValue(HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName, LPCTSTR lpszValue);
HRESULT LoadTypeInfo(ITypeInfo FAR* FAR* pptinfo, OLECHAR FAR* file, REFGUID guid, REFCLSID clsid);
VARIANT VariantString(BSTR str);