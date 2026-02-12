#pragma once
#include <Windows.h>

class IDXGISwapChain;

class CIDXGISwapChainHook {
private:
	using PresentFunc = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);

	static inline PresentFunc m_pPresentOrig;

	static HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

	static void Initialize();
	static void Destroy();
public:
	static void Register();
};