#pragma once
#include <windows.h>

#include "../offsets.hpp"

#include "CEntityHandle.hpp"

enum EntityFlags_t : uint32_t
{
	EF_IS_INVALID_EHANDLE = 0x1,
	EF_SPAWN_IN_PROGRESS = 0x2,
	EF_IN_STAGING_LIST = 0x4,
	EF_IN_POST_DATA_UPDATE = 0x8,
	EF_DELETE_IN_PROGRESS = 0x10,
	EF_IN_STASIS = 0x20,
	EF_IS_ISOLATED_ALLOCATION_NETWORKABLE = 0x40,
	EF_IS_DORMANT = 0x80,
	EF_IS_PRE_SPAWN = 0x100,
	EF_MARKED_FOR_DELETE = 0x200,
	EF_IS_CONSTRUCTION_IN_PROGRESS = 0x400,
	EF_IS_ISOLATED_ALLOCATION = 0x800,
	EF_HAS_BEEN_UNSERIALIZED = 0x1000,
	EF_IS_SUSPENDED = 0x2000,
	EF_IS_ANONYMOUS_ALLOCATION = 0x4000,
	EF_SUSPEND_OUTSIDE_PVS = 0x8000,
};

class CEntityIdentity {
public:
	CEntityIdentity() = delete;

	template <typename T>
	T* m_pInstance() const {
		return *reinterpret_cast<T**>(THIS_ADDR);
	}

	SCHEMA(CEntityHandle,		offsets::CEntityIdentity::m_EHandle,		m_EHandle		);
	SCHEMA(const char*,			offsets::CEntityIdentity::m_name,			m_name			);
	SCHEMA(CEntityIdentity*,	offsets::CEntityIdentity::m_pPrev,			m_pPrev			);
	SCHEMA(CEntityIdentity*,	offsets::CEntityIdentity::m_pNext,			m_pNext			);
	SCHEMA(CEntityIdentity*,	offsets::CEntityIdentity::m_pPrevByClass,	m_pPrevByClass	);
	SCHEMA(CEntityIdentity*,	offsets::CEntityIdentity::m_pNextByClass,	m_pNextByClass	);
	SCHEMA(EntityFlags_t,		offsets::CEntityIdentity::m_flags,			m_flags			);
};