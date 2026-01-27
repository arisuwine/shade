#pragma once
#include "../offsets.hpp"

class CBasePlayerWeaponVData {
public:
	SCHEMA(int,			offsets::client::CCSWeaponBaseVData::m_iMaxClip1,	m_iMaxClip1	);
	SCHEMA(int,			offsets::client::CCSWeaponBaseVData::m_iMaxClip2,	m_iMaxClip2	);
};

class CCSWeaponBaseVData : public CBasePlayerWeaponVData {
public:
	SCHEMA(const char*, offsets::client::CCSWeaponBaseVData::m_szName,		m_szName	);
};