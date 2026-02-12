#include "wndproc.hpp"

#include <stdexcept>
#include <d3d11.h>

#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "../utils/debug.hpp"

#include "../sdk/sdk.hpp"

#include "../menu/menu.hpp"
#include "../render/render.hpp"

// CWndProcHook
void CWndProcHook::Initialize() {
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	if (FAILED(g_SwapChain->GetDesc(&SwapChainDesc)))
		throw std::runtime_error("failed to get swapchain desc");

	m_hwnd = SwapChainDesc.OutputWindow;
	if (!m_hwnd)
		throw std::runtime_error("failed to find window");

	ImGui::CreateContext();

	ImGui_ImplWin32_Init(m_hwnd);
	ImGui_ImplDX11_Init(g_Device, g_DeviceContext);

	RenderTarget::Initialize();
	Menu::Get().Initialize();

	m_pWndProcOrig = reinterpret_cast<WNDPROC>(SetWindowLongPtr(m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hkWndProc)));
	if (!m_pWndProcOrig)
		throw std::runtime_error("failed to hook wndproc");

	lg::Success("[+]", "Hook %s initialized successfully.\n", "CWndProcHook");
}

void CWndProcHook::Destroy() {
	SetWindowLongPtrW(m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_pWndProcOrig));

	m_hwnd = nullptr;
	m_pWndProcOrig = nullptr;

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	lg::Success("[-]", "Hook %s removed successfully.\n", "CWndProcHook");
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CWndProcHook::hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

	return CallWindowProc(CWndProcHook::m_pWndProcOrig, hWnd, uMsg, wParam, lParam);
}
