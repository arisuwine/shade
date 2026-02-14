#pragma once
#include <Windows.h>
#include <d3d11.h>

class CVMTHook;

class CIDXGIFactoryHook {
private:
	using CreateSwapChainFunc = HRESULT(__stdcall*)(IDXGIFactory*, IUnknown*, DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**);

	static inline CreateSwapChainFunc m_pCreateSwapChainOrig;
	static inline CVMTHook* m_pSwapChainHook;

	static HRESULT __stdcall hkCreateSwapChain(IDXGIFactory* pFactory, IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain);

public:
	static void Register();
};