#pragma once
#include <Windows.h>

#define THIS_ADDR reinterpret_cast<uintptr_t>(this)
#define CONST_OFFSET constexpr uintptr_t

namespace offsets {
	namespace CCSPlayerController {
		CONST_OFFSET m_hPawn					= 0x6B4;
		CONST_OFFSET m_iszPlayerName			= 0x6e8; // char[128], m_sSanitizedPlayerName?
		CONST_OFFSET m_sSanitizedPlayerName		= 0x850;
		CONST_OFFSET m_pEntity					= 0x10;
	}

	namespace CCSPlayerPawn {
		CONST_OFFSET m_bIsScoped				= 0x2718;
		CONST_OFFSET m_bIsDefusing				= 0x271A;
		CONST_OFFSET m_ArmorValue				= 0x274c;
		CONST_OFFSET m_vOldOrigin				= 0x15a0;
		CONST_OFFSET m_iHealth					= 0x34c;
		CONST_OFFSET m_iTeamNum					= 0x3eb;
		CONST_OFFSET m_pGameSceneNode			= 0x330;
		CONST_OFFSET m_pCollision				= 0x340;
		CONST_OFFSET m_pMovementServices		= 0x1430;
		CONST_OFFSET m_hController				= 0x15B8;
	}

	namespace CCollisionProperty {
		CONST_OFFSET m_vecMins					= 0x40;
		CONST_OFFSET m_vecMaxs					= 0x4c;
	}

	namespace CGameSceneNode {
		CONST_OFFSET m_modelState				= 0x190;
		CONST_OFFSET m_vecAbsOrigin				= 0xD0;
	}

	namespace CModelState {
		CONST_OFFSET BoneArray					= 0x80;
	}

	namespace CPlayer_MovementServices {
		CONST_OFFSET m_flDuckAmount				= 0x288;
	}

	namespace CEntityIdentity {
		CONST_OFFSET m_name						= 0x20;
		CONST_OFFSET m_pPrev					= 0x50;
		CONST_OFFSET m_pNext					= 0x58;
		CONST_OFFSET m_pPrevByClass				= 0x60;
		CONST_OFFSET m_pNextByClass				= 0x68;
	}

	namespace CEntityClass {
		CONST_OFFSET m_pFirstEntity				= 0x108;
	}
}