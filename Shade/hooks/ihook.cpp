#include "ihook.hpp"

#include "../utils/debug.hpp"

// CDetourHook
bool CDetourHook::Initialize() {
	if (auto status = MH_Initialize(); status != MH_OK)
		throw std::runtime_error(std::format("failed to initialize MinHook {}", (int)status));

	return true;
}

bool CDetourHook::Uninitialize() {
	if (auto status = MH_Uninitialize(); status != MH_OK)
		throw std::runtime_error(std::format("failed to uninitialize MinHook {}", (int)status));

	return true;
}

CDetourHook::CDetourHook(std::string_view szName, void* pTarget, void* pDetour, std::function<void()> onCreate, std::function<void()> onDestroy) : m_pDetour(nullptr), m_pOriginal(nullptr), m_pTarget(nullptr) {
	if (MH_CreateHook(pTarget, pDetour, &m_pOriginal) != MH_OK)
		throw std::runtime_error(std::format("failed to create hook {}", szName));

	m_pDetour = pDetour;
	m_pTarget = pTarget;
	m_szName = std::string(szName);
	m_onCreate = onCreate;
	m_onDestroy = onDestroy;

	if (m_onCreate)
		m_onCreate();
}

bool CDetourHook::Enable() {
	if (!IsEnabled() && MH_EnableHook(m_pTarget) == MH_OK) {
		m_bIsEnabled = true;
		return true;
	}

	return false;
}

bool CDetourHook::Disable() {
	if (IsEnabled() && MH_DisableHook(m_pTarget) == MH_OK) {
		m_bIsEnabled = false;
		return true;
	}

	return false;
}

CDetourHook::~CDetourHook() {
	if (Disable() && m_onDestroy)
		m_onDestroy();

	MH_RemoveHook(m_pTarget);

	lg::Success("[-]", "Hook %s removed successfully.\n", m_szName.data());
}

// CVMTHook
CVMTHook::CVMTHook(std::string_view szName, void* pObject, std::function<void()> onCreate, std::function<void()> onDestroy) : m_Shadowing(pObject) {
	if (!m_Shadowing.IsInitialized())
		throw std::runtime_error(std::format("failed to initialize VMT {} at 0x{}", szName, pObject));

	m_bIsEnabled = true;
	m_szName = szName;
	m_onCreate = onCreate;
	m_onDestroy = onDestroy;

	if (m_onCreate)
		m_onCreate();
}

bool CVMTHook::Rebase(void* pObject, bool RestoreOld) {
	if (!m_Shadowing.Rebase(pObject, RestoreOld))
		return false;

	return true;
}

bool CVMTHook::Disable(size_t iFuncIndex) {
	if (!IsEnabled())
		return false;

	if (!m_Shadowing.UnHook(iFuncIndex))
		return false;

	return true;
}