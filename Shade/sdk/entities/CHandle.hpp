#pragma once
#include "../sdk.hpp"

#include "CEntityHandle.hpp"

#define INVALID_EHANDLE_INDEX	0xFFFFFFFF

template<typename T>
class CHandle
{
public:
	CHandle() = delete;

	T* GetEntityFromHandle() const {
		int v1;
		__int64 v2;
		__int32* v3;

		uintptr_t EntityList = reinterpret_cast<uintptr_t>(g_CGameEntitySystem) + 0x10;

		v1 = *(__int32*)(this);
		if (v1 == -1 || !EntityList)
			return nullptr;
		if (v1 != -2
			&& (v2 = *(__int64*)(EntityList + 8 * ((unsigned __int64)(v1 & 0x7FFF) >> 9))) != 0
			&& (v3 = (__int32*)(v2 + 112LL * (v1 & 0x1FF))) != 0)
		{
			if (v3[4] != v1)
				v3 = 0;
		}
		else
		{
			v3 = 0;
		}
		if (v3)
			return *(T**)v3;
		else
			return nullptr;
	}

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
		return m_Index != INVALID_EHANDLE_INDEX;
	}
};