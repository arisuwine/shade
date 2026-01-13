#include "glow.hpp"

#include "minhook.h"

#include "entity_system.hpp"

#include "../sdk/entities/C_CSPlayerPawn.hpp"

#include "../sdk/services/CGlowProperty.hpp"

#include "../sdk/utils/color.hpp"

#include "../menu/options.hpp"

#include "../utils/debug.hpp"

bool GlowHook::is_init = false;
bool GlowHook::Initialize() {
	if (is_init)
		return TRUE;

	if (MH_CreateHook((LPVOID)pGetGlow, &GetGlowHk, reinterpret_cast<void**>(&oGetGlow)) != MH_OK)
		LOG_AND_RETURN("[-] GetGlowHk hook creation has failed.\n");

	if (MH_CreateHook((LPVOID)pIsGlowing, &IsGlowingHk, reinterpret_cast<void**>(&oIsGlowing)) != MH_OK)
		LOG_AND_RETURN("[-] IsGlowingHk hook creation has failed.\n");

	if (MH_EnableHook((LPVOID)pGetGlow) != MH_OK)
		LOG_AND_RETURN("[-] pGetGlow hook enabling has failed.\n");

	if (MH_EnableHook((LPVOID)pIsGlowing) != MH_OK)
		LOG_AND_RETURN("[-] pIsGlowing hook enabling has failed.\n");

	is_init = TRUE;
	return TRUE;
}

bool GlowHook::Shutdown() {
	if (!is_init)
		return TRUE;

	if (MH_DisableHook((LPVOID)pGetGlow) != MH_OK)
		LOG_AND_RETURN("[-] pGetGlow hook disabling has failed.\n");

	if (MH_DisableHook((LPVOID)pIsGlowing) != MH_OK)
		LOG_AND_RETURN("[-] pIsGlowing hook disabling has failed.\n");

	is_init = FALSE;
	return TRUE;
}

bool __fastcall GlowHook::IsGlowingHk(CGlowProperty* property) {
	if (!(g_CNetworkClientService->m_pCNetworkGameClient->IsInGame()))
		return oIsGlowing(property);

	C_BaseEntity* entity = property->m_pParent;
	if (entity == nullptr)
		return oIsGlowing(property);

	if (entity->IsWeapon() && entity->m_hOwnerEntity.m_Index == -1)
		return true;

	if (entity->Schema_DynamicBinding() != g_CSchemaSystem->FindClassByScopedName("client.dll!C_CSPlayerPawn"))
		return oIsGlowing(property);

	return true;
}

void __fastcall GlowHook::GetGlowHk(CGlowProperty* property, int color) {
	if (!g_CNetworkClientService->m_pCNetworkGameClient->IsInGame())
		return oGetGlow(property, color);

	if (!g_options.esp_enabled || !g_options.esp_glow)
		return oGetGlow(property, color);

	C_BaseEntity* entity = property->m_pParent;
	if (!entity)
		return oGetGlow(property, color);

	int32_t glow_color = (*g_options.col_esp_glow).GetRawColor();
	if (entity->IsWeapon())
		return oGetGlow(property, glow_color);
	
	if (entity->IsPawn())
		return oGetGlow(property, color);

	C_CSPlayerPawn* local_player = LocalPlayer::Get().GetPawn();
	if (!local_player)
		return oGetGlow(property, color);

	if (entity == local_player)
		return oGetGlow(property, color);

	if (g_options.esp_enemies_only && (local_player->m_iTeamNum == entity->m_iTeamNum))
		return oGetGlow(property, color);

	return oGetGlow(property, glow_color);
}
