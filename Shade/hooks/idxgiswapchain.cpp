#include "idxgiswapchain.hpp"

#include "wndproc.hpp"

#include "hooks.hpp"

#include "../sdk/sdk.hpp"
#include "../render/render.hpp"

// CIDXGISwapChainHook
void CIDXGISwapChainHook::Register() {
	std::unique_ptr<CVMTHook> hook = std::make_unique<CVMTHook>("CIDXGISwapChainHook", g_pSwapChain, &Initialize, &Destroy);

	hooks::AddVMTHook<PresentFunc>		(hook.get(), 8,		hkPresent,			&m_pPresentOrig);
	hooks::AddVMTHook<ResizeBuffersFunc>(hook.get(), 13,	hkResizeBuffers,	&m_pResizeBuffersOrig);

	lg::Success("[+]", "Hook %s initialized successfully.\n", hook->GetName().data());

	hooks::g_pHooks.push_back(std::move(hook));
}

void CIDXGISwapChainHook::CreateRenderTargetView() {
	ID3D11Texture2D* renderTarget = nullptr;

	g_pSwapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<void**>(&renderTarget));
	g_pDevice->CreateRenderTargetView(renderTarget, nullptr, &g_pTargetView);
	renderTarget->Release();
}

void CIDXGISwapChainHook::Initialize() {
	g_pSwapChain->GetDevice(__uuidof(g_pDevice), reinterpret_cast<void**>(&g_pDevice));
	g_pDevice->GetImmediateContext(&g_pDeviceContext);

	CreateRenderTargetView();

	CWndProcHook::Initialize();
}

void CIDXGISwapChainHook::Destroy() {
	CWndProcHook::Destroy();

	g_pDevice->Release();
	g_pDevice = nullptr;

	g_pDeviceContext->Release();
	g_pDeviceContext = nullptr;

	g_pTargetView->Release();
	g_pTargetView = nullptr;
}

HRESULT __stdcall CIDXGISwapChainHook::hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	if (!g_pTargetView)
		CreateRenderTargetView();

	if (g_pTargetView)
		g_pDeviceContext->OMSetRenderTargets(1, &g_pTargetView, nullptr);

	RenderTarget::BeginScene();

	return m_pPresentOrig(pSwapChain, SyncInterval, Flags);
}

HRESULT __stdcall CIDXGISwapChainHook::hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
	if (g_pTargetView) {
		g_pTargetView->Release();
		g_pTargetView = nullptr;
	}

	HRESULT result = m_pResizeBuffersOrig(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	if (SUCCEEDED(result))
	{
		CreateRenderTargetView();
		lg::Info("[CIDXGISwapChainHook]", "hkResizeBuffers called.\n");
	}

	return result;
}
