#pragma once
#include "../offsets.hpp"

#include "CHandle.hpp"
#include "CEntityInstance.hpp"

#include "../utils/hash.hpp"

class CCollisionProperty;
class CGameSceneNode;

enum Flags_t : uint32_t
{
	// PLAYER SPECIFIC FLAGS
	FL_ONGROUND = (1u << 0), // At rest / on the ground
	FL_DUCKING = (1u << 1), // Player flag -- Player is fully crouched
	FL_WATERJUMP = (1u << 2), // player jumping out of water
	// FL_EMPTY					= (1u << 3),
	FL_BOT = (1u << 4), // Fake client controlled pawn entity, mostly referenced in movement related code
	FL_FROZEN = (1u << 5), // Player is frozen for 3rd person camera
	FL_ATCONTROLS = (1u << 6), // Player can't move, but keeps key inputs for controlling another entity
	FL_CLIENT = (1u << 7), // Is a player
	FL_FAKECLIENT = (1u << 8), // Fake client, simulated server side. Mainly set on controllers
	// FL_EMPTY 				= (1u << 9),

	// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
	FL_FLY = (1u << 10), // Changes the SV_Movestep() behavior to not need to be on ground
	FL_SUPPRESS_SAVE = (1u << 11),
	FL_IN_VEHICLE = (1u << 12),
	FL_IN_VEHICLE_TRANSPORT = (1u << 13),
	FL_GODMODE = (1u << 14),
	FL_NOTARGET = (1u << 15),
	FL_AIMTARGET = (1u << 16), // set if the crosshair needs to aim onto the entity
	// FL_EMPTY 				= (1u << 17),
	FL_STATICPROP = (1u << 18), // Eetsa static prop!
	// FL_EMPTY 				= (1u << 19),
	FL_GRENADE = (1u << 20),
	// FL_EMPTY					= (1u << 21),
	FL_DONTTOUCH = (1u << 22), // Doesn't generate touch functions, generates Untouch() for anything it was touching when this flag was set
	FL_BASEVELOCITY = (1u << 23),
	FL_CONVEYOR = (1u << 24),
	FL_OBJECT = (1u << 25), // Terrible name. This is an object that NPCs should see. Missiles, for example.
	// FL_EMPTY 				= (1u << 26),
	FL_ONFIRE = (1u << 27), // You know...
	FL_DISSOLVING = (1u << 28), // We're dissolving!
	FL_TRANSRAGDOLL = (1u << 29), // In the process of turning into a client side ragdoll.
	FL_UNBLOCKABLE_BY_PLAYER = (1u << 30)  // pusher that can't be blocked by the player
	// FL_EMPTY 				= (1u << 31),
};

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
	SCHEMA	(Flags_t,				offsets::client::C_BaseEntity::m_fFlags,			m_fFlags		);
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