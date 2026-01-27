#pragma once
#include "../offsets.hpp"

class CGameEntitySystem;

class IGameResourceService {
public:
	SCHEMA(CGameEntitySystem*, offsets::client::IGameResourceService::m_pCGameEntitySystem, m_pCGameEntitySystem);
};