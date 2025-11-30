#pragma once
#include "../offsets.hpp"

class CEntityIdentity;

class CEntityInstance {
public:
	CEntityInstance() = delete;
	
	SCHEMA(CEntityIdentity*, offsets::CEntityInstance::m_pEntity, m_pEntity);
};