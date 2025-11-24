#pragma once
#include "../offsets.hpp"
#include "CEntityIterator.hpp"

class CEntityIdentity;

class CEntityClass {
public:
	CEntityClass() = delete;

	SCHEMA(CEntityIdentity*, offsets::CEntityClass::m_pFirstEntity, m_pFirstEntity);

	template <typename T>
	CEntityIterator<T, true> all_entities() {
		return m_pFirstEntity;
	}
};