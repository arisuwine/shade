//#pragma once
//#include <d3d11.h>
//
//#include "ihook.hpp"
//
//#include "../sdk/modules.hpp"
//#include "../sdk/signatures.hpp"
//
//class GameOverlayHook {
//private:
//    using OriginalPresentFunc = HRESULT(*)(IDXGISwapChain*, UINT, UINT);
//
//    static inline uintptr_t m_pCreateHook;
//    static inline uintptr_t m_pHkPresent;
//    static inline uintptr_t m_pUnHook;
//
//    static inline void* m_pWndProc;
//
//    static inline __int64(__fastcall* CreateHook)(unsigned __int64 pFuncAddress, __int64 pDetourFuncAddress, unsigned __int64* pOriginalFuncAddressOut, int a4, __int64 sFuncName);
//    static inline void(__fastcall* UnHook)(unsigned __int64 pOriginalFuncAddress, bool bLogFailures);
//
//    static inline OriginalPresentFunc PresentOrig;
//    static HRESULT __stdcall hkPresent(IDXGISwapChain* swap_chain, UINT SyncInterval, UINT Flags);
//
//    static inline HWND m_hwnd;
//    static inline WNDPROC WndProcOrig;
//    static LRESULT hkWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//
//    static inline bool m_bIsInit = false;
//
//public:
//    static bool Initialize();
//    static bool Shutdown();
//};
