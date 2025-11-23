#pragma once
#include <cstdint>
#include <optional>

#include "../modules.hpp"
#include "../offsets.hpp"
#include "../signatures.hpp"
#include "../utils/valve/utlmap.hpp"

class CConcreteEntityList;
class CEntityClass;

class CGameEntitySystem {
public:
	CGameEntitySystem() = delete;

	inline CConcreteEntityList* m_entityList() const {
		return reinterpret_cast<CConcreteEntityList*>(THIS_ADDR + 0x10);
	}

	auto& m_ClassesByName() {
		return *reinterpret_cast<CUtlMap<const char*, CEntityClass*, std::uint16_t, CDefCaselessStringLess>*>(THIS_ADDR + 0xAA0);
	}

	static uintptr_t GetEntityByIndex(int idx);
	static uintptr_t GetPawnByController(const uintptr_t& controller);
	static uintptr_t GetControllerByPawn(const uintptr_t& pawn);
};

