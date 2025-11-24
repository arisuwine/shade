#pragma once
#include <cstdint>
#include <optional>

#include "../modules.hpp"
#include "../offsets.hpp"
#include "../signatures.hpp"
#include "../utils/valve/utlmap.hpp"

#include "CEntityHandle.hpp"
#include "CEntityIdentity.hpp"
#include "CConcreteEntityList.hpp"

class CConcreteEntityList;
class CEntityClass;

class CGameEntitySystem {
public:
	CGameEntitySystem() = delete;

	using EntityMap = CUtlMap<const char*, CEntityClass*, std::uint16_t, CDefCaselessStringLess>;

	SCHEMA(CConcreteEntityList,		offsets::CGameEntitySystem::m_entityList,		m_entityList	);
	SCHEMA(EntityMap,				offsets::CGameEntitySystem::m_ClassesByName,	m_ClassesByName	);

	static uintptr_t		GetEntityByIndex	(int idx);
};

