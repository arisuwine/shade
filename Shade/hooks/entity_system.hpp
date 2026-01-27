#pragma once
#include <vector>

#include "../sdk/modules.hpp"
#include "../sdk/signatures.hpp"

#include "../sdk/entities/CEntityHandle.hpp"

#include "../utils/vmt/vmt.hpp"

class C_BaseEntity;
class C_CSPlayerPawn;
class C_CSWeaponBase;
class CGameEntitySystem;

class EntitySystemHook {
private:
	using OnAddEntityFunc		= void(__fastcall*)(CGameEntitySystem*, C_BaseEntity*, CEntityHandle);
	using OnRemoveEntityFunc	= void(__fastcall*)(CGameEntitySystem*, C_BaseEntity*, CEntityHandle);

	static vmt::Shadowing* m_Shadowing;

	//static inline uintptr_t pOnAddEntity	= modules::client.find(ON_ADD_ENTITY); // 15
	//static inline uintptr_t pOnRemoveEntity = modules::client.find(ON_REMOVE_ENTITY); // 16

	static inline OnAddEntityFunc		OnAddEntityOrig;
	static inline OnRemoveEntityFunc	OnRemoveEntityOrig;

	static void __fastcall hkOnAddEntity(CGameEntitySystem*, C_BaseEntity*, CEntityHandle);
	static void __fastcall hkOnRemoveEntity(CGameEntitySystem*, C_BaseEntity*, CEntityHandle);


	static bool m_bIsInit;

public:
	static bool Initialize();
	static bool Shutdown();

	inline bool IsInitialized() { return m_bIsInit; }
};

extern std::vector<C_CSWeaponBase*>	g_WeaponsCache;
extern std::vector<C_CSPlayerPawn*> g_PawnsCache;