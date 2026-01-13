#pragma once
#include "../offsets.hpp"

#include "C_BaseEntity.hpp"

class CEntityIdentity;
class CCSWeaponBaseVData;

class C_BasePlayerWeapon : public C_EconEntity {
public:
	C_BasePlayerWeapon() = delete;

	SCHEMA(int,					offsets::client::C_BasePlayerWeapon::m_iClip1,		m_iClip1		);
};

class C_CSWeaponBase : public C_BasePlayerWeapon {
public:
	C_CSWeaponBase() = delete;

	SCHEMA(CCSWeaponBaseVData*, offsets::client::C_CSWeaponBase::m_pWeaponVData,	m_pWeaponVData	);
};