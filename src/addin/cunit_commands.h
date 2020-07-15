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
 * @(#)cuint_commands.h: cunit msdev commands objects definition
 * $Id: cunit_commands.h,v 1.1.1.1 2004/08/20 05:30:52 zhengl Exp $
 */

#ifndef __CUNIT_COMMANDS_H_INCLUDE__
#define __CUNIT_COMMANDS_H_INCLUDE__

#include "cunit_includes.h"

class //__declspec(novtable)
DSCommands : public ICommands {
public:
    LPDATAOBJECT m_pDataObj;

protected:
    ULONG       m_cRef;
	ITypeInfo  *m_pTInfo;
	IApplication* m_pApplication;

public:
    DSCommands();
    ~DSCommands();

    /* IUnknown members */
    STDMETHODIMP            QueryInterface(REFIID, LPVOID FAR *);
    STDMETHODIMP_(ULONG)    AddRef();
    STDMETHODIMP_(ULONG)    Release();

    /* IDispatch members */
    STDMETHODIMP            GetTypeInfoCount(UINT FAR* pctinfo);
    STDMETHODIMP            GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo FAR* FAR* pptinfo);
    STDMETHODIMP            GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames,
                                          UINT cNames, LCID lcid, DISPID FAR* rgdispid);
    STDMETHODIMP            Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags,
                                   DISPPARAMS FAR* pdispparams, VARIANT FAR* pvarResult,
                                   EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr);

    /* local members */
    STDMETHODIMP            set_Application(IApplication *pApplication);
    STDMETHODIMP            get_Application(IApplication **ppApplication);

    /* ICommands members */
    STDMETHODIMP            RunUnitTest();
    STDMETHODIMP            GotoSourceLine(BSTR bszFileName, int nLineNumber);
};

#endif /* __CUNIT_COMMANDS_H_INCLUDE__ */
