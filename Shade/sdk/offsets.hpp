#pragma once
#include <Windows.h>
#include <cstring>

#define THIS_ADDR reinterpret_cast<uintptr_t>(this)

#define GET_PSCHEMA(NAME, TYPE, OFFSET)									\
	inline TYPE& Get_##NAME() {											\
		return *(TYPE*)(THIS_ADDR + OFFSET);							\
	}																	\

#define SET_PSCHEMA(NAME, TYPE, OFFSET)									\
    inline void Set_##NAME(TYPE val) {									\
        std::memcpy((void*)(THIS_ADDR + OFFSET), &val, sizeof(TYPE));	\
    }																	\

#define PSCHEMA(TYPE, OFFSET, NAME)										\
    __declspec( property( get=Get_##NAME, put=Set_##NAME ) ) TYPE NAME; \
    GET_PSCHEMA(NAME, TYPE, OFFSET);									\
    SET_PSCHEMA(NAME, TYPE, OFFSET);									\

#define GET_SCHEMA(NAME, TYPE, OFFSET)									\
	inline TYPE Get_##NAME() {											\
		return *(TYPE*)(THIS_ADDR + OFFSET);							\
	}																	\

#define SET_SCHEMA(NAME, TYPE, OFFSET)									\
	inline void Set_##NAME(TYPE val) {									\
		*(TYPE*)(THIS_ADDR + OFFSET) = val;								\
	}																	\

#define SCHEMA(TYPE, OFFSET, NAME)										\
    __declspec( property( get=Get_##NAME, put=Set_##NAME ) ) TYPE NAME; \
    GET_SCHEMA(NAME, TYPE, OFFSET);										\
    SET_SCHEMA(NAME, TYPE, OFFSET);										\

#define CONST_OFFSET constexpr uintptr_t

namespace offsets {
	namespace client {
		namespace C_CSPlayerController {
			CONST_OFFSET m_hPawn							= 0x6B4;
			CONST_OFFSET m_iszPlayerName					= 0x6e8;
			CONST_OFFSET m_sSanitizedPlayerName				= 0x850;
			CONST_OFFSET m_pEntity							= 0x10;
		}

		namespace C_BaseEntity {
			CONST_OFFSET m_iHealth							= 0x34c;
			CONST_OFFSET m_iTeamNum							= 0x3eb;
			CONST_OFFSET m_pCollision						= 0x340;
			CONST_OFFSET m_pGameSceneNode					= 0x330;
			CONST_OFFSET m_hOwnerEntity						= 0x520;
		}

		namespace CConcreteEntityList {
			CONST_OFFSET m_pIdentityChunks					= 0x0;
			CONST_OFFSET m_pFirstActiveEntity				= 0x200;
			CONST_OFFSET m_usedList_Head					= 0x208;
		}

		namespace CEntityHandle {
			CONST_OFFSET m_Index							= 0x0;
		}

		namespace C_BasePlayerPawn {
			CONST_OFFSET m_vOldOrigin						= 0x15a0;
			CONST_OFFSET m_pMovementServices				= 0x1430;
			CONST_OFFSET m_pWeaponServices					= 0x13F0;
			CONST_OFFSET m_hController						= 0x15B8;
		}

		namespace C_CSPlayerPawn {
			CONST_OFFSET m_bIsScoped						= 0x2718;
			CONST_OFFSET m_bIsDefusing						= 0x271A;
			CONST_OFFSET m_ArmorValue						= 0x274c;
			CONST_OFFSET m_pClippingWeapon					= 0x3de0;
		}

		namespace CCollisionProperty {
			CONST_OFFSET m_vecMins							= 0x40;
			CONST_OFFSET m_vecMaxs							= 0x4c;
		}

		namespace CGameSceneNode {
			CONST_OFFSET m_modelState						= 0x190;
			CONST_OFFSET m_vecAbsOrigin						= 0xD0;
		}

		namespace CModelState {
			CONST_OFFSET BoneArray							= 0x80;
		}

		namespace CPlayer_MovementServices {
			CONST_OFFSET m_flDuckAmount						= 0x288;
		}

		namespace CEntityIdentity {
			CONST_OFFSET m_pClass							= 0x8;	// CEntityClass*
			CONST_OFFSET m_EHandle							= 0x10;
			CONST_OFFSET m_name								= 0x20;
			CONST_OFFSET m_designerName						= 0x28;
			CONST_OFFSET m_flags							= 0x30;
			CONST_OFFSET m_pPrev							= 0x50;
			CONST_OFFSET m_pNext							= 0x58;
			CONST_OFFSET m_pPrevByClass						= 0x60;
			CONST_OFFSET m_pNextByClass						= 0x68;
		}

		namespace CEntityClass {
			CONST_OFFSET m_pFirstEntity						= 0x108;
		}

		namespace CEntityInstance {
			CONST_OFFSET m_pEntity							= 0x10;
		}

		namespace CGameEntitySystem {
			CONST_OFFSET m_entityList						= 0x10;
			CONST_OFFSET m_ClassesByName					= 0xAA0;
		}

		namespace CPlayer_WeaponServices {
			CONST_OFFSET m_hMyWeapons						= 0x40;
			CONST_OFFSET m_hActiveWeapon					= 0x58;
			CONST_OFFSET m_iAmmo							= 0x60;
		}

		namespace C_BasePlayerWeapon {
			CONST_OFFSET m_iClip1							= 0x18f0;
		}

		namespace C_CSWeaponBase {
			CONST_OFFSET m_pWeaponVData						= 0x388;
		}

		namespace CCSWeaponBaseVData {
			CONST_OFFSET m_szName							= 0x720;
			CONST_OFFSET m_iMaxClip1						= 0x3e8;
			CONST_OFFSET m_iMaxClip2						= 0x3ec;
		}

		namespace CGlowObjectManager {
			CONST_OFFSET m_GlowObjectDefinitions			= 0x20;
		}

		namespace CGlowProperty {
			CONST_OFFSET m_vGlowColor						= 0x8;
			CONST_OFFSET m_pParent							= 0x18;
			CONST_OFFSET m_glowColorOverride				= 0x40;
			CONST_OFFSET m_bGlowing							= 0x51;
		}

		namespace CGlobalVarsBase {
			CONST_OFFSET m_flRealTime						= 0x0;
			CONST_OFFSET m_iFrameCount						= 0x4;
			CONST_OFFSET m_flAbsoluteFrameTime				= 0x8;
			CONST_OFFSET m_flAbsoluteFrameStartTimesTDDev	= 0xc;
			CONST_OFFSET m_iMaxClients						= 0x10;
			CONST_OFFSET m_iUnknown1						= 0x14;
			CONST_OFFSET m_iUnknown2						= 0x18;
			CONST_OFFSET m_iUnknown3						= 0x1c;
			CONST_OFFSET m_iUnknown4						= 0x20;
			CONST_OFFSET m_iUnknown5						= 0x24;
			CONST_OFFSET m_pfnWarningFunc					= 0x28; // FnGlobalVarsWarningFunc
			CONST_OFFSET m_flCurTime						= 0x30;
			CONST_OFFSET m_flFrameTime						= 0x34;
			CONST_OFFSET m_iUnknown6						= 0x38;
			CONST_OFFSET m_iUnknown7						= 0x3c;
			CONST_OFFSET m_bInSimulation					= 0x40;
			CONST_OFFSET m_bEnableAssertions				= 0x41;
			CONST_OFFSET m_iTickCount						= 0x44;
			CONST_OFFSET m_iUnknown8						= 0x48;
			CONST_OFFSET m_iUnknown9						= 0x4c;
			CONST_OFFSET m_flSubtickFraction				= 0x50;
		}

		namespace CViewSetup {
			CONST_OFFSET m_flFov							= 0x4d8;
			CONST_OFFSET m_flFovViewModel					= 0x4dc;
			CONST_OFFSET m_vecOrigin						= 0x4e0;
			CONST_OFFSET m_angView							= 0x4fc;
			CONST_OFFSET m_flAspectRatio					= 0x518;
			CONST_OFFSET m_nSomeFlags						= 0x595;
		}

		namespace CViewRender {
			CONST_OFFSET m_CurrentView						= 0x10;
		}
	}

	namespace engine2 {
		namespace CNetworkClientService {
			CONST_OFFSET m_pCNetworkGameClient				= 0x98;
		}
	}

	namespace tier0 {
		namespace ConVarRef {
			CONST_OFFSET m_ConVarAccessIndex				= 0x0;
			CONST_OFFSET m_ConVarRegisteredIndex			= 0x4;
		}
	}
}