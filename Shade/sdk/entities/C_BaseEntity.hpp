#pragma once
#include "../offsets.hpp"

#include "CHandle.hpp"
#include "CEntityInstance.hpp"

class CCollisionProperty;
class CGameSceneNode;

constexpr uint32_t hash_str(const char* str) {
	uint32_t hash = 0x811c9dc5;
	uint32_t prime = 0x1000193;

	while (*str) {
		hash ^= static_cast<uint32_t>(*str++);
		hash *= prime;
	}
	return hash;
}

class C_BaseEntity : public CEntityInstance {
public:
	C_BaseEntity() = delete;

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
		const char* binding_name = Schema_DynamicBinding()->m_pszName;
		if (std::strncmp(binding_name, "C_Weapon", 8) == 0) {
			return TRUE;
		}

		switch (hash_str(binding_name)) {
			case hash_str("C_AK47"):
			case hash_str("C_C4"):
			case hash_str("C_Deagle"):
			case hash_str("C_Knife"):
				return TRUE;
			default:
				return FALSE;
		}
	}

	inline bool IsGrenade() {
		const char* binding_name = Schema_DynamicBinding()->m_pszName;

		switch (hash_str(binding_name)) {
			case hash_str("C_DecoyGrenade"):
			case hash_str("C_Flashbang"):
			case hash_str("C_HEGrenade"):
			case hash_str("C_MolotovGrenade"):
			case hash_str("C_SmokeGrenade"):
			case hash_str("C_IncendiaryGrenade"):
				return TRUE;
			default:
				return FALSE;
		}
	}

	inline bool IsProjectile() {
		const char* binding_name = Schema_DynamicBinding()->m_pszName;

		switch (hash_str(binding_name)) {
			case hash_str("C_DecoyProjectile"):
			case hash_str("C_FlashbangProjectile"):
			case hash_str("C_HEGrenadeProjectile"):
			case hash_str("C_MolotovProjectile"):
			case hash_str("C_SmokeGrenadeProjectile"):
				return TRUE;
			default:
				return FALSE;
		}
	}

	inline bool IsPawn() {
		return Schema_DynamicBinding() == g_CSchemaSystem->FindClassByScopedName("client.dll!C_CSPlayerPawn");
	}

	inline bool IsAlive() {
		return this->m_iHealth != 0;
	}
};

class C_BaseModelEntity : public C_BaseEntity {
public:
	C_BaseModelEntity() = delete;
};

class CBaseAnimGraph : public C_BaseModelEntity {
public:
	CBaseAnimGraph() = delete;
};

class C_BaseFlex : public CBaseAnimGraph {
public:
	C_BaseFlex() = delete;
};

class C_EconEntity : public C_BaseFlex {
public:
	C_EconEntity() = delete;
};

class C_BaseCombatCharacter : public C_BaseFlex {
public:
	C_BaseCombatCharacter() = delete;
};