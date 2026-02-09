#include "hooks.hpp"

#include "entity_system.hpp"
#include "game_overlay.hpp"
#include "glow.hpp"
#include "source2client.hpp"
#include "view_render.hpp"
#include "idxgiswapchain.hpp"

#include "../utils/debug.hpp"

void hooks::Initialize() {
	printf("\n");
	lg::Info("[HOOKS]", "Hooks initialization.\n");

	CDetourHook::Initialize();

	CEntitySystemHook::Register();
	CIsGlowingHook::Register();
	CApplyGlowHook::Register();
	CViewRenderHook::Register();
	COverrideFovHook::Register();
	CSetupViewModelHook::Register();
	CIDXGISwapChainHook::Register();
}

void hooks::Shutdown() {
	printf("\n");
	lg::Info("[HOOKS]", "Hooks shutdown.\n");
	
	g_pHooks.clear(); // hooks shutdown

	CDetourHook::Uninitialize();
} 