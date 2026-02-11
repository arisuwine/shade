#pragma once

// client.dll
#define FOV_CS_DEBUG			"40 53 48 83 EC ? 48 8B D9 E8 ? ? ? ? 48 85 C0 74 ? 48 8B C8 48 83 C4" // xref: fov_cs_debug
#define VIEW_MATRIX				"48 8D 0D ? ? ? ? 48 89 44 24 ? 48 89 4C 24 ? 4C 8D 0D"
#define VIEW_RENDER				"48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 48 83 C4 ? E9 ? ? ? ? 48 8D 0D ? ? ? ? E9 ? ? ? ? ? ? ? ? 48 83 EC ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 48 83 C4 ? E9 ? ? ? ? 4C 8B DC"
#define ON_RENDER_START			"48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 81 EC ? ? ? ? 4C 8B F1 48 8D 94 24"
#define SETUP_VIEWMODEL			"40 55 53 56 41 56 41 57 48 8B EC 48 83"
#define LOCAL_PLAYER_CONTROLLER "48 8B 15 ? ? ? ? 48 85 D2 74 ? 8B 92"
#define GLOW_MANAGER			"4C 8B 05 ? ? ? ? 49 63 48 ? 85 C9 7E ? 49 8B 40 ? ? ? ? 74"
#define GET_GLOW_COLOR			"40 53 48 83 EC ? 48 8B D9 48 83 C1 ? ? ? 74 ? ? ? E8"
#define APPLY_GLOW				"E8 ? ? ? ? F3 0F 10 BE ? ? ? ? 48 8B CF"
#define IS_GLOWING				"E8 ? ? ? ? 33 DB 84 C0 0F 84 ? ? ? ? 48 8B 4F"
#define ON_ADD_ENTITY			"48 89 74 24 ? 57 48 83 EC ? 41 B9 ? ? ? ? 41 8B C0 41 23 C1 48 8B F2 41 83 F8 ? 48 8B F9 44 0F 45 C8 41 81 F9 ? ? ? ? 73 ? FF 81"
#define ON_REMOVE_ENTITY		"48 89 74 24 ? 57 48 83 EC ? 41 B9 ? ? ? ? 41 8B C0 41 23 C1 48 8B F2 41 83 F8 ? 48 8B F9 44 0F 45 C8 41 81 F9 ? ? ? ? 73 ? FF 89"
#define GP_GLOBALS				"48 8B 05 ? ? ? ? 8B 48 ? FF C1"

// GameOverlayRenderer64.dll
#define CREATE_HOOK				"48 89 5C 24 ? 57 48 83 EC ? 33 C0"
#define HK_PRESENT				"48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 54 41 56 41 57 48 83 EC ? 41 8B E8"
#define UN_HOOK					"48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 0F B6 DA"

// engine2.dll
#define NETWORK_CLIENT_SERVICE	"48 8D 35 ? ? ? ? 4C 89 65"

// schemasystem.dll
#define SCHEMA_SYSTEM			"48 89 05 ? ? ? ? 4C 8D 0D ? ? ? ? 0F B6 45 ? 4C 8D 45 ? 33 F6"