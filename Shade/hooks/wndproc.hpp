#pragma once
#include <Windows.h>

class CWndProcHook {
	friend class CIDXGISwapChainHook;

private:
	static inline HWND m_hwnd;
	static inline WNDPROC m_pWndProcOrig;

	static LRESULT CALLBACK hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	static void Initialize();
	static void Destroy();
};