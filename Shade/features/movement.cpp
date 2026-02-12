#include "movement.hpp"

#include "../sdk/data/CUserCmd.hpp"

#include "../sdk/entities/C_CSPlayerPawn.hpp"

#include "../menu/options.hpp"

void Movement::Bhop(CUserCmd* pCmd, C_CSPlayerPawn* pPawn) {
	if (!g_Options->misc_bhop)
		return;

	if (pCmd->m_nButtons.m_nValue & ECommandButtons::IN_JUMP)
		if (pPawn->m_fFlags & FL_ONGROUND)
			pCmd->m_nButtons.m_nValue &= ~ECommandButtons::IN_JUMP;
}

void Movement::AutoStrafe(CUserCmd* pCmd, C_CSPlayerPawn* pPawn) {
	if (!g_Options->misc_autostrafe)
		return;
}

void Movement::OnMove(CUserCmd* pCmd, C_CSPlayerPawn* pPawn) {
	if (!pPawn || !pPawn->IsAlive())
		return;

	Bhop(pCmd, pPawn);
	AutoStrafe(pCmd, pPawn);
}