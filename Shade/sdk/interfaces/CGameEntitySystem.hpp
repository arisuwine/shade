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
};