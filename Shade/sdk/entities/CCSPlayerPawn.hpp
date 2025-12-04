#pragma once
#include "../offsets.hpp"
#include "../modules.hpp"
#include "../signatures.hpp"

#include "../interfaces/CHandle.hpp"

#include "C_BasePlayerPawn.hpp"

#include "../math/vector.hpp"

class CPlayer_MovementServices;
class CPlayer_WeaponServices;
class CCSWeaponBase;

class C_CSPlayerPawnBase : public C_BasePlayerPawn {
public:
	C_CSPlayerPawnBase() = delete;
};

class CCSPlayerPawn : public C_CSPlayerPawnBase {
public:
	CCSPlayerPawn() = delete;

	SCHEMA	(int,							offsets::CCSPlayerPawn::m_ArmorValue,			m_ArmorValue		);
	SCHEMA	(bool,							offsets::CCSPlayerPawn::m_bIsScoped,			m_bIsScoped			);
	SCHEMA	(bool,							offsets::CCSPlayerPawn::m_bIsDefusing,			m_bIsDefusing		);
	SCHEMA  (CCSWeaponBase*,				offsets::CCSPlayerPawn::m_pClippingWeapon,		m_pClippingWeapon	);

	inline bool IsAlive();
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

bool CCSPlayerPawn::IsAlive() {
	return this->m_iHealth != 0;
}