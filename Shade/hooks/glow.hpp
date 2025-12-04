#pragma once
#include "../sdk/modules.hpp"
#include "../sdk/signatures.hpp"

class CGlowProperty;

class Glow {
private:
	using GetGlow = void (__fastcall*)(CGlowProperty*, int);

	static inline uintptr_t pGetGlow = modules::client.find(GET_GLOW_COLOR);

	static inline GetGlow GetGlowO;
	static void __fastcall GetGlowHk(CGlowProperty* property, int color);
	static bool is_init;

public:
	static bool initialize();
	static bool shutdown();
};