#pragma once
#include <cstdint>

#include "../offsets.hpp"

#include "../../utils/vmt/vmt.hpp"

class ConVarRef
{
public:
	static inline const uint16_t kInvalidAccessIndex = 0xFFFF;

	ConVarRef();

	SCHEMA(uint16_t,	offsets::ConVarRef::m_ConVarAccessIndex,		m_ConVarAccessIndex		);
	SCHEMA(int,			offsets::ConVarRef::m_ConVarRegisteredIndex,	m_ConVarRegisteredIndex	);

	//inline void InvalidateRef() { m_ConVarAccessIndex = kInvalidAccessIndex; m_ConVarRegisteredIndex = 0; }
	inline bool		IsValidRef()			 { return m_ConVarAccessIndex != kInvalidAccessIndex; }
	inline uint16_t GetAccessIndex()		 { return m_ConVarAccessIndex; }
	inline int		GetRegisteredIndex()	 { return m_ConVarRegisteredIndex; }
};

class ICVar { // public IAppSystem
public:
	ICVar() = delete;

	auto FindConVar(const char* name, bool allow_defensive = false) { // 11
		ConVarRef result;

		using fn = void(__fastcall*)(void*, ConVarRef*, const char*, bool);

		auto pFunc = vmt::get_virtual<fn>(this, 11);
		if (pFunc)
			pFunc(this, &result, name, allow_defensive);

		return result;

		//return vmt::call_virtual_stret<ConVarRef>(this, 11, name, allow_defensive);
	}
};