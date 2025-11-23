#pragma once
#include <memory>
#include <string>

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
	// ESP
	OPTION(bool, esp_enabled, true);
	OPTION(bool, esp_enemies_only, true);
	OPTION(bool, esp_bouding_boxes, true);
	OPTION(bool, esp_player_names, true);
	OPTION(bool, esp_player_health, true);
	OPTION(bool, esp_player_skeleton, true);
};

inline options g_options;