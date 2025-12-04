#pragma once

// client.dll
#define VIEW_MATRIX				"48 8D 0D ? ? ? ? 48 89 44 24 ? 48 89 4C 24 ? 4C 8D 0D"
#define GAME_ENTITY_SYSTEM		"48 8B 0D ? ? ? ?? E8 ? ? ? ? 48 8B E8"
#define LOCAL_PLAYER_CONTROLLER "48 8B 15 ? ? ? ? 48 85 D2 74 ? 8B 92"
#define GLOW_MANAGER			"4C 8B 05 ? ? ? ? 49 63 48 ? 85 C9 7E ? 49 8B 40 ? ? ? ? 74"
#define GET_GLOW_COLOR			"40 53 48 83 EC ? 48 8B D9 48 83 C1 ? ? ? 74 ? ? ? E8"
#define SET_GLOWING				"48 81 C1 ? ? ? ? 0F 57 D2 BA"

// GameOverlayRenderer64.dll
#define CREATE_HOOK				"48 89 5C 24 ? 57 48 83 EC ? 33 C0"
#define HK_PRESENT				"48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 54 41 56 41 57 48 83 EC ? 41 8B E8"
#define UN_HOOK					"48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 0F B6 DA"

// engine2.dll
#define NETWORK_CLIENT_SERVICE	"48 8D 35 ? ? ? ? 4C 89 65"