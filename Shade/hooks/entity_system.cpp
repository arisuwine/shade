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

bool EntitySystemHook::is_init = false;
bool EntitySystemHook::Initialize() {
	if (is_init)
		return TRUE;

	if (MH_CreateHook((LPVOID)pOnAddEntity, &OnAddEntityHk, reinterpret_cast<void**>(&oOnAddEntity)) != MH_OK)
		LOG_AND_RETURN("[-] OnAddEntityHk hook creation has failed.\n");

	if (MH_CreateHook((LPVOID)pOnRemoveEntity, &OnRemoveEntityHk, reinterpret_cast<void**>(&oOnRemoveEntity)) != MH_OK)
		LOG_AND_RETURN("[-] OnRemoveEntityHk hook creation has failed.\n");

	if (MH_EnableHook((LPVOID)pOnAddEntity) != MH_OK)
		LOG_AND_RETURN("[-] pOnAddEntity hook enabling has failed.\n");

	if (MH_EnableHook((LPVOID)pOnRemoveEntity) != MH_OK)
		LOG_AND_RETURN("[-] pOnRemoveEntity hook enabling has failed.\n");

	is_init = TRUE;
	return TRUE;
}

bool EntitySystemHook::Shutdown() {
	if (!is_init)
		return TRUE;

	if (MH_DisableHook((LPVOID)pOnAddEntity) != MH_OK)
		LOG_AND_RETURN("[-] pOnAddEntity hook disabling has failed.\n");

	if (MH_DisableHook((LPVOID)pOnRemoveEntity) != MH_OK)
		LOG_AND_RETURN("[-] pOnRemoveEntity hook disabling has failed.\n");

	is_init = FALSE;
	return TRUE;
}

std::vector<C_CSWeaponBase*> g_WeaponsCache;
std::vector<C_CSPlayerPawn*> g_PawnsCache;

static long long ent_num = 0;
void __fastcall EntitySystemHook::OnAddEntityHk(CGameEntitySystem* pCGameEntitySystem, C_BaseEntity* pEnt, CEntityHandle handle) {
	oOnAddEntity(pCGameEntitySystem, pEnt, handle);

	if (!pEnt)
		return;

	if (pEnt->IsPawn())
		g_PawnsCache.push_back(reinterpret_cast<C_CSPlayerPawn*>(pEnt));

	if (pEnt->IsWeapon() || pEnt->IsGrenade())
		g_WeaponsCache.push_back(reinterpret_cast<C_CSWeaponBase*>(pEnt));
}

void __fastcall EntitySystemHook::OnRemoveEntityHk(CGameEntitySystem* pCGameEntitySystem, C_BaseEntity* pEnt, CEntityHandle handle) {
	oOnRemoveEntity(pCGameEntitySystem, pEnt, handle);

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