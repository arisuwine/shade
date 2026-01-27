#pragma once
#include "../offsets.hpp"

#include "../entities/CHandle.hpp"

class C_CSWeaponBase;

class CPlayer_WeaponServices {
public:
	PSCHEMA	(CHandle<C_CSWeaponBase>,	offsets::client::CPlayer_WeaponServices::m_hMyWeapons,		m_hMyWeapons	);
	PSCHEMA	(CHandle<C_CSWeaponBase>,	offsets::client::CPlayer_WeaponServices::m_hActiveWeapon,	m_hActiveWeapon	);
	SCHEMA	(uint16_t,					offsets::client::CPlayer_WeaponServices::m_iAmmo,			m_iAmmo);
};