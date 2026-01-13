#include "sdk.hpp"

#include "modules.hpp"
#include "signatures.hpp"

#include "../utils/debug.hpp"

#include "interfaces/CInterfaceSystem.hpp"

void interfaces::Initialize() {
	LOG("[INTERFACE] Initialization of interfaces.\n");

	// client.dll
	g_CGameEntitySystem		= DEREFERENCE(CGameEntitySystem,				modules::client.find(GAME_ENTITY_SYSTEM));
	g_CViewRender			= RESOLVE_RIP(CViewRender,						modules::client.find(VIEW_RENDER));
	g_ViewMatrix			= RESOLVE_RIP(ViewMatrix,						modules::client.find(VIEW_MATRIX));
	g_CGlowObjectManager	= RESOLVE_RIP(CGlowObjectManager,				modules::client.find(GLOW_MANAGER));
	gpGlobals				= RESOLVE_RIP(CGlobalVarsBase,					modules::client.find(GP_GLOBALS));

	LOG("g_CViewRender: %p\n", g_CViewRender);

	g_CNetworkClientService = CInterfaceSystem::Get<CNetworkClientService>	("engine2.dll",			"NetworkClientService_001");
	g_EngineClient			= CInterfaceSystem::Get<IVEngineClient>			("engine2.dll",			"Source2EngineToClient001");
	g_CVar					= CInterfaceSystem::Get<ICVar>					("tier0.dll",			"VEngineCvar007");
	g_CSchemaSystem			= CInterfaceSystem::Get<CShemaSystem>			("schemasystem.dll",	"SchemaSystem_001");
}