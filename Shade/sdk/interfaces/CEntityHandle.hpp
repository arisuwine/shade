#pragma once
#include <cstdint>

#define INVALID_EHANDLE_INDEX 0xFFFFFFFF

class CEntityInstance;

class CEntityHandle
{
public:
	CEntityHandle() = delete;

	friend class CEntityIdentity;

	SCHEMA(uint32_t, 0x0, m_Index);
};

typedef CEntityHandle CBaseHandle;