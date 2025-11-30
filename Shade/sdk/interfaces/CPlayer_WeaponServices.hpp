#pragma once
#include "../offsets.hpp"

#include "CHandle.hpp"

#include "../entities/CCSWeaponBase.hpp"

class CPlayer_WeaponServices {
public:
	CPlayer_WeaponServices() = delete;

	SCHEMA_R(CHandle<CCSWeaponBase>,	offsets::CPlayer_WeaponServices::m_hMyWeapons,		m_hMyWeapons	);
	SCHEMA_R(CHandle<CCSWeaponBase>,	offsets::CPlayer_WeaponServices::m_hActiveWeapon,	m_hActiveWeapon	);
	SCHEMA	(uint16_t,					offsets::CPlayer_WeaponServices::m_iAmmo,			m_iAmmo);
};