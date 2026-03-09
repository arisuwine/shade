#pragma once
#include <cstdint>

#include "../offsets.hpp"

#include "../../utils/vmt/vmt.hpp"

class ConVarRef {
public:
	static inline const uint16_t kInvalidAccessIndex = 0xFFFF;

	SCHEMA(uint16_t,	0x0, m_ConVarAccessIndex	);
	SCHEMA(int,			0x4, m_ConVarRegisteredIndex);

	inline bool		IsValidRef()			 { return m_ConVarAccessIndex != kInvalidAccessIndex; }
	inline uint16_t GetAccessIndex()		 { return m_ConVarAccessIndex; }
	inline int		GetRegisteredIndex()	 { return m_ConVarRegisteredIndex; }
};

class ICVar /*: public IAppSystem*/  {
public:
	auto FindConVar(const char* name, bool allow_defensive = false) { // 11
		ConVarRef result;

		using fn = void(__fastcall*)(void*, ConVarRef*, const char*, bool);

		auto pFunc = vmt::GetVirtual<fn>(this, 11);
		if (pFunc)
			pFunc(this, &result, name, allow_defensive);

		return result;

		//return vmt::call_virtual_stret<ConVarRef>(this, 11, name, allow_defensive);
	}
};