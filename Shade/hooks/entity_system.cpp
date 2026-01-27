#include "entity_system.hpp"

#include <cstring>
#include "minhook.h"

#include "../sdk/entities/CGameEntitySystem.hpp"
#include "../sdk/entities/C_BaseEntity.hpp"
#include "../sdk/entities/C_CSPlayerPawn.hpp"
#include "../sdk/entities/C_CSWeaponBase.hpp"

#include "../sdk/services/CGlowProperty.hpp"

#include "../sdk/utils/color.hpp"

#include "../menu/options.hpp"

#include "../utils/debug.hpp"

std::vector<C_CSWeaponBase*> g_WeaponsCache;
std::vector<C_CSPlayerPawn*> g_PawnsCache;

vmt::Shadowing* EntitySystemHook::m_Shadowing	= nullptr;
bool			EntitySystemHook::m_bIsInit		= FALSE;

bool EntitySystemHook::Initialize() {
	if (m_bIsInit)
		return TRUE;

	m_Shadowing = new vmt::Shadowing(g_CGameEntitySystem);
	if (!m_Shadowing->IsInitialized()) {
		LOG_AND_RETURN("[-] vmt Shadowing has failed at EntitySystemHook.\n");
		return FALSE;
	}

	OnAddEntityOrig = m_Shadowing->Hook<OnAddEntityFunc>(15, hkOnAddEntity);
	if (!OnAddEntityOrig) {
		LOG_AND_RETURN("[-] vmt Hooking has failed at EntitySystemHook.\n");
		return FALSE;
	}

	OnRemoveEntityOrig = m_Shadowing->Hook<OnRemoveEntityFunc>(16, hkOnRemoveEntity);
	if (!OnRemoveEntityOrig) {
		LOG_AND_RETURN("[-] vmt Hooking has failed at EntitySystemHook.\n");
		return FALSE;
	}

	m_bIsInit = TRUE;
	return TRUE;
}

bool EntitySystemHook::Shutdown() {
	if (!m_bIsInit)
		return TRUE;

	m_Shadowing->Shutdown();

	m_bIsInit = FALSE;
	return TRUE;
}

static long long ent_num = 0;
void __fastcall EntitySystemHook::hkOnAddEntity(CGameEntitySystem* pCGameEntitySystem, C_BaseEntity* pEnt, CEntityHandle handle) {
	OnAddEntityOrig(pCGameEntitySystem, pEnt, handle);

	if (!pEnt)
		return;

	if (pEnt->IsPawn())
		g_PawnsCache.push_back(reinterpret_cast<C_CSPlayerPawn*>(pEnt));

	if (pEnt->IsWeapon() || pEnt->IsGrenade())
		g_WeaponsCache.push_back(reinterpret_cast<C_CSWeaponBase*>(pEnt));
}

void __fastcall EntitySystemHook::hkOnRemoveEntity(CGameEntitySystem* pCGameEntitySystem, C_BaseEntity* pEnt, CEntityHandle handle) {
	OnRemoveEntityOrig(pCGameEntitySystem, pEnt, handle);

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