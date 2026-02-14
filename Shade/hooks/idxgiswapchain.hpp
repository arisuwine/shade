#pragma once
#include <Windows.h>
#include <d3d11.h>

class CIDXGISwapChainHook {
private:
	using PresentFunc		= HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);
	using ResizeBuffersFunc = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

	static inline PresentFunc		m_pPresentOrig;
	static inline ResizeBuffersFunc m_pResizeBuffersOrig;

	static HRESULT __stdcall hkPresent		(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	static HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

	static void CreateRenderTargetView();

	static void Initialize();
	static void Destroy();
public:
	static void Register();
};