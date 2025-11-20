#pragma once
#include <Windows.h>

namespace offsets {
	namespace CCSPlayerController {
		inline const uintptr_t m_hPawn = 0x6B4;
		inline const uintptr_t m_iszPlayerName = 0x6e8; // char[128], m_sSanitizedPlayerName?
		inline const uintptr_t m_sSanitizedPlayerName = 0x850;
	}

	namespace CCSPlayerPawn {
		inline const uintptr_t m_bIsScoped = 0x2718;
		inline const uintptr_t m_bIsDefusing = 0x271A;
		inline const uintptr_t m_ArmorValue = 0x274c;
		inline const uintptr_t m_vOldOrigin = 0x15a0;
		inline const uintptr_t m_iHealth = 0x34c;
		inline const uintptr_t m_iTeamNum = 0x3eb;
		inline const uintptr_t m_pGameSceneNode = 0x330;
		inline const uintptr_t m_pCollision = 0x340;
		inline const uintptr_t m_pMovementServices = 0x1430;
		inline const uintptr_t m_hController = 0x15B8;
	}

	namespace CCollisionProperty {
		inline const uintptr_t m_vecMins = 0x40;
		inline const uintptr_t m_vecMaxs = 0x4c;
	}

	namespace CGameSceneNode {
		inline const uintptr_t m_modelState = 0x190;
	}

	namespace CModelState {
		inline const uintptr_t BoneArray = 0x80;
	}

	namespace CPlayer_MovementServices {
		inline const uintptr_t m_flDuckAmount = 0x288;
	}
}