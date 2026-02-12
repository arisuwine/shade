#pragma once

class CUserCmd;
class C_CSPlayerPawn;

class Movement {
private:
	static void Bhop(CUserCmd* pCmd, C_CSPlayerPawn* pPawn);
	static void AutoStrafe(CUserCmd* pCmd, C_CSPlayerPawn* pPawn);

public:
	static void OnMove(CUserCmd* pCmd, C_CSPlayerPawn* pPawn);
};