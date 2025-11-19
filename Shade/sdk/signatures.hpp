#pragma once

// client.dll
#define VIEW_MATRIX				"48 8D 0D ? ? ? ? 48 89 44 24 ? 48 89 4C 24 ? 4C 8D 0D"
#define GAME_ENTITY_SYSTEM		"48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B E8"
#define LOCAL_PLAYER_CONTROLLER "48 8B 15 ? ? ? ? 48 85 D2 74 ? 8B 92"

// GameOverlayRenderer64.dll
#define CREATE_HOOK				"48 89 5C 24 ? 57 48 83 EC ? 33 C0"
#define HK_PRESENT				"48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 54 41 56 41 57 48 83 EC ? 41 8B E8"
#define UN_HOOK					"48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 0F B6 DA"