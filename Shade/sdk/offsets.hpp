#pragma once
#include <Windows.h>
#include <cstring>

#define THIS_ADDR reinterpret_cast<uintptr_t>(this)

#define GET_SCHEMA_RAW(NAME, TYPE, OFFSET)								\
	inline TYPE& Get_##NAME() {											\
		return *(TYPE*)(THIS_ADDR + OFFSET);							\
	}

#define SET_SCHEMA_RAW(NAME, TYPE, OFFSET)								\
    inline void Set_##NAME(TYPE val) {									\
        std::memcpy((void*)(THIS_ADDR + OFFSET), &val, sizeof(TYPE));	\
    }

#define SCHEMA_R(TYPE, OFFSET, NAME)									\
    __declspec( property( get=Get_##NAME, put=Set_##NAME ) ) TYPE NAME; \
    GET_SCHEMA_RAW(NAME, TYPE, OFFSET);									\
    SET_SCHEMA_RAW(NAME, TYPE, OFFSET);

#define GET_SCHEMA(NAME, TYPE, OFFSET)									\
	inline TYPE Get_##NAME() {											\
		return *(TYPE*)(THIS_ADDR + OFFSET);							\
	}

#define SET_SCHEMA(NAME, TYPE, OFFSET)									\
	inline void Set_##NAME(TYPE val) {									\
		*(TYPE*)(THIS_ADDR + OFFSET) = val;								\
	}

#define SCHEMA(TYPE, OFFSET, NAME)										\
    __declspec( property( get=Get_##NAME, put=Set_##NAME ) ) TYPE NAME; \
    GET_SCHEMA(NAME, TYPE, OFFSET);										\
    SET_SCHEMA(NAME, TYPE, OFFSET);										\

#define CONST_OFFSET constexpr uintptr_t

namespace offsets {
	namespace CCSPlayerController {
		CONST_OFFSET m_hPawn					= 0x6B4;
		CONST_OFFSET m_iszPlayerName			= 0x6e8;
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
		CONST_OFFSET m_pWeaponServices			= 0x13F0;
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
		CONST_OFFSET m_EHandle					= 0x10;
		CONST_OFFSET m_flags					= 0x30;
	}

	namespace CEntityClass {
		CONST_OFFSET m_pFirstEntity				= 0x108;
	}

	namespace CEntityInstance {
		CONST_OFFSET m_pEntity					= 0x10;
	}

	namespace CGameEntitySystem {
		CONST_OFFSET m_entityList				= 0x10;
		CONST_OFFSET m_ClassesByName			= 0xAA0;
	}

	namespace CPlayer_WeaponServices {
		CONST_OFFSET m_hMyWeapons				= 0x40;
		CONST_OFFSET m_hActiveWeapon			= 0x58;
	}
}