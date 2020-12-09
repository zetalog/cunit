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
 * @(#)cuint_addin.h: cunit msdev addin class definition
 * $Id: cunit_addin.h,v 1.1.1.1 2004/08/20 05:30:52 zhengl Exp $
 */

#ifndef __CUNIT_DSADDIN_INCLUDE_H__
#define __CUNIT_DSADDIN_INCLUDE_H__

#include "cunit_includes.h"

// {7CAB6CB9-902F-4945-A100-EFA89467BC7B}
DEFINE_GUID(CLSID_DSAddIn,
0x7cab6cb9, 0x902f, 0x4945, 0xa1, 0, 0xef, 0xa8, 0x94, 0x67, 0xbc, 0x7b);

// this class factory object creates Developer Studio Add-in
class DSFactory : public IClassFactory {

protected:
    ULONG       m_cRef;

public:
    DSFactory();
    ~DSFactory();

    /* IUnknown members */
    STDMETHODIMP            QueryInterface(REFIID, LPVOID FAR *);
    STDMETHODIMP_(ULONG)    AddRef();
    STDMETHODIMP_(ULONG)    Release();

    /* IClassFactory members */
    STDMETHODIMP            CreateInstance(LPUNKNOWN, REFIID, LPVOID FAR *);
    STDMETHODIMP            LockServer(BOOL);
};

//
class
DSAddin : public IDSAddIn {
public:
    LPDATAOBJECT m_pDataObj;
	IApplication* m_pApplication;
    LONG m_dwCookie;
	ICommands *m_pCommands;

protected:
    ULONG       m_cRef;
	ITypeInfo  *m_pTInfo;

public:
    DSAddin();
    ~DSAddin();

    /* IUnknown members */
    STDMETHODIMP            QueryInterface(REFIID, LPVOID FAR *);
    STDMETHODIMP_(ULONG)    AddRef();
    STDMETHODIMP_(ULONG)    Release();

    /* IDSAddin members */
	STDMETHODIMP            OnConnection(IApplication* pApp, VARIANT_BOOL bFirstTime,
                                         LONG dwCookie, VARIANT_BOOL* bOnConnection);
	STDMETHODIMP            OnDisconnection(VARIANT_BOOL bLastTime);

	/* IApplicationEvents members */
	STDMETHODIMP            BeforeBuildStart();
	STDMETHODIMP            BuildFinish(long nNumErrors, long nNumWarnings);
	STDMETHODIMP            BeforeApplicationShutDown();
	STDMETHODIMP            DocumentOpen(IDispatch * theDocument);
	STDMETHODIMP            BeforeDocumentClose(IDispatch * theDocument);
	STDMETHODIMP            DocumentSave(IDispatch * theDocument);
	STDMETHODIMP            NewDocument(IDispatch * theDocument);
	STDMETHODIMP            WindowActivate(IDispatch * theWindow);
	STDMETHODIMP            WindowDeactivate(IDispatch * theWindow);
	STDMETHODIMP            WorkspaceOpen();
	STDMETHODIMP            WorkspaceClose();
	STDMETHODIMP            NewWorkspace();
};
typedef DSAddin CUNITDSADDIN, *LPCUNITDSADDIN;

#endif /* __CUNIT_DSADDIN_INCLUDE_H__ */
