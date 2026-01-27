#pragma once
#include "../offsets.hpp"
#include "../modules.hpp"
#include "../signatures.hpp"

#include "CHandle.hpp"
#include "C_BaseEntity.hpp"
#include "CCSPlayerController.hpp"

#include "../math/vector_3d.hpp"
#include "../math/vector_2d.hpp"

#include "../utils/singleton.hpp"

class CPlayer_MovementServices;
class CPlayer_WeaponServices;
class C_CSWeaponBase;

class C_BasePlayerPawn : public C_BaseCombatCharacter {
public:
	SCHEMA	(Vector3D,							offsets::client::C_BasePlayerPawn::m_vOldOrigin,		m_vOldOrigin		);
	SCHEMA	(CPlayer_MovementServices*,			offsets::client::C_BasePlayerPawn::m_pMovementServices, m_pMovementServices	);
	SCHEMA	(CPlayer_WeaponServices*,			offsets::client::C_BasePlayerPawn::m_pWeaponServices,	m_pWeaponServices	);
	PSCHEMA	(CHandle<CCSPlayerController>,		offsets::client::C_BasePlayerPawn::m_hController,		m_hController		);
};

class C_CSPlayerPawnBase : public C_BasePlayerPawn {};

class C_CSPlayerPawn : public C_CSPlayerPawnBase {
public:
	SCHEMA	(int,					offsets::client::C_CSPlayerPawn::m_ArmorValue,			m_ArmorValue		);
	SCHEMA	(bool,					offsets::client::C_CSPlayerPawn::m_bIsScoped,			m_bIsScoped			);
	SCHEMA	(bool,					offsets::client::C_CSPlayerPawn::m_bIsDefusing,			m_bIsDefusing		);
	SCHEMA	(C_CSWeaponBase*,		offsets::client::C_CSPlayerPawn::m_pClippingWeapon,		m_pClippingWeapon	);
};

class LocalPlayer : public Singleton<LocalPlayer> {
	friend class Singleton<LocalPlayer>;

private:
	uintptr_t handle;

	CCSPlayerController* controller;
	C_CSPlayerPawn* pawn;

	LocalPlayer() = default;

public:
	inline void Initialize() {
		if (!handle)
			handle = modules::client.Find(LOCAL_PLAYER_CONTROLLER);

		controller = RESOLVE_RELATIVE(CCSPlayerController, handle);
	}

	void Update() {
		Initialize();

		pawn = controller->m_hPawn.GetEntityFromHandle();
	}

	inline bool IsValid() const {
		return (controller && controller->m_hPawn.IsValid() && pawn);
	}

	C_CSPlayerPawn* GetPawn() const {
		return IsValid() ? pawn : nullptr;
	}
};