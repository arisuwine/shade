#include "glow.hpp"

#include "minhook.h"

#include "../sdk/interfaces/CGlowProperty.hpp"
#include "../sdk/entities/CCSPlayerPawn.hpp"

#include "../sdk/utils/color.hpp"

#include "../menu/options.hpp"

bool Glow::is_init = false;
bool Glow::initialize() {
	if (is_init)
		return true;

	if (MH_Initialize() != MH_OK)
		return false;

	if (MH_CreateHook((LPVOID)pGetGlow, &GetGlowHk, reinterpret_cast<void**>(&GetGlowO)) != MH_OK)
		return false;

	if (MH_EnableHook((LPVOID)pGetGlow) != MH_OK)
		return false;

	is_init = true;
	return true;
}

bool Glow::shutdown() {
	if (!is_init)
		return true;

	if (MH_DisableHook((LPVOID)pGetGlow) != MH_OK)
		return false;

	is_init = false;
	return true;
}

void __fastcall Glow::GetGlowHk(CGlowProperty* property, int color) {
	if (!g_options.esp_enabled)
		return GetGlowO(property, color);

	if (!(g_CNetworkClientService->m_pCNetworkGameClient->IsInGame()))
		return GetGlowO(property, color);

	if (!g_options.esp_glow)
		return GetGlowO(property, color);

	CCSPlayerPawn* local_player = LocalPlayer::get().get_pawn();
	C_BaseEntity* player = property->m_pParent;

	if (player && property->m_pParent == local_player)
		return GetGlowO(property, color);

	if (g_options.esp_enemies_only && (local_player->m_iTeamNum == player->m_iTeamNum))
		return GetGlowO(property, color);

	int32_t glow_color = (*g_options.col_esp_glow).ByteColorRGBA();
	property->m_bGlowing = true;
	return GetGlowO(property, glow_color);
}
