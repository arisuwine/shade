#pragma once
#include "../offsets.hpp"

#include "C_BaseEntity.hpp"
#include "CCSPlayerController.hpp"

class CPlayer_MovementServices;
class CPlayer_WeaponServices;

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

class C_BaseCombatCharacter : public C_BaseFlex {
public:
	C_BaseCombatCharacter() = delete;
};

class C_BasePlayerPawn : public C_BaseCombatCharacter {
public:
	C_BasePlayerPawn() = delete;

	SCHEMA	(vector_3d,						offsets::C_BasePlayerPawn::m_vOldOrigin,		m_vOldOrigin		);
	SCHEMA	(CPlayer_MovementServices*,		offsets::C_BasePlayerPawn::m_pMovementServices, m_pMovementServices	);
	SCHEMA	(CPlayer_WeaponServices*,		offsets::C_BasePlayerPawn::m_pWeaponServices,	m_pWeaponServices	);
	SCHEMA_R(CHandle<CCSPlayerController>,	offsets::C_BasePlayerPawn::m_hController,		m_hController		);
};