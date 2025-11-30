#pragma once
#include "../offsets.hpp"

class CEntityIdentity;
class CCSWeaponBaseVData;

class CCSWeaponBase {
public:
	CCSWeaponBase() = delete;

	SCHEMA(CEntityIdentity*,	offsets::CCSWeaponBase::m_pEntity,		m_pEntity		);
	SCHEMA(int,					offsets::CCSWeaponBase::m_iClip1,		m_iClip1		);
	SCHEMA(CCSWeaponBaseVData*, offsets::CCSWeaponBase::m_pWeaponVData, m_pWeaponVData	);
};