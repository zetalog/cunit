#ifndef __CUNIT_EVENTS_H_INCLUDE__
#define __CUNIT_EVENTS_H_INCLUDE__

class ApplicationEvents : public IApplicationEvents
{
public:
	// IApplicationEvents methods
	STDMETHOD(BeforeBuildStart)(THIS);
	STDMETHOD(BuildFinish)(THIS_ long nNumErrors, long nNumWarnings);
	STDMETHOD(BeforeApplicationShutDown)(THIS);
	STDMETHOD(DocumentOpen)(THIS_ IDispatch * theDocument);
	STDMETHOD(BeforeDocumentClose)(THIS_ IDispatch * theDocument);
	STDMETHOD(DocumentSave)(THIS_ IDispatch * theDocument);
	STDMETHOD(NewDocument)(THIS_ IDispatch * theDocument);
	STDMETHOD(WindowActivate)(THIS_ IDispatch * theWindow);
	STDMETHOD(WindowDeactivate)(THIS_ IDispatch * theWindow);
	STDMETHOD(WorkspaceOpen)(THIS);
	STDMETHOD(WorkspaceClose)(THIS);
	STDMETHOD(NewWorkspace)(THIS);
};
typedef ApplicationEvents CUNITAPPEVENTS, *LPCUNITAPPEVENTS;

#endif /* __CUNIT_EVENTS_H_INCLUDE__ :/
