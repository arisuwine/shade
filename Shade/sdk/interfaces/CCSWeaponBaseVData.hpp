#pragma once
#include "../offsets.hpp"

class CCSWeaponBaseVData {
public:
	CCSWeaponBaseVData() = delete;

	SCHEMA(const char*, offsets::CCSWeaponBaseVData::m_szName,		m_szName	);
	SCHEMA(int,			offsets::CCSWeaponBaseVData::m_iMaxClip1,	m_iMaxClip1	);
	SCHEMA(int,			offsets::CCSWeaponBaseVData::m_iMaxClip2,	m_iMaxClip2	);
};