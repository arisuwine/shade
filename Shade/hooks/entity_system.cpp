#include "entity_system.hpp"

#include <cstring>
#include <stdexcept>

#include "hooks.hpp"

#include "../sdk/entities/CGameEntitySystem.hpp"
#include "../sdk/entities/C_BaseEntity.hpp"
#include "../sdk/entities/C_CSPlayerPawn.hpp"
#include "../sdk/entities/C_CSWeaponBase.hpp"

#include "../utils/debug.hpp"

std::vector<C_CSWeaponBase*> g_WeaponsCache;
std::vector<C_CSPlayerPawn*> g_PawnsCache;

void CEntitySystemHook::Register() {
	std::unique_ptr<CVMTHook> hook = std::make_unique<CVMTHook>("CEntitySystemHook", g_CGameEntitySystem);

	m_pOnAddEntityOrig = hook->Enable<OnAddEntityFunc>(15, hkOnAddEntity);
	if (!m_pOnAddEntityOrig)
		throw std::runtime_error("failed to enable OnAddEntity hook");

	m_pOnRemoveEntityOrig = hook->Enable<OnRemoveEntityFunc>(16, hkOnRemoveEntity);
	if (!m_pOnRemoveEntityOrig)
		throw std::runtime_error("failed to enable OnRemoveEntit hook");

	lg::Success("[+]", "Hook %s initialized successfully.\n", hook->GetName().data());

	hooks::g_pHooks.push_back(std::move(hook));
}

void __fastcall CEntitySystemHook::hkOnAddEntity(CGameEntitySystem* pCGameEntitySystem, C_BaseEntity* pEnt, CEntityHandle handle) {
	m_pOnAddEntityOrig(pCGameEntitySystem, pEnt, handle);

	if (!pEnt)
		return;

	if (pEnt->IsPawn())
		g_PawnsCache.push_back(reinterpret_cast<C_CSPlayerPawn*>(pEnt));

	if (pEnt->IsWeapon() || pEnt->IsGrenade())
		g_WeaponsCache.push_back(reinterpret_cast<C_CSWeaponBase*>(pEnt));
}

void __fastcall CEntitySystemHook::hkOnRemoveEntity(CGameEntitySystem* pCGameEntitySystem, C_BaseEntity* pEnt, CEntityHandle handle) {
	m_pOnRemoveEntityOrig(pCGameEntitySystem, pEnt, handle);

	if (!pEnt)
		return;

	auto find_and_pop = [pEnt]<typename T>(std::vector<T*>&v) {
		auto it = std::find(v.begin(), v.end(), pEnt);
		if (it != v.end()) {
			*it = v.back();
			v.pop_back();
		}
	};

	find_and_pop(g_WeaponsCache);
	find_and_pop(g_PawnsCache);
}