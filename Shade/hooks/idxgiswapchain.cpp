#include "idxgiswapchain.hpp"

#include "wndproc.hpp"

#include "hooks.hpp"

#include "../sdk/sdk.hpp"
#include "../render/render.hpp"

// CIDXGISwapChainHook
void CIDXGISwapChainHook::Register() {
	std::unique_ptr<CVMTHook> hook = std::make_unique<CVMTHook>("CIDXGISwapChainHook", g_SwapChain, &Initialize, &Destroy);

	m_pPresentOrig = hook->Enable<PresentFunc>(8, hkPresent);
	if (!m_pPresentOrig)
		throw std::runtime_error("failed to enable Present hook");

	lg::Success("[+]", "Hook %s initialized successfully.\n", hook->GetName().data());

	hooks::g_pHooks.push_back(std::move(hook));
}

void CIDXGISwapChainHook::Initialize() {
	ID3D11Texture2D* renderTarget = nullptr;

	g_SwapChain->GetDevice(__uuidof(g_Device), reinterpret_cast<void**>(&g_Device));
	g_Device->GetImmediateContext(&g_DeviceContext);

	g_SwapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<void**>(&renderTarget));
	g_Device->CreateRenderTargetView(renderTarget, nullptr, &g_TargetView);
	renderTarget->Release();

	CWndProcHook::Initialize();
}

void CIDXGISwapChainHook::Destroy() {
	CWndProcHook::Destroy();

	g_Device->Release();
	g_Device = nullptr;

	g_DeviceContext->Release();
	g_DeviceContext = nullptr;

	g_TargetView->Release();
	g_TargetView = nullptr;
}

HRESULT __stdcall CIDXGISwapChainHook::hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	RenderTarget::BeginScene();

	return m_pPresentOrig(pSwapChain, SyncInterval, Flags);
}
