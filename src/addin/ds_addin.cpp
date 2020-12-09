#include "comhpr.h"
#include "cunit_addin.h"
#include "cunit_commands.h"
#include "cunit_resource.h"

STDMETHODIMP DSAddin::OnConnection(IApplication* pApp, VARIANT_BOOL bFirstTime,
                                   LONG dwCookie, VARIANT_BOOL* OnConnection)
{
    /* Store info passed into addin */
    IApplication* pApplication = NULL;
    if (FAILED(pApp->QueryInterface(IID_IApplication, (void**) &pApplication))
        || pApplication == NULL) {
        *OnConnection = VARIANT_FALSE;
        return S_OK;
    }
    
    m_pApplication = pApplication;
    m_dwCookie = dwCookie;
    
    /* Create command, send info back to DevStudio */
    /*
    if (FAILED(CoCreateInstance(__uuidof(DSCommands),
                                NULL,
                                CLSCTX_INPROC_SERVER,
                                __uuidof(ICommands),
                                (void**)&m_pCommands))) {
        *OnConnection = VARIANT_FALSE;
        return S_OK;
    }
    */
    /* hack! hack! */
    m_pCommands = new DSCommands();
    ((DSCommands *)m_pCommands)->set_Application(pApplication);

    if (FAILED(pApplication->SetAddInInfo((long)_addin_instance,
        m_pCommands, IDR_TOOLBAR_MEDIUM, IDR_TOOLBAR_LARGE, m_dwCookie))) {
        *OnConnection = VARIANT_FALSE;
        return S_OK;
    }

    /* Inform DevStudio of the commands we implement */
    /*
     * TODO: Replace the AddCommand call below with a series of calls,
     *  one for each command your add-in will add.
     */
    /*
     * The command name should not be localized to other languages.  The 
     * tooltip, command description, and other strings related to this
     * command are stored in the string table (IDS_CMD_STRING) and should
     * be localized.
     */
    LPCTSTR szCommand = _T("cunit_command");
    LPCTSTR szMethod = _T("RunUnitTest");
	USES_CONVERSION;
    VARIANT_BOOL bRet;
    TCHAR szCmdString[512+1];
    TCHAR *lpszCommand = NULL;
    BSTR bstrCommand = NULL;
    BSTR bstrMethod = NULL;
    LPOLESTR lpOleStr = NULL;
    UINT nLength = 0;

    lpOleStr = T2OLE(szMethod);
    bstrMethod = OLE2BSTR(lpOleStr);

    LoadString(_addin_instance, IDS_CMD_STRING, szCmdString, 512);
    nLength = _tcslen(szCmdString) + _tcslen(szCommand);

    lpszCommand = (TCHAR *)malloc(sizeof (TCHAR) * nLength);
    _tcscpy(lpszCommand, szCommand);
    _tcscat(lpszCommand, szCmdString);

    lpOleStr = T2OLE(lpszCommand);
    bstrCommand = OLE2BSTR(lpOleStr);
    //CoTaskMemFree(lpOleStr1);
    //CoTaskMemFree(lpOleStr2);

    if (FAILED(pApplication->AddCommand(bstrCommand, bstrMethod, 0, m_dwCookie, &bRet))) {
        /*
         * AddCommand failed because a command with this name already
         * exists.
         */
        *OnConnection = VARIANT_FALSE;
        if (bstrCommand) SysFreeString(bstrCommand);
        if (bstrMethod) SysFreeString(bstrMethod);
        return S_OK;
    }
    
    if (bstrCommand) SysFreeString(bstrCommand);
    if (bstrMethod) SysFreeString(bstrMethod);

    /*
     * Add toolbar buttons only if this is the first time the add-in
     * is being loaded.  Toolbar buttons are automatically remembered
     * by Developer Studio from session to session, so we should only
     * add the toolbar buttons once.
     */
    if (bFirstTime == VARIANT_TRUE) {
        BSTR bstrCmdName = NULL;
        lpOleStr = T2OLE(szCommand);
        bstrCmdName = OLE2BSTR(lpOleStr);

        pApplication->AddCommandBarButton(dsGlyph, bstrCmdName, m_dwCookie);
        if (bstrCmdName) SysFreeString(bstrCmdName);
        //CoTaskMemFree(lpOleStr);
    }
    
    *OnConnection = VARIANT_TRUE;
    return S_OK;
}

/*
 * This is called on shut-down, and also when the user unloads the add-in
 */
STDMETHODIMP DSAddin::OnDisconnection(VARIANT_BOOL bLastTime)
{
	/* TODO: Perform any cleanup work here */
    m_pApplication->Release();
	return S_OK;
}
