#include "hooks.hpp"

#include <tuple>

#include "minhook.h"
#include "imgui_impl_dx11.h"

#include "game_overlay.hpp"
#include "glow.hpp"
#include "entity_system.hpp"
#include "view_render.hpp"
#include "source2client.hpp"

#include "../sdk/sdk.hpp"

#include "../utils/debug.hpp"
#include "../utils/vmt/vmt.hpp"

auto hook_objects = std::make_tuple(
	GameOverlayHook{},
	GlowHook{},
	EntitySystemHook{},
	ViewRenderHook{},
	OverrideViewModelHook{},
	ISource2ClientHook{}
);

bool hooks::Initialize() {
	LOG("\n[HOOK] Initialization of hooks.\n");

	if (auto status = MH_Initialize(); status != MH_OK && status != MH_ERROR_ALREADY_INITIALIZED)
		LOG_AND_RETURN("[-] MH Initialize has failed. Status: %d\n", status);

	bool result = std::apply([](auto&&... objects) {
		auto init = [](auto&& object) {
			bool result = object.Initialize();

			if (result)
				LOG("[+] %s initialized successfully.\n", typeid(object).name() + 6);
			else
				LOG("[-] %s failed to initialize hook.\n", typeid(object).name() + 6);

			return result;
		};

		return (init(objects) && ...);
	}, hook_objects);

	return result;
}

bool hooks::Shutdown() {
	LOG("\n[HOOK] Hooks shutdown.\n");
	std::apply([](auto&&... objects) {
		auto init = [](auto&& object) {
			if (!object.IsInitialized()) {
				return true;
			}

			bool result = object.Shutdown();

			if (result)
				LOG("[+] %s shutdown successfully.\n", typeid(object).name() + 6);
			else
				LOG("[-] %s failed to shutdown hook.\n", typeid(object).name() + 6);

			return result;
		};

		((init(objects)), ...);
	}, hook_objects);

	MH_Uninitialize();

	return TRUE;
}