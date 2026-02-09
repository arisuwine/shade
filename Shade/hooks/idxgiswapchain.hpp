#pragma once
#include <Windows.h>

class IDXGISwapChain;

class CIDXGISwapChainHook {
private:
	using PresentFunc = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);

	static inline PresentFunc m_pPresentOrig;

	static HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

public:
	static void Register();
	static void Destroy();
};