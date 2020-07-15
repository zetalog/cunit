/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Apr 02 20:36:19 2004
 */
/* Compiler settings for J:\cunit\src\addin\cunit_addin.odl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __cunit_types_h__
#define __cunit_types_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICommands_FWD_DEFINED__
#define __ICommands_FWD_DEFINED__
typedef interface ICommands ICommands;
#endif 	/* __ICommands_FWD_DEFINED__ */


#ifndef __DSCommands_FWD_DEFINED__
#define __DSCommands_FWD_DEFINED__

#ifdef __cplusplus
typedef class DSCommands DSCommands;
#else
typedef struct DSCommands DSCommands;
#endif /* __cplusplus */

#endif 	/* __DSCommands_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __cunit_addin_LIBRARY_DEFINED__
#define __cunit_addin_LIBRARY_DEFINED__

/* library cunit_addin */
/* [helpstring][version][uuid] */ 


DEFINE_GUID(LIBID_cunit_addin,0x2CB2D72E,0xC564,0x4054,0x8B,0xAB,0x18,0xBF,0x48,0x8C,0x48,0x04);

#ifndef __ICommands_INTERFACE_DEFINED__
#define __ICommands_INTERFACE_DEFINED__

/* interface ICommands */
/* [object][dual][oleautomation][uuid] */ 


DEFINE_GUID(IID_ICommands,0x732E82B3,0x2500,0x40B3,0x9A,0xFC,0x6C,0x5B,0xD1,0x93,0xF0,0x0D);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("732E82B3-2500-40B3-9AFC-6C5BD193F00D")
    ICommands : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RunUnitTest( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICommands __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICommands __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICommands __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICommands __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICommands __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICommands __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICommands __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RunUnitTest )( 
            ICommands __RPC_FAR * This);
        
        END_INTERFACE
    } ICommandsVtbl;

    interface ICommands
    {
        CONST_VTBL struct ICommandsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommands_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommands_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommands_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommands_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICommands_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICommands_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICommands_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICommands_RunUnitTest(This)	\
    (This)->lpVtbl -> RunUnitTest(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE ICommands_RunUnitTest_Proxy( 
    ICommands __RPC_FAR * This);


void __RPC_STUB ICommands_RunUnitTest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommands_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DSCommands,0xF7337CBB,0xA795,0x4CC3,0xB2,0xD4,0x67,0xDA,0xAB,0x78,0x81,0x5C);

#ifdef __cplusplus

class DECLSPEC_UUID("F7337CBB-A795-4CC3-B2D4-67DAAB78815C")
DSCommands;
#endif
#endif /* __cunit_addin_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
