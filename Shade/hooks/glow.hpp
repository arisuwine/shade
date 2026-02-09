#pragma once

class CGlowProperty;
class CGlowObject;

class CIsGlowingHook {
private:
	using IsGlowingFunc = bool(__fastcall*)(CGlowProperty*);
	static inline IsGlowingFunc m_pIsGlowingOrig;

	static bool __fastcall hkIsGlowing(CGlowProperty* property);

public:
	static void Register();
};

class CApplyGlowHook {
private:
	using ApplyGlowFunc	= void (__fastcall*)(CGlowProperty*, CGlowObject*);
	static inline ApplyGlowFunc m_pApplyGlowOrig;

	static void __fastcall hkApplyGlow(CGlowProperty* property, CGlowObject* object);

public:
	static void Register();
};