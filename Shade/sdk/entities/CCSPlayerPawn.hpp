#pragma once
#include "../math/vector.hpp"
#include "../offsets.hpp"

#include "../interfaces/CGameEntitySystem.hpp"
#include "../entities/CCSPlayerController.hpp"
#include "../interfaces/CHandle.hpp"

class CCollisionProperty;
class CPlayer_MovementServices;
class CGameSceneNode;
class CPlayer_WeaponServices;

class CCSPlayerPawn {
public:
	CCSPlayerPawn() = delete;

	enum TEAM : int {
		SPEC = 1,
		T = 2,
		CT = 3
	};

	SCHEMA	(int,							offsets::CCSPlayerPawn::m_iHealth,				m_iHealth			);
	SCHEMA	(int,							offsets::CCSPlayerPawn::m_ArmorValue,			m_ArmorValue		);
	SCHEMA	(TEAM,							offsets::CCSPlayerPawn::m_iTeamNum,				m_iTeamNum			);
	SCHEMA	(vector_3d,						offsets::CCSPlayerPawn::m_vOldOrigin,			m_vOldOrigin		);
	SCHEMA	(bool,							offsets::CCSPlayerPawn::m_bIsScoped,			m_bIsScoped			);
	SCHEMA	(bool,							offsets::CCSPlayerPawn::m_bIsDefusing,			m_bIsDefusing		);
	SCHEMA	(CCollisionProperty*,			offsets::CCSPlayerPawn::m_pCollision,			m_pCollision		);
	SCHEMA  (CPlayer_MovementServices*,		offsets::CCSPlayerPawn::m_pMovementServices,	m_pMovementServices	);
	SCHEMA  (CGameSceneNode*,				offsets::CCSPlayerPawn::m_pGameSceneNode,		m_pGameSceneNode	);
	SCHEMA  (CPlayer_WeaponServices*,		offsets::CCSPlayerPawn::m_pWeaponServices,		m_pWeaponServices	);
	SCHEMA_R(CHandle<CCSPlayerController>,	offsets::CCSPlayerPawn::m_hController,			m_hController		);
};

class LocalPlayer {
private:
	uintptr_t handle;
	CCSPlayerController* controller;

	CCSPlayerPawn* pawn;

	LocalPlayer() : pawn(nullptr) {}

public:
	static LocalPlayer& get() {
		static LocalPlayer instance;
		return instance;
	}

	inline void initialize() {
		if (!handle)
			handle = modules::client.find(LOCAL_PLAYER_CONTROLLER);

			controller = *reinterpret_cast<CCSPlayerController**>(handle + *((int32_t*)(handle + 3)) + 7);
	}

	void update() {
		initialize();

		pawn = controller->m_hPawn.GetEntityFromHandle();
	}

	CCSPlayerPawn* get_pawn() const {
		return pawn ? pawn : nullptr;
	}
};