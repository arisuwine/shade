#pragma once
#include "../offsets.hpp"

#include "CHandle.hpp"
#include "CEntityInstance.hpp"

#include "../utils/hash.hpp"

class CCollisionProperty;
class CGameSceneNode;

class C_BaseEntity : public CEntityInstance {
public:
	enum TEAM : int {
		SPEC = 1,
		T = 2,
		CT = 3
	};

	SCHEMA	(int,					offsets::client::C_BaseEntity::m_iHealth,			m_iHealth		);
	SCHEMA	(TEAM,					offsets::client::C_BaseEntity::m_iTeamNum,			m_iTeamNum		);
	SCHEMA	(CCollisionProperty*,	offsets::client::C_BaseEntity::m_pCollision,		m_pCollision	);
	SCHEMA	(CGameSceneNode*,		offsets::client::C_BaseEntity::m_pGameSceneNode,	m_pGameSceneNode);
	PSCHEMA	(CHandle<C_BaseEntity>, offsets::client::C_BaseEntity::m_hOwnerEntity,		m_hOwnerEntity	);

	bool operator==(C_BaseEntity* entity) {
		return this == entity;
	}

	inline bool IsWeapon() {
		std::string name = Schema_DynamicBinding()->m_pszName ? Schema_DynamicBinding()->m_pszName : "";
		if (name.starts_with("C_Weapon"))
			return TRUE;

		hash_t hash = hash::Get(name);

		switch (hash) {
			case hash::Set("C_AK47"):
			case hash::Set("C_C4"):
			case hash::Set("C_Deagle"):
			case hash::Set("C_Knife"):
				return TRUE;
			default:
				return FALSE;
		}
	}

	inline bool IsGrenade() {
		std::string name = Schema_DynamicBinding()->m_pszName ? Schema_DynamicBinding()->m_pszName : "";
		hash_t hash = hash::Get(name);

		switch (hash) {
			case hash::Set("C_DecoyGrenade"):
			case hash::Set("C_Flashbang"):
			case hash::Set("C_HEGrenade"):
			case hash::Set("C_MolotovGrenade"):
			case hash::Set("C_SmokeGrenade"):
			case hash::Set("C_IncendiaryGrenade"):
				return TRUE;
			default:
				return FALSE;
		}
	}

	inline bool IsProjectile() {
		std::string name = Schema_DynamicBinding()->m_pszName ? Schema_DynamicBinding()->m_pszName : "";
		hash_t hash = hash::Get(name);

		switch (hash) {
			case hash::Set("C_DecoyProjectile"):
			case hash::Set("C_FlashbangProjectile"):
			case hash::Set("C_HEGrenadeProjectile"):
			case hash::Set("C_MolotovProjectile"):
			case hash::Set("C_SmokeGrenadeProjectile"):
				return TRUE;
			default:
				return FALSE;
		}
	}

	inline bool IsPawn() {
		return Schema_DynamicBinding() == g_CSchemaSystem->FindClassByScopedName("client.dll!C_CSPlayerPawn");
	}

	inline bool IsPlayerController() {
		return Schema_DynamicBinding() == g_CSchemaSystem->FindClassByScopedName("client.dll!CCSPlayerController");
	}

	inline bool IsAlive() {
		return this->m_iHealth != 0;
	}
};

class C_BaseModelEntity : public C_BaseEntity {};

class CBaseAnimGraph : public C_BaseModelEntity {};

class C_BaseFlex : public CBaseAnimGraph {};

class C_EconEntity : public C_BaseFlex {};

class C_BaseCombatCharacter : public C_BaseFlex {};