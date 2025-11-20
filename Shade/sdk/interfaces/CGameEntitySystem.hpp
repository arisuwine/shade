#pragma once
#include "../modules.hpp"
#include "../offsets.hpp"
#include "../signatures.hpp"

class CGameEntitySystem {
private:
	static uintptr_t handle;
	CGameEntitySystem() = delete;

public:
	static uintptr_t get_entity_system();
	static uintptr_t GetEntityByIndex(int idx);
	static uintptr_t GetPawnByController(const uintptr_t& controller);
	static uintptr_t GetControllerByPawn(const uintptr_t& pawn);
};