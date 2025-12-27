#pragma once
#include <vector>

#include "../sdk/modules.hpp"
#include "../sdk/signatures.hpp"

#include "../sdk/entities/CEntityHandle.hpp"

class C_BaseEntity;
class C_CSPlayerPawn;
class C_CSWeaponBase;
class CGameEntitySystem;

class EntitySystemHook {
private:
	using OnAddEntity		= void(__fastcall*)(CGameEntitySystem*, C_BaseEntity*, CEntityHandle);
	using OnRemoveEntity	= void(__fastcall*)(CGameEntitySystem*, C_BaseEntity*, CEntityHandle);

	static inline uintptr_t pOnAddEntity	= modules::client.find(ON_ADD_ENTITY);
	static inline uintptr_t pOnRemoveEntity = modules::client.find(ON_REMOVE_ENTITY);

	static void __fastcall OnAddEntityHk(CGameEntitySystem*, C_BaseEntity*, CEntityHandle);
	static void __fastcall OnRemoveEntityHk(CGameEntitySystem*, C_BaseEntity*, CEntityHandle);

	static inline OnAddEntity		oOnAddEntity;
	static inline OnRemoveEntity	oOnRemoveEntity;

	static bool is_init;

public:
	static bool initialize();
	static bool shutdown();
};

extern std::vector<C_CSWeaponBase*>	g_WeaponsCache;
extern std::vector<C_CSPlayerPawn*> g_PawnsCache;