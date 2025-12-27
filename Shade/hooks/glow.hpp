#pragma once
#include "../sdk/modules.hpp"
#include "../sdk/signatures.hpp"

class CGlowProperty;

class GlowHook {
private:
	using GetGlow	= void (__fastcall*)(CGlowProperty*, int);
	using IsGlowing = bool(__fastcall*)(CGlowProperty*);

	static inline uintptr_t pGetGlow	= modules::client.find(GET_GLOW_COLOR);
	static inline uintptr_t pIsGlowing	= modules::client.find(IS_GLOWING);

	static inline GetGlow	oGetGlow;
	static inline IsGlowing oIsGlowing;

	static void __fastcall GetGlowHk	(CGlowProperty* property, int color);
	static bool __fastcall IsGlowingHk	(CGlowProperty*);

	static bool is_init;

public:
	static bool initialize();
	static bool shutdown();
};