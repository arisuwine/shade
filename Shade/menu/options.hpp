#pragma once
#include <memory>
#include <string>

#include "../sdk/utils/color.hpp"

#define DEFAULT_COLOR Color(255, 255, 255, 255)

#define STRINGIFY(s) #s
#define OPTION(type, var, val) Var<type> var = { STRINGIFY(var), val }

template <typename T = bool>
struct Var {
public:
	std::string name;
	std::shared_ptr<T> value;
	int32_t size;

	Var(std::string name, T v) : name(name) {
		value = std::make_shared<T>(v);
		size = sizeof(T);
	}

	operator T() { return *value; }
	operator T* () { return &*value; }
	operator T() const { return *value; }
};

class COptions {
public:
	// ESP
	OPTION(bool, esp_enabled,				true);
	OPTION(bool, esp_enemies_only,			true);
	OPTION(bool, esp_bounding_boxes,		true);
	OPTION(bool, esp_player_names,			true);
	OPTION(bool, esp_player_health,			true);
	OPTION(bool, esp_player_skeleton,		true);
	OPTION(bool, esp_player_weapon,			true);
	OPTION(bool, esp_weapon_ammo,			true);
	OPTION(bool, esp_glow,					true);
	OPTION(bool, esp_dropped_items,			true);
	OPTION(bool, esp_attachments,			true);
	OPTION(bool, esp_projectiles,			true);

	OPTION(Color, col_esp_bounding_boxes,	DEFAULT_COLOR);
	OPTION(Color, col_esp_weapon_ammo,		DEFAULT_COLOR);
	OPTION(Color, col_esp_player_skeleton,	DEFAULT_COLOR);
	OPTION(Color, col_esp_glow,				DEFAULT_COLOR);
	OPTION(Color, col_esp_dropped_items,	DEFAULT_COLOR);

	// MISC
	OPTION(float, misc_aspect_ratio,		100.0f);
	OPTION(float, misc_viewmodel_fov,		68.0f);
	OPTION(float, misc_fov,					80.0f);
};

inline std::unique_ptr<COptions> g_Options = std::make_unique<COptions>();