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

	SCHEMA	(vector_3d,							offsets::C_BasePlayerPawn::m_vOldOrigin,		m_vOldOrigin		);
	SCHEMA	(CPlayer_MovementServices*,			offsets::C_BasePlayerPawn::m_pMovementServices, m_pMovementServices	);
	SCHEMA	(CPlayer_WeaponServices*,			offsets::C_BasePlayerPawn::m_pWeaponServices,	m_pWeaponServices	);
	PSCHEMA	(CHandle<C_CSPlayerController>,		offsets::C_BasePlayerPawn::m_hController,		m_hController		);
};

class C_CSPlayerPawnBase : public C_BasePlayerPawn {
public:
	C_CSPlayerPawnBase() = delete;
};

class C_CSPlayerPawn : public C_CSPlayerPawnBase {
public:
	C_CSPlayerPawn() = delete;

	SCHEMA(int,					offsets::C_CSPlayerPawn::m_ArmorValue,			m_ArmorValue		);
	SCHEMA(bool,				offsets::C_CSPlayerPawn::m_bIsScoped,			m_bIsScoped			);
	SCHEMA(bool,				offsets::C_CSPlayerPawn::m_bIsDefusing,			m_bIsDefusing		);
	SCHEMA(C_CSWeaponBase*,		offsets::C_CSPlayerPawn::m_pClippingWeapon,		m_pClippingWeapon	);

	inline bool IsAlive();
};

class LocalPlayer {
private:
	uintptr_t handle;
	C_CSPlayerController* controller;

	C_CSPlayerPawn* pawn;

	LocalPlayer() : pawn(nullptr) {}

public:
	static LocalPlayer& get() {
		static LocalPlayer instance;
		return instance;
	}

	inline void initialize() {
		if (!handle)
			handle = modules::client.find(LOCAL_PLAYER_CONTROLLER);

			controller = *reinterpret_cast<C_CSPlayerController**>(handle + *((int32_t*)(handle + 3)) + 7);
	}

	void update() {
		initialize();

		pawn = controller->m_hPawn.GetEntityFromHandle();
	}

	C_CSPlayerPawn* get_pawn() const {
		return pawn ? pawn : nullptr;
	}
};

bool C_CSPlayerPawn::IsAlive() {
	return this->m_iHealth != 0;
}