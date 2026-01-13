#pragma once
#include <cstdint>

#include "../offsets.hpp"

class CEntityHandle
{
public:
	CEntityHandle() = delete;

	SCHEMA(uint32_t, offsets::client::CEntityHandle::m_Index, m_Index);
};