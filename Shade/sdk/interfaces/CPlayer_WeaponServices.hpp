#pragma once
#include "../offsets.hpp"

#include "CHandle.hpp"
#include "../entities/C_BasePlayerWeapon.hpp"

class CPlayer_WeaponServices {
public:
	CPlayer_WeaponServices() = delete;

	SCHEMA_R(CHandle<C_BasePlayerWeapon>,	offsets::CPlayer_WeaponServices::m_hMyWeapons,		m_hMyWeapons	);
	SCHEMA_R(CHandle<C_BasePlayerWeapon>,	offsets::CPlayer_WeaponServices::m_hActiveWeapon,	m_hActiveWeapon	);
};