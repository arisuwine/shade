#pragma once
#include <cstdint>

#include "../offsets.hpp"

class CEntityHandle
{
public:
	SCHEMA(uint32_t, offsets::client::CEntityHandle::m_Index, m_Index);
};