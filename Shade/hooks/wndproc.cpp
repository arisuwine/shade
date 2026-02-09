#include "wndproc.hpp"

#include <stdexcept>

#include "imgui_impl_win32.h"

#include "../utils/debug.hpp"

// CWndProcHook
void CWndProcHook::Initialize() {
	m_hwnd = FindWindowA("SDL_APP", "Counter-Strike 2");
	if (!m_hwnd)
		throw std::runtime_error("failed to find window");

	m_pWndProcOrig = reinterpret_cast<WNDPROC>(SetWindowLongPtr(m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hkWndProc)));
	if (!m_pWndProcOrig)
		throw std::runtime_error("failed to hook wndproc");

	lg::Success("[+]", "Hook %s initialized successfully.\n", "CWndProcHook");

}

void CWndProcHook::Destroy() {
	SetWindowLongPtr(m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_pWndProcOrig));
	m_hwnd = NULL;

	lg::Success("[-]", "Hook %s removed successfully.\n", "CWndProcHook");
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CWndProcHook::hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

	return m_pWndProcOrig(hWnd, uMsg, wParam, lParam);
}
