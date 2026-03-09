#pragma once
#include <cstdint>

#include "../offsets.hpp"

#define INVALID_EHANDLE_INDEX 0xFFFFFFFF

class CEntityHandle {
public:
	union
	{
		uint32_t m_Index;
		struct
		{
			uint32_t m_EntityIndex : 15;
			uint32_t m_Serial : 17;
		} m_Parts;
	};

	inline bool IsValid() const {
		return m_Index != INVALID_EHANDLE_INDEX && m_Index != -1;
	}
};