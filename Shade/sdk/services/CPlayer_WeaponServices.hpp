#pragma once
#include "../offsets.hpp"

#include "CHandle.hpp"

class C_CSWeaponBase;

class CPlayer_WeaponServices {
public:
	CPlayer_WeaponServices() = delete;

	PSCHEMA	(CHandle<C_CSWeaponBase>,	offsets::CPlayer_WeaponServices::m_hMyWeapons,		m_hMyWeapons	);
	PSCHEMA	(CHandle<C_CSWeaponBase>,	offsets::CPlayer_WeaponServices::m_hActiveWeapon,	m_hActiveWeapon	);
	SCHEMA	(uint16_t,					offsets::CPlayer_WeaponServices::m_iAmmo,			m_iAmmo);
};