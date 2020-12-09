#include "comhpr.h"

static LPWSTR WINAPI _A2WHelper(LPWSTR lpw, LPCSTR lpa, int nChars, UINT acp) {
	/*
     * verify that no illegal character present
	 * since lpw was allocated based on the size of lpa
	 * don't worry about the number of chars
     */
	lpw[0] = '\0';
	MultiByteToWideChar(acp, 0, lpa, -1, lpw, nChars);
	return lpw;
}

static LPSTR WINAPI _W2AHelper(LPSTR lpa, LPCWSTR lpw, int nChars, UINT acp) {
	/*
     * verify that no illegal character present
     * since lpa was allocated based on the size of lpw
     * don't worry about the number of chars
     */
	lpa[0] = '\0';
	WideCharToMultiByte(acp, 0, lpw, -1, lpa, nChars, NULL, NULL);
	return lpa;
}

LPWSTR WINAPI A2WHelper(LPWSTR lpw, LPCSTR lpa, int nChars) {
	return _A2WHelper(lpw, lpa, nChars, CP_ACP);
}

LPSTR WINAPI W2AHelper(LPSTR lpa, LPCWSTR lpw, int nChars) {
	return _W2AHelper(lpa, lpw, nChars, CP_ACP);
}

LONG RegSetKeyValue(HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName, LPCTSTR lpszValue) {
    HKEY hSubKey = NULL;
    DWORD dw;
    LONG lRes;
    
    lRes = RegCreateKeyEx(hKey, lpszKeyName, 0, REG_NONE, REG_OPTION_NON_VOLATILE,
                          KEY_SET_VALUE, NULL, &hSubKey, &dw);
    if (lRes == ERROR_SUCCESS) {
        RegSetValueEx(hSubKey, lpszValueName, NULL, REG_SZ,
                      (BYTE * const)lpszValue, (lstrlen(lpszValue)+1)*sizeof (TCHAR));
        RegCloseKey(hSubKey);
        return lRes;
    }
    return lRes;
}

static LONG RegRecurseDeleteKey(HKEY hKey, LPCTSTR lpszKey) {
    HKEY hSubKey = NULL;
    FILETIME time;
    DWORD dwSize = 256;
    TCHAR szBuffer[256];
    LONG lRes = ERROR_SUCCESS;
    
    lRes = RegOpenKeyEx(hKey, lpszKey, 0, KEY_READ | KEY_WRITE, &hSubKey);
    if (lRes != ERROR_SUCCESS)
        return lRes;
    while (RegEnumKeyEx(hKey, 0, szBuffer, &dwSize, NULL, NULL, NULL,
                        &time) == ERROR_SUCCESS) {
        lRes = RegRecurseDeleteKey(hKey, szBuffer);
        if (lRes != ERROR_SUCCESS)
            return lRes;
        dwSize = 256;
    }
    RegCloseKey(hSubKey);
    return RegDeleteKey(hKey, lpszKey);
}

HRESULT RegisterProgID(LPCTSTR lpszCLSID, LPCTSTR lpszProgID, LPCTSTR lpszUserDesc) {
    DWORD dw;
    HKEY hKey = NULL;
    LONG lRes;
    
    lRes = RegCreateKeyEx(HKEY_CLASSES_ROOT, lpszProgID, 0, REG_NONE,
        REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hKey, &dw);
    if (lRes == ERROR_SUCCESS) {
        RegSetValueEx(hKey, NULL, NULL, REG_SZ,
                      (BYTE * const)lpszUserDesc, (lstrlen(lpszUserDesc)+1)*sizeof (TCHAR));
        RegSetKeyValue(hKey, _T("CLSID"), NULL, lpszCLSID);
        RegCloseKey(hKey);
        return S_OK;
    }
    return HRESULT_FROM_WIN32(lRes);
}

HRESULT WINAPI ModuleRegisterClass(HINSTANCE hInstance, const CLSID& clsid, LPCTSTR lpszProgID,
                                   LPCTSTR lpszVerIndProgID, UINT nDescID, DWORD dwFlags) {
    static const TCHAR szProgID[] = _T("ProgID");
    static const TCHAR szVIProgID[] = _T("VersionIndependentProgID");
    static const TCHAR szLS32[] = _T("LocalServer32");
    static const TCHAR szIPS32[] = _T("InprocServer32");
    static const TCHAR szThreadingModel[] = _T("ThreadingModel");
    static const TCHAR szAUTPRX32[] = _T("AUTPRX32.DLL");
    static const TCHAR szApartment[] = _T("Apartment");
    static const TCHAR szBoth[] = _T("both");
    HRESULT hRes = S_OK;
    TCHAR szDesc[256];
    TCHAR szModule[_MAX_PATH];
    HKEY hKey = NULL, hSubKey = NULL;
    LPOLESTR lpOleStr;
    LPTSTR lpsz = NULL;
    LONG lRes = ERROR_SUCCESS;
    DWORD dw;
    USES_CONVERSION;
    
    LoadString(hInstance, nDescID, szDesc, 256);
    GetModuleFileName(hInstance, szModule, _MAX_PATH);
    StringFromCLSID(clsid, &lpOleStr);
    lpsz = OLE2T(lpOleStr);
    
    hRes = RegisterProgID(lpsz, lpszProgID, szDesc);
    if (hRes == S_OK)
        hRes = RegisterProgID(lpsz, lpszVerIndProgID, szDesc);
    if (hRes == S_OK) {
        lRes = RegOpenKeyEx(HKEY_CLASSES_ROOT, _T("CLSID"), 0, KEY_READ | KEY_WRITE, &hKey);
        if (lRes == ERROR_SUCCESS) {
            lRes = RegCreateKeyEx(hKey, lpsz, 0, REG_NONE, REG_OPTION_NON_VOLATILE,
                                  KEY_SET_VALUE, NULL, &hSubKey, &dw);
            if (lRes == ERROR_SUCCESS) {
                RegSetValueEx(hSubKey, NULL, NULL, REG_SZ,
		                      (BYTE * const)szDesc, (lstrlen(szDesc)+1)*sizeof (TCHAR));
                RegSetKeyValue(hSubKey, szProgID, NULL, lpszProgID);
                RegSetKeyValue(hSubKey, szVIProgID, NULL, lpszVerIndProgID);
                
                /* register as EXE */
                if ((hInstance == NULL) || (hInstance == GetModuleHandle(NULL))) {
                    /* Convert to short path to work around bug in NT4's CreateProcess */
                    TCHAR szModuleShort[_MAX_PATH];
                    int cbShortName = GetShortPathName(szModule, szModuleShort, _MAX_PATH);
                    TCHAR* pszModule;
                    
                    if (cbShortName == _MAX_PATH) {
                        RegCloseKey(hSubKey);
                        RegCloseKey(hKey);
                        return E_OUTOFMEMORY;
                    }
                    pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? szModule : szModuleShort;
                    RegSetKeyValue(hSubKey, szLS32, NULL, pszModule);
                } else {
                    RegSetKeyValue(hSubKey, szIPS32, NULL, (dwFlags & AUTPRXFLAG) ? szAUTPRX32 : szModule);
                    LPCTSTR lpszModel = (dwFlags & THREADFLAGS_BOTH) ? szBoth :
                    (dwFlags & THREADFLAGS_APARTMENT) ? szApartment : NULL;
                    if (lpszModel != NULL)
                        RegSetKeyValue(hSubKey, szIPS32, szThreadingModel, lpszModel);
                }
            }
        }
    }
    CoTaskMemFree(lpOleStr);
    if (lRes != ERROR_SUCCESS)
        hRes = HRESULT_FROM_WIN32(lRes);
    if (hSubKey) RegCloseKey(hSubKey);
    if (hKey) RegCloseKey(hKey);
    return hRes;
}

HRESULT WINAPI ModuleUnregisterClass(HINSTANCE hInstance, const CLSID& clsid,
                                     LPCTSTR lpszProgID, LPCTSTR lpszVerIndProgID) {
    HKEY hKey = NULL;
    LPOLESTR lpOleStr;
    USES_CONVERSION;
    LPTSTR lpsz = NULL;
    LONG lRes = ERROR_SUCCESS;
    
    if (lpszProgID != NULL && lstrcmpi(lpszProgID, _T("")))
        RegRecurseDeleteKey(HKEY_CLASSES_ROOT, lpszProgID);
    if (lpszVerIndProgID != NULL && lstrcmpi(lpszVerIndProgID, _T("")))
        RegRecurseDeleteKey(HKEY_CLASSES_ROOT, lpszVerIndProgID);
    StringFromCLSID(clsid, &lpOleStr);
    lpsz = OLE2T(lpOleStr);
    lRes = RegOpenKeyEx(HKEY_CLASSES_ROOT, _T("CLSID"), 0, KEY_READ | KEY_WRITE, &hKey);
    if (lRes == ERROR_SUCCESS)
        RegRecurseDeleteKey(hKey, lpsz);
    CoTaskMemFree(lpOleStr);
    if (hKey) RegCloseKey(hKey);
    return S_OK;
}

WINAPI ModuleLoadTypeLib(HINSTANCE hInstance, LPCOLESTR lpszIndex,
                         BSTR* pbstrPath, ITypeLib** ppTypeLib) {
    USES_CONVERSION;
    TCHAR szModule[_MAX_PATH+10];
    LPOLESTR lpszModule;
    HRESULT hr;
    
    *pbstrPath = NULL;
    *ppTypeLib = NULL;
    GetModuleFileName(hInstance, szModule, _MAX_PATH);
    if (lpszIndex != NULL)
        lstrcat(szModule, OLE2CT(lpszIndex));
    lpszModule = T2OLE(szModule);
    hr = LoadTypeLib(lpszModule, ppTypeLib);
    if (!SUCCEEDED(hr)) {
        /* typelib not in module, try <module>.tlb instead */
        LPTSTR lpszExt = NULL;
        LPTSTR lpsz;
        for (lpsz = szModule; *lpsz != NULL; lpsz = CharNext(lpsz)) {
            if (*lpsz == _T('.'))
                lpszExt = lpsz;
        }
        if (lpszExt == NULL)
            lpszExt = lpsz;
        lstrcpy(lpszExt, _T(".tlb"));
        lpszModule = T2OLE(szModule);
        hr = LoadTypeLib(lpszModule, ppTypeLib);
    }
    if (SUCCEEDED(hr))
        *pbstrPath = OLE2BSTR(lpszModule);
    return hr;
}

WINAPI ModuleUnRegisterTypeLib(HINSTANCE hInstance, LPCOLESTR lpszIndex) {
    typedef HRESULT (WINAPI *PFNRTL)(REFGUID, WORD, WORD, LCID, SYSKIND);
    BSTR bstrPath;
    ITypeLib *pTypeLib;
    HRESULT hr = ModuleLoadTypeLib(hInstance, lpszIndex, &bstrPath, &pTypeLib);
    if (SUCCEEDED(hr)) {
        TLIBATTR* ptla;
        HRESULT hr = pTypeLib->GetLibAttr(&ptla);
        if (SUCCEEDED(hr)) {
            HINSTANCE h = LoadLibrary(_T("oleaut32.dll"));
            if (h != NULL) {
                PFNRTL pfn = (PFNRTL) GetProcAddress(h, "UnRegisterTypeLib");
                if (pfn != NULL)
                    hr = pfn(ptla->guid, ptla->wMajorVerNum, ptla->wMinorVerNum, ptla->lcid, ptla->syskind);
                FreeLibrary(h);
            }
            pTypeLib->ReleaseTLibAttr(ptla);
        }
    }
    return hr;
}

static UINT WINAPI GetDirLen(LPCOLESTR lpszPathName) {
    /* always capture the complete file name including extension (if present) */
    LPCOLESTR lpszTemp = lpszPathName;
    for (LPCOLESTR lpsz = lpszPathName; *lpsz != NULL;) {
        LPCOLESTR lp = CharNextO(lpsz);
        /* remember last directory/drive separator */
        if (*lpsz == OLESTR('\\') || *lpsz == OLESTR('/') || *lpsz == OLESTR(':'))
            lpszTemp = lp;
        lpsz = lp;
    }
    
    return lpszTemp-lpszPathName;
}

WINAPI ModuleRegisterTypeLib(HINSTANCE hInstance, LPCOLESTR lpszIndex) {
    BSTR bstrPath;
    ITypeLib *pTypeLib;
    HRESULT hr = ModuleLoadTypeLib(hInstance, lpszIndex, &bstrPath, &pTypeLib);
    if (SUCCEEDED(hr)) {
        OLECHAR szDir[_MAX_PATH];
        ocscpy(szDir, bstrPath);
        szDir[GetDirLen(szDir)] = 0;
        hr = RegisterTypeLib(pTypeLib, bstrPath, szDir);
    }
    return hr;
}

VARIANT VariantString(BSTR str) {
   VARIANT var;
   VariantInit(&var);
   V_BSTR(&var) = SysAllocString(str);
   V_VT(&var) = VT_BSTR;
   return var;
}

/*
 * LoadTypeInfo
 *
 *  Purpose:
 *   Gets type information of an object's interface from type library.
 *
 * Parameters:
 *  ppunkStdDispatch    Returns type information.
 *  clsid               Interface id of object in type library. 
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT LoadTypeInfo(ITypeInfo FAR* FAR* pptinfo, OLECHAR FAR* file, REFGUID guid, REFCLSID clsid) {                          
    HRESULT hr;
    LPTYPELIB ptlib = NULL;
    LPTYPEINFO ptinfo = NULL;

    *pptinfo = NULL;     
    
    /* Load Type Library. */
    hr = LoadRegTypeLib(guid, 1, 0, 0x09, &ptlib);
    if (FAILED(hr))  {
        /*
         * if it wasn't registered, try to load it from the path
         * if this succeeds, it will have registered the type library for us
         * for the next time.
         */
        hr = LoadTypeLib(file, &ptlib); 
        if (FAILED(hr))
            return hr;
    }
    
    /* Get type information for interface of the object. */
    hr = ptlib->GetTypeInfoOfGuid(clsid, &ptinfo);
    if (FAILED(hr))  { 
        ptlib->Release();
        return hr;
    }   

    ptlib->Release();
    *pptinfo = ptinfo;
    return NOERROR;
}
