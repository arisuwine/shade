#pragma once
#include <cstdint>

class CEntityHandle
{
public:
	CEntityHandle() = delete;

	SCHEMA(uint32_t, 0x0, m_Index);
};