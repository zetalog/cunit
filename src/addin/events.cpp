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
 * @(#)events.h: cunit msdev application events handler
 * $Id: events.cpp,v 1.1.1.1 2004/08/20 05:30:52 zhengl Exp $
 */

#include "comhpr.h"
#include "cunit_addin.h"

/* application events */
STDMETHODIMP DSAddin::BeforeBuildStart() {
    return S_OK;
}

STDMETHODIMP DSAddin::BuildFinish(long nNumErrors, long nNumWarnings) {
    return S_OK;
}

STDMETHODIMP DSAddin::BeforeApplicationShutDown() {
    return S_OK;
}

STDMETHODIMP DSAddin::DocumentOpen(IDispatch* theDocument) {
    return S_OK;
}

STDMETHODIMP DSAddin::BeforeDocumentClose(IDispatch* theDocument) {
    return S_OK;
}

STDMETHODIMP DSAddin::DocumentSave(IDispatch* theDocument) {
    return S_OK;
}

STDMETHODIMP DSAddin::NewDocument(IDispatch * theDocument) {
    return S_OK;
}

STDMETHODIMP DSAddin::WindowDeactivate(IDispatch * theWindow) {
    return S_OK;
}

STDMETHODIMP DSAddin::WindowActivate(IDispatch * theWindow) {
    return S_OK;
}

STDMETHODIMP DSAddin::WorkspaceOpen() {
    return S_OK;
}

STDMETHODIMP DSAddin::WorkspaceClose() {
    return S_OK;
}

STDMETHODIMP DSAddin::NewWorkspace() {
    return S_OK;
}
