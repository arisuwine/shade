#pragma once
#include "../offsets.hpp"

class CEntityIdentity;

class C_CSWeaponBase {
public:
	C_CSWeaponBase() = delete;

	SCHEMA(CEntityIdentity*,	offsets::C_CSWeaponBase::m_pEntity, m_pEntity	);
	SCHEMA(uint32_t,			offsets::C_CSWeaponBase::m_iClip1,	m_iClip1	);
};