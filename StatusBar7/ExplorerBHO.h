#ifndef _EXPLORERBHO_99B69ACD_5ADF_4FD0_863C_158A9D3E736E_
#define _EXPLORERBHO_99B69ACD_5ADF_4FD0_863C_158A9D3E736E_

#include "resource.h"       // main symbols
#include "StatusBar7.h"
#include <Shtypes.h>
#include <Shlguid.h>
#include <Ntquery.h>
#include <Strsafe.h>
#include <shlobj.h>
#include <comdef.h>
#include <shobjidl.h>
#include <shlguid.h>
#include <exdispid.h>


#ifdef _WIN64
#pragma comment(lib,"atlthunk.lib") //resolves error LNK2019 'missing CComStdCallThunkHelper()' for x64 build
#endif

/////////////////////////////////////////////////////////////////////////////
// CExplorerBHO

class ATL_NO_VTABLE CExplorerBHO : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExplorerBHO, &CLSID_ExplorerBHO>,
	public IObjectWithSiteImpl<CExplorerBHO>,
	public IDispatchImpl<IExplorerBHO, &IID_IExplorerBHO, &LIBID_STATUSBAR7Lib,/*wMajor =*/ 1 /*, wMinor = 0*/>
{
public:
	CExplorerBHO(): m_dwEventCookie(0xFEFEFEFE), m_hwStatusBar(NULL) {}

	BEGIN_COM_MAP(CExplorerBHO)
//COM_INTERFACE_ENTRY(IExplorerBHO)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CExplorerBHO) 
	DECLARE_REGISTRY_RESOURCEID(IDR_ExplorerBHO)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

	//IObjectWithSite override
	STDMETHOD(SetSite)(IUnknown *pUnkSite);

	//IDispatch override
	STDMETHOD(Invoke)(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);

	LRESULT WndSubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass);

private:
	HWND m_hwStatusBar;
	CComPtr<IWebBrowser2> m_pWebBrowser2;
	CComPtr<IShellBrowser> m_pShellBrowser;

	//from _IDispEvent
	DWORD m_dwEventCookie;
	HRESULT DispEventAdvise(IUnknown* pUnk, const IID* piid)
	{
		ATLTRACE("DispEventAdvise\n");
		ATLENSURE(m_dwEventCookie == 0xFEFEFEFE);
		return AtlAdvise(pUnk, reinterpret_cast<IUnknown*>(this), *piid, &m_dwEventCookie);
	}
	HRESULT DispEventUnadvise(IUnknown* pUnk, const IID* piid)
	{
		ATLTRACE("DispEventUnadvise\n");
		HRESULT hr = AtlUnadvise(pUnk, *piid, m_dwEventCookie);
		m_dwEventCookie = 0xFEFEFEFE;
		return hr;
	}
};

#endif//_EXPLORERBHO_99B69ACD_5ADF_4FD0_863C_158A9D3E736E_
