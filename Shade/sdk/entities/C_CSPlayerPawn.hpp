#pragma once
#include "../offsets.hpp"
#include "../modules.hpp"
#include "../signatures.hpp"

#include "CHandle.hpp"
#include "C_BaseEntity.hpp"
#include "C_CSPlayerController.hpp"

#include "../math/vector.hpp"

class CPlayer_MovementServices;
class CPlayer_WeaponServices;
class C_CSWeaponBase;

class C_BasePlayerPawn : public C_BaseCombatCharacter {
public:
	C_BasePlayerPawn() = delete;

	SCHEMA	(vector_3d,							offsets::client::C_BasePlayerPawn::m_vOldOrigin,		m_vOldOrigin		);
	SCHEMA	(CPlayer_MovementServices*,			offsets::client::C_BasePlayerPawn::m_pMovementServices, m_pMovementServices	);
	SCHEMA	(CPlayer_WeaponServices*,			offsets::client::C_BasePlayerPawn::m_pWeaponServices,	m_pWeaponServices	);
	PSCHEMA	(CHandle<C_CSPlayerController>,		offsets::client::C_BasePlayerPawn::m_hController,		m_hController		);
};

class C_CSPlayerPawnBase : public C_BasePlayerPawn {
public:
	C_CSPlayerPawnBase() = delete;
};

class C_CSPlayerPawn : public C_CSPlayerPawnBase {
public:
	C_CSPlayerPawn() = delete;

	SCHEMA(int,					offsets::client::C_CSPlayerPawn::m_ArmorValue,			m_ArmorValue		);
	SCHEMA(bool,				offsets::client::C_CSPlayerPawn::m_bIsScoped,			m_bIsScoped			);
	SCHEMA(bool,				offsets::client::C_CSPlayerPawn::m_bIsDefusing,			m_bIsDefusing		);
	SCHEMA(C_CSWeaponBase*,		offsets::client::C_CSPlayerPawn::m_pClippingWeapon,		m_pClippingWeapon	);

	
};

class LocalPlayer {
private:
	uintptr_t handle;
	C_CSPlayerController* controller;

	C_CSPlayerPawn* pawn;

	LocalPlayer() : pawn(nullptr) {}

public:
	static LocalPlayer& Get() {
		static LocalPlayer instance;
		return instance;
	}

	inline void Initialize() {
		if (!handle)
			handle = modules::client.find(LOCAL_PLAYER_CONTROLLER);

			controller = *reinterpret_cast<C_CSPlayerController**>(handle + *((int32_t*)(handle + 3)) + 7);
	}

	void Update() {
		Initialize();

		pawn = controller->m_hPawn.GetEntityFromHandle();
	}

	C_CSPlayerPawn* GetPawn() const {
		return pawn ? pawn : nullptr;
	}
};