#include "hooks.hpp"

#include "minhook.h"

#include "game_overlay.hpp"
#include "glow.hpp"
#include "entity_system.hpp"
#include "view_render.hpp"

#include "../utils/debug.hpp"

bool hooks::initialize() {
	LOG("\n[HOOK] Initialization of hooks.\n");

	if (auto status = MH_Initialize(); status != MH_OK && status != MH_ERROR_ALREADY_INITIALIZED)
		LOG_AND_RETURN("[-] MH Initialize has failed. Status: %d\n", status);

	if (!GameOverlayHook::initialize())
		return FALSE;

	LOG("[+] GameOverlayHook has been initialized.\n");

	if (!GlowHook::initialize())
		return FALSE;

	LOG("[+] GlowHook has been initialized.\n");

	if (!EntitySystemHook::initialize())
		return FALSE;

	LOG("[+] EntitySystemHook has been initialized.\n");

	if (!ViewRenderHook::initialize())
		return FALSE;

	LOG("[+] ViewRenderHook has been initialized.\n");

	if (!OverrideViewModelHook::initialize())
		return FALSE;

	LOG("[+] OverrideViewModelHook has been initialized.\n");

	return TRUE;
}

bool hooks::shutdown() {
	if (!GlowHook::shutdown())
		return FALSE;

	if (!GameOverlayHook::shutdown())
		return FALSE;

	if (!EntitySystemHook::shutdown())
		return FALSE;

	if (!ViewRenderHook::shutdown())
		return FALSE;

	if (!OverrideViewModelHook::shutdown())
		return FALSE;

	return TRUE;
}