#pragma once
#include "../offsets.hpp"
#include "CEntityIterator.hpp"

class CEntityIdentity;

class CEntityClass {
public:
	CEntityClass() = delete;

	CEntityIdentity* m_pFirstEntity() const {
		return *reinterpret_cast<CEntityIdentity**>(THIS_ADDR + offsets::CEntityClass::m_pFirstEntity);
	}

	template <typename T>
	CEntityIterator<T, true> all_entities() const {
		return { m_pFirstEntity() };
	}
};