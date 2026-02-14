#include "idxgiswapchain.hpp"

#include "wndproc.hpp"

#include "hooks.hpp"

#include "../sdk/sdk.hpp"
#include "../render/render.hpp"

// CIDXGISwapChainHook
void CIDXGISwapChainHook::Register() {
	std::unique_ptr<CVMTHook> hook = std::make_unique<CVMTHook>("CIDXGISwapChainHook", g_SwapChain, &Initialize, &Destroy);

	hooks::AddVMTHook<PresentFunc>		(hook.get(), 8,		hkPresent,			&m_pPresentOrig);
	hooks::AddVMTHook<ResizeBuffersFunc>(hook.get(), 13,	hkResizeBuffers,	&m_pResizeBuffersOrig);

	lg::Success("[+]", "Hook %s initialized successfully.\n", hook->GetName().data());

	hooks::g_pHooks.push_back(std::move(hook));
}

void CIDXGISwapChainHook::CreateRenderTargetView() {
	ID3D11Texture2D* renderTarget = nullptr;

	g_SwapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<void**>(&renderTarget));
	g_Device->CreateRenderTargetView(renderTarget, nullptr, &g_TargetView);
	renderTarget->Release();
}

void CIDXGISwapChainHook::Initialize() {
	g_SwapChain->GetDevice(__uuidof(g_Device), reinterpret_cast<void**>(&g_Device));
	g_Device->GetImmediateContext(&g_DeviceContext);

	CreateRenderTargetView();

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
	if (!g_TargetView)
		CreateRenderTargetView();

	if (g_TargetView)
		g_DeviceContext->OMSetRenderTargets(1, &g_TargetView, nullptr);

	RenderTarget::BeginScene();

	return m_pPresentOrig(pSwapChain, SyncInterval, Flags);
}

HRESULT __stdcall CIDXGISwapChainHook::hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
	if (g_TargetView) {
		g_TargetView->Release();
		g_TargetView = nullptr;
	}

	HRESULT result = m_pResizeBuffersOrig(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	if (SUCCEEDED(result))
	{
		CreateRenderTargetView();
		lg::Info("[CIDXGISwapChainHook]", "hkResizeBuffers called.\n");
	}

	return result;
}
