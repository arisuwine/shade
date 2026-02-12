#pragma once

class CCSGOInput;
class CUserCmd;

class CCSGOInputHook {
private:
	// 22

	using CreateMoveFunc = double(__fastcall*)(CCSGOInput*, unsigned int, CUserCmd*);

	static inline CreateMoveFunc m_pCreateMoveOrig;

	static double __fastcall hkCreateMove(CCSGOInput* input, unsigned int slot, CUserCmd* pCmd);

public:
	static void Register();
};