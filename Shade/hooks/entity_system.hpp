#pragma once
#include <vector>

#include "../sdk/entities/CEntityHandle.hpp"

class C_BaseEntity;
class C_CSPlayerPawn;
class C_CSWeaponBase;
class CGameEntitySystem;

class CEntitySystemHook {
private:
	using OnAddEntityFunc		= void(__fastcall*)(CGameEntitySystem*, C_BaseEntity*, CEntityHandle);
	using OnRemoveEntityFunc	= void(__fastcall*)(CGameEntitySystem*, C_BaseEntity*, CEntityHandle);

	static inline OnAddEntityFunc		m_pOnAddEntityOrig;
	static inline OnRemoveEntityFunc	m_pOnRemoveEntityOrig;

	static void __fastcall hkOnAddEntity(CGameEntitySystem*, C_BaseEntity*, CEntityHandle);
	static void __fastcall hkOnRemoveEntity(CGameEntitySystem*, C_BaseEntity*, CEntityHandle);

public:
	static void Register();
};

extern std::vector<C_CSWeaponBase*>	g_WeaponsCache;
extern std::vector<C_CSPlayerPawn*> g_PawnsCache;