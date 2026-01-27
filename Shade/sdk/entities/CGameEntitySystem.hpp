#pragma once
#include <string_view>

#include "../offsets.hpp"

#include "CConcreteEntityList.hpp"
#include "CEntityClass.hpp"

#include "../utils/cutlmap.hpp"

#include "../utils/debug.hpp"

class CConcreteEntityList;
class CEntityClass;

class CGameEntitySystem {
public:
	using EntityMap = CUtlMap<const char*, CEntityClass*, std::uint16_t, CDefCaselessStringLess>;

	SCHEMA(CConcreteEntityList,		offsets::client::CGameEntitySystem::m_entityList,		m_entityList	);
	SCHEMA(EntityMap,				offsets::client::CGameEntitySystem::m_ClassesByName,	m_ClassesByName	);

	template <typename T>
	T* GetEntityByIndex(int idx);

	template <typename T>
	CEntityIterator<T, true> GetAll() {
		const char* class_name = typeid(T).name();
		if (!class_name)
			return nullptr;

		class_name += 6;
		auto class_by_name = m_ClassesByName[class_name];
		if (!class_by_name)
			return nullptr;

		auto first_entity = class_by_name->m_pFirstEntity;
		if (!first_entity)
			return nullptr;

		return first_entity;
	}
};

template <typename T>
T* CGameEntitySystem::GetEntityByIndex(int idx) {
	__int64 v2; // r9
	int v3; // ecx
	__int64 v4; // r8
	__int64 v5; // rax

	v2 = THIS_ADDR + 16;

	if (idx > 0x7FFE) {
		return 0;
	}

	v3 = idx >> 9;

	if ((unsigned int)v3 > 0x3F) {
		return 0;
	}

	v4 = *(__int64*)(v2 + 8LL * v3);
	if (v4 == 0) {
		return 0;
	}

	v5 = v4 + 112LL * (idx & 0x1FF);
	if (v5 == 0) {
		return 0;
	}

	if ((*(__int64*)(v5 + 16) & 0x7FFF) != idx) {
		return 0;
	}

	return *(T**)(*(__int64*)(v2 + 8LL * v3) + 112LL * (idx & 0x1FF));
}