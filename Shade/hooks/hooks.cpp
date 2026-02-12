#include "hooks.hpp"

#include "entity_system.hpp"
#include "glow.hpp"
#include "source2client.hpp"
#include "view_render.hpp"
#include "idxgiswapchain.hpp"
#include "ccsgoinput.hpp"

#include "../utils/debug.hpp"

void hooks::Initialize() {
	printf("\n");
	lg::Info("[HOOKS]", "Hooks initialization.\n");

	CDetourHook::Initialize();

	CIDXGISwapChainHook::Register();
	CEntitySystemHook::Register();
	CIsGlowingHook::Register();
	CApplyGlowHook::Register();
	CViewRenderHook::Register();
	CSetupFovHook::Register();
	CSetupViewModelHook::Register();
	CCSGOInputHook::Register();
}

void hooks::Shutdown() {
	printf("\n");
	lg::Info("[HOOKS]", "Hooks shutdown.\n");
	
	g_pHooks.clear(); // hooks shutdown

	CDetourHook::Uninitialize();
} 