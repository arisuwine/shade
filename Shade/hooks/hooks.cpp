#include "hooks.hpp"

#include "minhook.h"
#include "imgui_impl_dx11.h"

#include "game_overlay.hpp"
#include "glow.hpp"
#include "entity_system.hpp"
#include "view_render.hpp"

#include "../utils/debug.hpp"

bool hooks::Initialize() {
	LOG("\n[HOOK] Initialization of hooks.\n");

	if (auto status = MH_Initialize(); status != MH_OK && status != MH_ERROR_ALREADY_INITIALIZED)
		LOG_AND_RETURN("[-] MH Initialize has failed. Status: %d\n", status);

	if (!GameOverlayHook::Initialize())
		return FALSE;

	LOG("[+] GameOverlayHook has been initialized.\n");

	if (!GlowHook::Initialize())
		return FALSE;

	LOG("[+] GlowHook has been initialized.\n");

	if (!EntitySystemHook::Initialize())
		return FALSE;

	LOG("[+] EntitySystemHook has been initialized.\n");

	if (!ViewRenderHook::Initialize())
		return FALSE;

	LOG("[+] ViewRenderHook has been initialized.\n");

	if (!OverrideViewModelHook::Initialize())
		return FALSE;

	LOG("[+] OverrideViewModelHook has been initialized.\n");

	return TRUE;
}

bool hooks::Shutdown() {
	if (!GameOverlayHook::Shutdown())
		return FALSE;

	if (!GlowHook::Shutdown())
		return FALSE;

	if (!EntitySystemHook::Shutdown())
		return FALSE;

	if (!ViewRenderHook::Shutdown())
		return FALSE;

	if (!OverrideViewModelHook::Shutdown())
		return FALSE;

	MH_Uninitialize();

	return TRUE;
}