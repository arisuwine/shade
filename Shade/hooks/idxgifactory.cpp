#include "idxgifactory.hpp"

#include "hooks.hpp"

#include "../sdk/sdk.hpp"

void CIDXGIFactoryHook::Register() {
	IDXGIDevice* pDXGIDevice = nullptr;
	IDXGIAdapter* pAdapter = nullptr;
	IDXGIFactory* pFactory = nullptr;

	if (FAILED(g_Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pDXGIDevice))))
		throw std::runtime_error("failed to get IDXGIDevice");

	if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&pAdapter))))
		throw std::runtime_error("failed to get IDXGIAdapter");

	if (FAILED(pAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFactory))))
		throw std::runtime_error("failed to get IDXGIFactory");

	std::unique_ptr<CVMTHook> hook = std::make_unique<CVMTHook>("CIDXGIFactoryHook", pFactory);
	
	hooks::AddVMTHook<CreateSwapChainFunc>(hook.get(), 10, hkCreateSwapChain, &m_pCreateSwapChainOrig);

	lg::Success("[+]", "Hook %s initialized successfully.\n", hook->GetName().data());

	pDXGIDevice->Release();
	pAdapter->Release();

	hooks::g_pHooks.push_back(std::move(hook));
}

HRESULT __stdcall CIDXGIFactoryHook::hkCreateSwapChain(IDXGIFactory* pFactory, IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain) {
	HRESULT result = m_pCreateSwapChainOrig(pFactory, pDevice, pDesc, ppSwapChain);
	if (SUCCEEDED(result) && ppSwapChain && *ppSwapChain) {
		if (g_TargetView) {
			g_TargetView->Release();
			g_TargetView = nullptr;
		}

		if (g_SwapChain != *ppSwapChain) {
			g_SwapChain = *ppSwapChain;

			if (!m_pSwapChainHook)
				for (const auto& hook : hooks::g_pHooks)
					if (hook->GetName() == "CIDXGISwapChainHook") {
						m_pSwapChainHook = static_cast<CVMTHook*>(hook.get());
						break;
					}

			m_pSwapChainHook->Rebase(g_SwapChain, true);
		}
	}
	
	return result;
}
