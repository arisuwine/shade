#include "CCSPlayerPawn.hpp"

uintptr_t LocalPlayer::controller = 0;
uintptr_t LocalPlayer::handle = 0;

const char* CCSPlayerPawn::m_sSanitizedPlayerName() const {

	CCSPlayerController* controller = reinterpret_cast<CCSPlayerController*>(CGameEntitySystem::GetControllerByPawn(reinterpret_cast<uintptr_t>(this)));
	return controller->m_sSanitizedPlayerName();
}

int CCSPlayerPawn::m_iHealth() const {
	return get_data<int>(offsets::CCSPlayerPawn::m_iHealth);
}

int CCSPlayerPawn::m_ArmorValue() const {
	return get_data<int>(offsets::CCSPlayerPawn::m_ArmorValue);
}

CCSPlayerPawn::TEAM CCSPlayerPawn::m_iTeamNum() const {
	return get_data<TEAM>(offsets::CCSPlayerPawn::m_iTeamNum);
}

vector_3d CCSPlayerPawn::m_vOldOrigin() const {
	return get_data<vector_3d>(offsets::CCSPlayerPawn::m_vOldOrigin);
}

bool CCSPlayerPawn::m_bIsScoped() const {
	return get_data<bool>(offsets::CCSPlayerPawn::m_bIsScoped);
}

bool CCSPlayerPawn::m_bIsDefusing() const {
	return get_data<bool>(offsets::CCSPlayerPawn::m_bIsDefusing);
}

CCollisionProperty* CCSPlayerPawn::m_pCollision() const {
	return get_data<CCollisionProperty*>(offsets::CCSPlayerPawn::m_pCollision);
}

CPlayer_MovementServices* CCSPlayerPawn::m_pMovementServices() const {
	return get_data<CPlayer_MovementServices*>(offsets::CCSPlayerPawn::m_pMovementServices);
}

CGameSceneNode* CCSPlayerPawn::m_pGameSceneNode() const {
	return get_data<CGameSceneNode*>(offsets::CCSPlayerPawn::m_pGameSceneNode);
}