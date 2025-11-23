#include "CGameEntitySystem.hpp"
#include "../sdk.hpp"

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

uintptr_t __fastcall CGameEntitySystem::GetPawnByController(const uintptr_t& controller) {
	int v1; // edx
	__int64 v2; // r9
	__int32* v3; // rax

	uintptr_t EntityList = reinterpret_cast<uintptr_t>(g_CGameEntitySystem) + 0x10;

	v1 = *(__int32*)(controller + offsets::CCSPlayerController::m_hPawn);
	if (v1 == -1 || !EntityList)
		return 0;
	if (v1 != -2
		&& (v2 = *(__int64*)(EntityList + 8 * ((unsigned __int64)(v1 & 0x7FFF) >> 9))) != 0
		&& (v3 = (__int32*)(v2 + 112LL * (v1 & 0x1FF))) != 0)
	{
		if (v3[4] != v1)
			v3 = 0;
	}
	else
	{
		v3 = 0;
	}
	if (v3)
		return *(__int64*)v3;
	else
		return 0;
}

uintptr_t __fastcall CGameEntitySystem::GetControllerByPawn(const uintptr_t& pawn) {
	int handle; // edx
	__int64 chunk; // r9
	__int32* entity; // rax

	uintptr_t EntityList = reinterpret_cast<uintptr_t>(g_CGameEntitySystem) + 0x10;

	handle = *(__int32*)(pawn + offsets::CCSPlayerPawn::m_hController);

	if (handle == -1 || !EntityList)
		return 0;

	if (handle != -2
		&& (chunk = *(__int64*)(EntityList + 8 * ((unsigned __int64)(handle & 0x7FFF) >> 9))) != 0
		&& (entity = (__int32*)(chunk + 112LL * (handle & 0x1FF))) != 0)
	{
		if (entity[4] != handle)
			entity = 0;
	}
	else
	{
		entity = 0;
	}

	if (entity)
		return *(__int64*)entity;
	else
		return 0;
}