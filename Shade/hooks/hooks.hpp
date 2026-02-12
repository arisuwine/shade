#pragma once
#include <vector>

#include "ihook.hpp"

namespace hooks {
	inline std::vector<std::unique_ptr<IHookBase>> g_pHooks;

	void Initialize();
	void Shutdown();

	template <typename Func>
	void AddDetour(std::string_view szName, void* pTarget, void* pDetour, Func* ppOriginal, std::function<void()> onCreate, std::function<void()> onDestroy) {
		std::unique_ptr<CDetourHook> hook = std::make_unique<CDetourHook>(szName, pTarget, pDetour, onCreate, onDestroy);

		*ppOriginal = hook->GetOriginal<Func>();

		if (!hook->Enable()) {
			MH_RemoveHook(hook->m_pTarget);
			throw std::runtime_error(std::format("failed to enable hook {}", szName));
		}

		hook->m_bIsEnabled = true;

		lg::Success("[+]", "Hook %s initialized successfully.\n", hook->m_szName.data());

		g_pHooks.push_back(std::move(hook));
	}

	template <typename Func>
	void AddVMTHook(CVMTHook* hook, size_t iFuncIndex, Func pDetour, Func* ppOriginal) {
		*ppOriginal = hook->Enable<Func>(iFuncIndex, pDetour);
		if (!(*ppOriginal))
			throw std::runtime_error(std::format("failed to enable hook in {}", hook->m_szName.data()));
	}
}