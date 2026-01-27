#pragma once
#include "../sdk/modules.hpp"
#include "../sdk/signatures.hpp"

class CGlowProperty;

class CGlowObject {
public:
	float red, green, blue, alpha;
	void SetColor(int r, int g, int b, float a) {
		red = r / 255.f;
		green = g / 255.f;
		blue = b / 255.f;
		alpha = a;
	}
};

class GlowHook {
private:
	using ApplyGlow	= void (__fastcall*)(CGlowProperty*, CGlowObject*);
	using IsGlowing = bool(__fastcall*)(CGlowProperty*);

	static inline uintptr_t pApplyGlow	= modules::client.Find(APPLY_GLOW);
	static inline uintptr_t pIsGlowing	= modules::client.Find(IS_GLOWING);

	static inline ApplyGlow	ApplyGlowOrig;
	static inline IsGlowing IsGlowingOrig;

	static void __fastcall hkApplyGlow	(CGlowProperty* property, CGlowObject* object);
	static bool __fastcall hkIsGlowing	(CGlowProperty*);

	static bool m_bIsInit;

public:
	static bool Initialize();
	static bool Shutdown();

	inline bool IsInitialized() { return m_bIsInit; }
};