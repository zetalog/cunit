#include "comhpr.h"
#include "cunit_types.h"
#include "cunit_commands.h"

/*=========================================================================
 * DSCommands common functions
 *=======================================================================*/
DSCommands::DSCommands() {
    ODS("DSCommands::DSCommands()\r\n");

    m_cRef = 0L;
    m_pDataObj = NULL;
    m_pTInfo = NULL;
}

DSCommands::~DSCommands() {
    if (m_pDataObj)
        m_pDataObj->Release();
    m_pDataObj = NULL;
	if (m_pTInfo != NULL)
		m_pTInfo->Release();
	m_pTInfo = NULL;
}

STDMETHODIMP DSCommands::QueryInterface(REFIID riid, LPVOID FAR *ppv) {
    *ppv = NULL;

    if (IsEqualIID(riid, IID_IUnknown) ||
        IsEqualIID(riid, IID_IDispatch) ||
        IsEqualIID(riid, IID_ICommands)) {
        ODS("DSCommands::QueryInterface()==>IID_IDSCommands\r\n");
        *ppv = this;
    }
    if (*ppv) {
        AddRef();
        return NOERROR;
    }

    ODS("DSCommands::QueryInterface()==>Unknown Interface!\r\n");

    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) DSCommands::AddRef() {
    ODS("DSCommands::AddRef()\r\n");

    return ++m_cRef;
}

STDMETHODIMP_(ULONG) DSCommands::Release() {
    ODS("DSCommands::Release()\r\n");

    if (--m_cRef)
        return m_cRef;
    
    delete this;
    return 0L;
}

STDMETHODIMP DSCommands::GetTypeInfoCount(UINT FAR* pctinfo) {
    ODS("DSCommands::GetTypeInfoCount()\r\n");

    *pctinfo = 1;
    return NOERROR;
}

STDMETHODIMP DSCommands::GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo FAR* FAR* pptinfo) {
    ODS("DSCommands::GetTypeInfo()\r\n");

    if (0 != itinfo)
        return ResultFromScode(TYPE_E_ELEMENTNOTFOUND);

    if (NULL == pptinfo)
        return ResultFromScode(E_POINTER);

    *pptinfo = NULL;
    HRESULT hr = NOERROR;

    if (m_pTInfo == NULL) {
        hr = LoadTypeInfo(&m_pTInfo, OLESTR("cunit_addin.tlb"),
                          LIBID_cunit_addin, IID_ICommands);
        if (FAILED(hr))
            return hr;
    }
    *pptinfo = m_pTInfo;
    m_pTInfo->AddRef();

    /* ignore the LCID */
    return hr;
}

STDMETHODIMP DSCommands::GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames,
                                       UINT cNames, LCID lcid, DISPID FAR* rgdispid) {
    ODS("DSCommands::GetIDsOfNames()\r\n");

    HRESULT hr = NOERROR;

    if (IID_NULL != riid)
        return ResultFromScode(DISP_E_UNKNOWNINTERFACE);

    if (m_pTInfo == NULL) {
        hr = LoadTypeInfo(&m_pTInfo, OLESTR("cunit_addin.tlb"),
                          LIBID_cunit_addin, IID_ICommands);
        if (FAILED(hr))
            return hr;
    }

    if (SUCCEEDED(hr)) {
        return DispGetIDsOfNames(m_pTInfo, rgszNames, cNames, rgdispid);
    }

    return hr;
}

STDMETHODIMP DSCommands::Invoke(DISPID dispid, REFIID riid, LCID lcid, WORD wFlags,
                                DISPPARAMS FAR* pdispparams, VARIANT FAR* pvarResult,
                                EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr) {
    ODS("DSCommands::Invoke()\r\n");

    HRESULT hr = NOERROR;

    /* riid is supposed to be IID_NULL always */
    if (IID_NULL != riid)
        return ResultFromScode(DISP_E_UNKNOWNINTERFACE);

    /* Get the ITypeInfo for lcid */
    if (m_pTInfo == NULL) {
        hr = LoadTypeInfo(&m_pTInfo, OLESTR("cunit_addin.tlb"),
                          LIBID_cunit_addin, IID_ICommands);
        if (FAILED(hr))
            return hr;
    }

    return m_pTInfo->Invoke(this, dispid, wFlags,
                            pdispparams, pvarResult, pexcepinfo, puArgErr);
}

STDMETHODIMP DSCommands::RunUnitTest()  {
	m_pApplication->EnableModeless(VARIANT_FALSE);
	MessageBox(NULL, "Run Test Command invoked.", "cunit", MB_OK | MB_ICONINFORMATION);
	m_pApplication->EnableModeless(VARIANT_TRUE);
	return S_OK;
}

STDMETHODIMP DSCommands::set_Application(IApplication *papp) {
    m_pApplication = papp;
    return S_OK;
}

STDMETHODIMP DSCommands::get_Application(IApplication **ppapp) {
    if (NULL == ppapp)
        return ResultFromScode(E_POINTER);
    *ppapp = m_pApplication;
    return S_OK;
}

STDMETHODIMP DSCommands::GotoSourceLine(BSTR bstrFileName, int nLineNumber) {
    HRESULT hResult = S_OK;
    
    try {
        IDocuments *pIDocuments;
        ITextDocument *pITextDocu;
        ITextSelection *pITextSel;
        VARIANT var;
        
        var.vt = VT_EMPTY;
        
        m_pApplication->get_Documents((IDispatch **)&pIDocuments);
        pIDocuments->Open(bstrFileName, var,
                          var, (IDispatch **)&pITextDocu);
        pITextDocu->get_Selection((IDispatch **)&pITextSel);
        pITextSel->GoToLine(nLineNumber, var);
    } catch (const _com_error) {
        hResult = E_FAIL;
    }
    
    return hResult;
}
