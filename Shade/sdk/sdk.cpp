#include "sdk.hpp"

#include "modules.hpp"
#include "signatures.hpp"

#include "../utils/debug.hpp"

#include "interfaces/CInterfaceSystem.hpp"

void interfaces::Initialize() {
	LOG("[INTERFACE] Initialization of interfaces.\n");

	// client.dll
	//g_CGameEntitySystem		= RESOLVE_RELATIVE	(CGameEntitySystem,					modules::client.Find(GAME_ENTITY_SYSTEM	));
	//g_CViewRender			= RESOLVE_RIP		(CViewRender,						modules::client.Find(VIEW_RENDER		));
	g_ViewMatrix			= RESOLVE_RIP		(ViewMatrix,						modules::client.Find(VIEW_MATRIX		));
	g_CGlowObjectManager	= RESOLVE_RIP		(CGlowObjectManager,				modules::client.Find(GLOW_MANAGER		));
	gpGlobals				= RESOLVE_RIP		(CGlobalVarsBase,					modules::client.Find(GP_GLOBALS			));

	//LOG("g_CViewRender: %p\n", g_CViewRender);

	g_CNetworkClientService = CInterfaceSystem::Get<CNetworkClientService>	("engine2.dll",			"NetworkClientService_001"		);
	g_EngineClient			= CInterfaceSystem::Get<IVEngineClient>			("engine2.dll",			"Source2EngineToClient001"		);
	g_CVar					= CInterfaceSystem::Get<ICVar>					("tier0.dll",			"VEngineCvar007"				);
	g_CSchemaSystem			= CInterfaceSystem::Get<CShemaSystem>			("schemasystem.dll",	"SchemaSystem_001"				);
	g_Source2Client			= CInterfaceSystem::Get<ISource2Client>			("client.dll",			"Source2Client002"				);
	g_GameResourceService	= CInterfaceSystem::Get<IGameResourceService>	("engine2.dll",			"GameResourceServiceClientV001"	);

	g_CGameEntitySystem		= g_GameResourceService->m_pCGameEntitySystem;
}