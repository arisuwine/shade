#pragma once
#include <memory>
#include <string>

#include "../sdk/utils/color.hpp"

#define DEFAULT_COLOR color(255, 255, 255)

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

class options {
public:
	OPTION(bool, show_menu, true);

	// ESP
	OPTION(bool, esp_enabled, true);
	OPTION(bool, esp_enemies_only, true);
	OPTION(bool, esp_bounding_boxes, true);
	OPTION(bool, esp_player_names, true);
	OPTION(bool, esp_player_health, true);
	OPTION(bool, esp_player_skeleton, true);

	float col_esp_bounding_boxes[3];
	float col_esp_player_names[3];
	float col_esp_player_skeleton[3];
};

inline options g_options;