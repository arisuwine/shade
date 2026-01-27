#pragma once
#include "../offsets.hpp"

#include "CEntityIterator.hpp"

class CEntityIdentity;

class CEntityClass {
public:
	SCHEMA(CEntityIdentity*, offsets::client::CEntityClass::m_pFirstEntity, m_pFirstEntity);

	template <typename T>
	CEntityIterator<T, true> GetAll() {
		return m_pFirstEntity;
	}
};