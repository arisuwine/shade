#include "CGameEntitySystem.hpp"

uintptr_t CGameEntitySystem::get_entity_system() {
	uintptr_t address = handle + *((int32_t*)(handle + 3)) + 7;
	return *reinterpret_cast<uintptr_t*>(address);
}

uintptr_t CGameEntitySystem::GetEntityByIndex(int idx) {
	__int64 v2; // r9
	int v3; // ecx
	__int64 v4; // r8
	__int64 v5; // rax

	v2 = get_entity_system() + 16;
	if (idx <= 0x7FFE
		&& (v3 = (int)idx >> 9, (unsigned int)((int)idx >> 9) <= 0x3F)
		&& (v4 = *(__int64*)(v2 + 8LL * v3)) != 0
		&& (v5 = v4 + 112LL * (idx & 0x1FF)) != 0
		&& (*(__int64*)(v5 + 16) & 0x7FFF) == idx)
	{
		return *(__int64*)(*(__int64*)(v2 + 8LL * v3) + 112LL * (idx & 0x1FF));
	}
	else
	{
		return 0;
	}
}