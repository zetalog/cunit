#include "comhpr.h"
#include <ole2.h>

/*
 * Initialize GUIDs (should be done only and at-least once per DLL/EXE)
 */
#pragma data_seg(".text")
#define INITGUID
#include <initguid.h>
#include "cunit_addin.h"
#pragma data_seg()

#include <tchar.h>
#include "cunit_resource.h"

/*=========================================================================
 * Variable definitions
 *=======================================================================*/
static UINT _addin_initialized = 0;
static UINT _addin_refcount = 0;

/* Handle to this DLL. */
extern "C" HINSTANCE _addin_instance = NULL;

extern "C"
int APIENTRY DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        ODS("In DLLMain, DLL_PROCESS_ATTACH\r\n");

        /* Extension DLL one-time initialization */
        if (!_addin_initialized) {
            _addin_instance = instance;
            _addin_initialized++;
            DisableThreadLibraryCalls(instance);
        }
    } else if (reason == DLL_PROCESS_DETACH) {
        ODS("In DLLMain, DLL_PROCESS_DETACH\r\n");
        _addin_initialized--;
        if (!_addin_initialized) {
        }
    }
    
    return 1;
}

/*=========================================================================
 * COM functions
 *=======================================================================*/
STDAPI DllCanUnloadNow(void) {
    ODS("In DLLCanUnloadNow\r\n");
    
    return (_addin_refcount == 0 ? S_OK : S_FALSE);
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppvOut) {
    ODS("In DllGetClassObject\r\n");
    
    *ppvOut = NULL;
    if (IsEqualIID(rclsid, CLSID_DSAddIn)) {
        DSFactory *pcf = new DSFactory;
        return pcf->QueryInterface(riid, ppvOut);
    }
    
    return S_OK;//CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllRegisterServer(void) {
#define CUNIT_DESC_LENGTH       1024
	HRESULT hRes = S_OK;
    TCHAR desc[CUNIT_DESC_LENGTH+1] = _T("DSAddin");
    HKEY hKey;
    DWORD ret;
	
    ODS("In DllRegisterServer\r\n");
    
    ModuleRegisterClass(_addin_instance, CLSID_DSAddIn,
                        "cunit.DSAddIn.1", "cunit.DSAddIn",
                        IDS_CUNIT_ADDIN_LONGNAME, THREADFLAGS_BOTH);
    ModuleRegisterTypeLib(_addin_instance, 0);
	/*
     * Register description of this add-in object in its own
	 * "/Description" subkey.
	 * TODO:  If you add more add-ins to this module, you need
	 *  to register all of their descriptions, each description
	 *  in each add-in object's registry CLSID entry:
	 *  HKEY_CLASSES_ROOT\Clsid\{add-in CLSID}\Description="add-in description"
     */
    
    /* Open the registry */
    ret = RegOpenKeyEx(HKEY_CLASSES_ROOT,
                       _T("CLSID"),
                       0,
                       KEY_READ | KEY_WRITE,
                       &hKey);
    
    if (ret == ERROR_SUCCESS) {
        USES_CONVERSION;
        LPOLESTR lpOleStr;
        StringFromCLSID(CLSID_DSAddIn, &lpOleStr);
        LPTSTR key = OLE2T(lpOleStr);
        
        ret = RegOpenKeyEx(hKey,
                           key,
                           0,
                           KEY_READ | KEY_WRITE,
                           &hKey);
        if (ret == ERROR_SUCCESS) {
            LoadString(_addin_instance, IDS_CUNIT_ADDIN_DESCRIPTION, desc, CUNIT_DESC_LENGTH);
            RegSetKeyValue(hKey, _T("Description"), NULL, desc);
        }
        CoTaskMemFree(lpOleStr);
    }
    if (ret != ERROR_SUCCESS)
        hRes = HRESULT_FROM_WIN32(ret);
    
    RegCloseKey(hKey);
    
    return hRes;
}

STDAPI DllUnregisterServer(void) {
	HRESULT hRes = S_OK;
    ModuleUnRegisterTypeLib(_addin_instance, 0);
    ModuleUnregisterClass(_addin_instance, CLSID_DSAddIn,
                          "cunit.DSAddIn.1", "cunit.DSAddIn");
    /*
    ModuleUnregisterClass(_addin_instance, CLSID_DSCommands,
                          "cunit.DSCommands.1", "cunit.DSCommands");
    */
	return hRes;
}

/*=========================================================================
 * DSFactory
 *=======================================================================*/
DSFactory::DSFactory() {
    ODS("DSFactory::DSFactory()\r\n");

    m_cRef = 0L;
    _addin_refcount++;
}

DSFactory::~DSFactory() {
    _addin_refcount--;
}

STDMETHODIMP DSFactory::QueryInterface(REFIID riid,
                                                 LPVOID FAR *ppv) {
    ODS("DSFactory::QueryInterface()\r\n");

    *ppv = NULL;

    /* Any interface on this object is the object pointer */

    if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IClassFactory)) {
        *ppv = (LPCLASSFACTORY)this;
        AddRef();
        return NOERROR;
    }

    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) DSFactory::AddRef() {
    return ++m_cRef;
}

STDMETHODIMP_(ULONG) DSFactory::Release() {
    if (--m_cRef)
        return m_cRef;

    delete this;
    return 0L;
}

STDMETHODIMP DSFactory::CreateInstance(LPUNKNOWN pUnkOuter,
                                       REFIID riid,
                                       LPVOID *ppvObj) {
    ODS("DSFactory::CreateInstance()\r\n");

	*ppvObj = NULL;

    if (pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    /* Create the DSAddin object */
    LPCUNITDSADDIN pAddin = new DSAddin();

    if (NULL == pAddin)
        return E_OUTOFMEMORY;
   
	return pAddin->QueryInterface(riid, ppvObj);
}

STDMETHODIMP DSFactory::LockServer(BOOL fLock) {
    return NOERROR;
}

/*=========================================================================
 * DSAddin common functions
 *=======================================================================*/
DSAddin::DSAddin() {
    ODS("DSAddin::DSAddin()\r\n");

    m_cRef = 0L;
    m_pDataObj = NULL;
    m_pTInfo = NULL;
    m_pCommands = NULL;
}

DSAddin::~DSAddin() {
    if (m_pDataObj)
        m_pDataObj->Release();
    m_pDataObj = NULL;
	if (m_pTInfo != NULL)
		m_pTInfo->Release();
	m_pTInfo = NULL;
}

STDMETHODIMP DSAddin::QueryInterface(REFIID riid, LPVOID FAR *ppv) {
    *ppv = NULL;

    if (IsEqualIID(riid, IID_IUnknown) ||
        IsEqualIID(riid, IID_IDSAddIn)) {
        ODS("DSAddin::QueryInterface()==>IID_IDSAddin\r\n");
        *ppv = this;
    }
    if (*ppv) {
        AddRef();
        return NOERROR;
    }

    ODS("DSAddin::QueryInterface()==>Unknown Interface!\r\n");

    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) DSAddin::AddRef() {
    ODS("DSAddin::AddRef()\r\n");

    return ++m_cRef;
}

STDMETHODIMP_(ULONG) DSAddin::Release() {
    ODS("DSAddin::Release()\r\n");

    if (--m_cRef)
        return m_cRef;
    
    delete this;
    return 0L;
}
