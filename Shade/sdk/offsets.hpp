#pragma once
#include <Windows.h>
#include <cstring>

#define RESOLVE_RIP_EX(type, addr, offset, size) reinterpret_cast<type*>(addr + *((int32_t*)(addr + offset)) + size)
#define RESOLVE_RIP(type, addr) RESOLVE_RIP_EX(type, addr, 3, 7)
#define RESOLVE_RELATIVE(type, addr) *reinterpret_cast<type**>(RESOLVE_RIP(type, addr))
#define RESOLVE_RELATIVE_EX(type, addr, offset, size) *reinterpret_cast<type**>(RESOLVE_RIP_EX(type, addr, offset, size))

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
		namespace CCSPlayerController {
			CONST_OFFSET m_hPawn							= 0x6C4;
			CONST_OFFSET m_iszPlayerName					= 0x6F8;
			CONST_OFFSET m_sSanitizedPlayerName				= 0x860;
		}

		namespace IGameResourceService {
			CONST_OFFSET m_pCGameEntitySystem				= 0x58;
		}

		namespace C_BaseEntity {
			CONST_OFFSET m_iHealth							= 0x354;
			CONST_OFFSET m_iTeamNum							= 0x3F3;
			CONST_OFFSET m_pCollision						= 0x348;
			CONST_OFFSET m_pGameSceneNode					= 0x338;
			CONST_OFFSET m_fFlags							= 0x400;
			CONST_OFFSET m_hOwnerEntity						= 0x528;
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
			CONST_OFFSET m_vOldOrigin						= 0x1588;
			CONST_OFFSET m_pMovementServices				= 0x1418;
			CONST_OFFSET m_pWeaponServices					= 0x13D8;
			CONST_OFFSET m_hController						= 0x15A0;
		}

		namespace C_CSPlayerPawn {
			CONST_OFFSET m_bIsScoped						= 0x26F8;
			CONST_OFFSET m_bIsDefusing						= 0x26FA;
			CONST_OFFSET m_ArmorValue						= 0x272C;
			CONST_OFFSET m_pClippingWeapon					= 0x3DC0;
		}

		namespace CCollisionProperty {
			CONST_OFFSET m_vecMins							= 0x40;
			CONST_OFFSET m_vecMaxs							= 0x4C;
		}

		namespace CGameSceneNode {
			CONST_OFFSET m_modelState						= 0x160;
			CONST_OFFSET m_vecAbsOrigin						= 0xD0;
		}

		namespace CModelState {
			CONST_OFFSET BoneArray							= 0x80;
		}

		namespace CPlayer_MovementServices {
			CONST_OFFSET m_flDuckAmount						= 0x284;
		}

		namespace CEntityIdentity {
			CONST_OFFSET m_pClass							= 0x8;	// CEntityClass*
			CONST_OFFSET m_EHandle							= 0x10;
			CONST_OFFSET m_name								= 0x18; // 0x20
			CONST_OFFSET m_designerName						= 0x20; // 0x20
			CONST_OFFSET m_flags							= 0x30;
			CONST_OFFSET m_pPrev							= 0x50;
			CONST_OFFSET m_pNext							= 0x58;
			CONST_OFFSET m_pPrevByClass						= 0x60;
			CONST_OFFSET m_pNextByClass						= 0x68;
		}

		namespace CEntityClass {
			CONST_OFFSET m_pFirstEntity						= 0x150;
		}

		namespace CEntityInstance {
			CONST_OFFSET m_pEntity							= 0x10;
		}

		namespace CGameEntitySystem {
			CONST_OFFSET m_entityList						= 0x10;
			CONST_OFFSET m_ClassesByName					= 0xAA0;
		}

		namespace CPlayer_WeaponServices {
			CONST_OFFSET m_hMyWeapons						= 0x48;
			CONST_OFFSET m_hActiveWeapon					= 0x60;
			CONST_OFFSET m_iAmmo							= 0x68;
		}

		namespace C_BasePlayerWeapon {
			CONST_OFFSET m_iClip1							= 0x18D0;
		}

		namespace C_CSWeaponBase {
			CONST_OFFSET m_pWeaponVData						= 0x390;
		}

		namespace CCSWeaponBaseVData {
			CONST_OFFSET m_szName							= 0x640;
			CONST_OFFSET m_iMaxClip1						= 0x3F0;
			CONST_OFFSET m_iMaxClip2						= 0x3F4;
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
			CONST_OFFSET m_flFov							= 0x498;
			CONST_OFFSET m_flFovViewModel					= 0x49C;
			CONST_OFFSET m_vecOrigin						= 0x4e0;
			CONST_OFFSET m_angView							= 0x4B8;
			CONST_OFFSET m_flAspectRatio					= 0x4d8;
			CONST_OFFSET m_nSomeFlags						= 0x555;
		}

		namespace CViewRender {
			CONST_OFFSET m_CurrentView						= 0x10;
		}

		namespace CUserCmd {
			CONST_OFFSET m_nButtons							= 0x58;
		}

		namespace CInButtonState {
			CONST_OFFSET m_nValue							= 0x8;
			CONST_OFFSET m_nValueChanged					= 0x10;
			CONST_OFFSET m_nValueScroll						= 0x18;
		}
	}

	namespace engine2 {
		namespace CNetworkClientService {
			CONST_OFFSET m_pCNetworkGameClient				= 0xA0;
		}
	}

	namespace tier0 {
		namespace ConVarRef {
			CONST_OFFSET m_ConVarAccessIndex				= 0x0;
			CONST_OFFSET m_ConVarRegisteredIndex			= 0x4;
		}
	}

	namespace rendersystemdx11 {
		namespace CSwapChainDx11 {
			CONST_OFFSET m_pDXGISwapChain					= 0x170;
		}
	}
}