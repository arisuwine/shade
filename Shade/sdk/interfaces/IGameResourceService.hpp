#pragma once
#include "../offsets.hpp"

class CGameEntitySystem;

class IGameResourceService {
public:
	SCHEMA(CGameEntitySystem*, 0x58, m_pGameEntitySystem);
};