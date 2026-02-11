#include "idxgiswapchain.hpp"

#include "wndproc.hpp"

#include "hooks.hpp"

#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "../sdk/sdk.hpp"
#include "../render/render.hpp"
#include "../menu/menu.hpp"

// CIDXGISwapChainHook
void CIDXGISwapChainHook::Register() {
	std::unique_ptr<CVMTHook> hook = std::make_unique<CVMTHook>("CIDXGISwapChainHook", g_SwapChain, nullptr, &Destroy);

	m_pPresentOrig = hook->Enable<PresentFunc>(8, hkPresent);
	if (!m_pPresentOrig)
		throw std::runtime_error("failed to enable Present hook");

	lg::Success("[+]", "Hook %s initialized successfully.\n", hook->GetName().data());

	hooks::g_pHooks.push_back(std::move(hook));
}

HRESULT __stdcall CIDXGISwapChainHook::hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	static bool bIsInit = false;
	if (!g_Device) {
		ID3D11Texture2D* renderTarget = nullptr;

		pSwapChain->GetDevice(__uuidof(g_Device), reinterpret_cast<void**>(&g_Device));
		g_Device->GetImmediateContext(&g_DeviceContext);

		pSwapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<void**>(&renderTarget));
		g_Device->CreateRenderTargetView(renderTarget, nullptr, &g_TargetView);
		renderTarget->Release();
	}

	if (!bIsInit) {
		CWndProcHook::Initialize();

		ImGui::CreateContext();

		ImGui_ImplWin32_Init(CWndProcHook::m_hwnd);
		ImGui_ImplDX11_Init(g_Device, g_DeviceContext);

		RenderTarget::Initialize();
		Menu::Get().Initialize();

		bIsInit = true;
	}

	RenderTarget::BeginScene();

	return m_pPresentOrig(pSwapChain, SyncInterval, Flags);
}

void CIDXGISwapChainHook::Destroy() {

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CWndProcHook::Destroy();

	g_Device->Release();
	g_Device = nullptr;

	g_DeviceContext->Release();
	g_DeviceContext = nullptr;

	g_TargetView->Release();
	g_TargetView = nullptr;
}