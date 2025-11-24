#include "../sdk.hpp"

#include "CGameEntitySystem.hpp"
#include "CConcreteEntityList.hpp"
#include "CEntityIdentity.hpp"

#define MAX_ENTITIES_IN_LIST 512
#define MAX_TOTAL_ENTITIES (MAX_ENTITIES_IN_LIST * MAX_ENTITY_LISTS)

uintptr_t CGameEntitySystem::GetEntityByIndex(int idx) {
	__int64 v2; // r9
	int v3; // ecx
	__int64 v4; // r8
	__int64 v5; // rax

	v2 = reinterpret_cast<uintptr_t>(g_CGameEntitySystem) + 16;

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

	return *(__int64*)(*(__int64*)(v2 + 8LL * v3) + 112LL * (idx & 0x1FF));
}