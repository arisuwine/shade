#include "sdk.hpp"

#include "modules.hpp"
#include "signatures.hpp"

#include "../utils/debug.hpp"

#include "interfaces/CInterfaceSystem.hpp"

#include "services/CSwapChainDx11.hpp"

void globals::Initialize() {
	lg::Info("[GLOBALS]", "Initialization of global variables.\n");

	g_pViewRender				= RESOLVE_RIP		(CViewRender,				modules::client.Find(VIEW_RENDER		));
	g_pViewMatrix				= RESOLVE_RIP		(ViewMatrix,				modules::client.Find(VIEW_MATRIX		));
	g_pCGlowObjectManager		= RESOLVE_RIP		(CGlowObjectManager,		modules::client.Find(GLOW_MANAGER		));
	g_pGlobalVars				= RESOLVE_RIP		(CGlobalVarsBase,			modules::client.Find(GP_GLOBALS			));
	g_pCSGOInput				= RESOLVE_RIP		(CCSGOInput,				modules::client.Find(CSGO_INPUT			));

	g_pNetworkClientService		= CInterfaceSystem::Get<INetworkClientService>	("engine2.dll",			"NetworkClientService_001"		);
	g_pEngineClient				= CInterfaceSystem::Get<IVEngineClient>			("engine2.dll",			"Source2EngineToClient001"		);
	g_pCVar						= CInterfaceSystem::Get<ICVar>					("tier0.dll",			"VEngineCvar007"				);
	g_pSchemaSystem				= CInterfaceSystem::Get<ISchemaSystem>			("schemasystem.dll",	"SchemaSystem_001"				);
	g_pSource2Client			= CInterfaceSystem::Get<ISource2Client>			("client.dll",			"Source2Client002"				);
	g_pGameResourceService		= CInterfaceSystem::Get<IGameResourceService>	("engine2.dll",			"GameResourceServiceClientV001"	);
	g_pEngineServiceMgr			= CInterfaceSystem::Get<IEngineServiceMgr>		("engine2.dll",			"EngineServiceMgr001"			);

	g_pGameEntitySystem			= g_pGameResourceService->m_pGameEntitySystem;
	g_pSwapChain				= g_pEngineServiceMgr->GetEngineSwapChain()->m_pDXGISwapChain;
}