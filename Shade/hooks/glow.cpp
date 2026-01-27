#include "glow.hpp"

#include "minhook.h"

#include "entity_system.hpp"

#include "../sdk/entities/C_CSPlayerPawn.hpp"

#include "../sdk/services/CGlowProperty.hpp"

#include "../sdk/utils/color.hpp"

#include "../menu/options.hpp"

#include "../utils/debug.hpp"

bool GlowHook::m_bIsInit = false;

bool GlowHook::Initialize() {
	if (m_bIsInit)
		return TRUE;

	if (MH_CreateHook((LPVOID)pApplyGlow, &hkApplyGlow, reinterpret_cast<void**>(&ApplyGlowOrig)) != MH_OK)
		LOG_AND_RETURN("[-] hkApplyGlow hook creation has failed.\n");

	if (MH_CreateHook((LPVOID)pIsGlowing, &hkIsGlowing, reinterpret_cast<void**>(&IsGlowingOrig)) != MH_OK)
		LOG_AND_RETURN("[-] hkIsGlowing hook creation has failed.\n");

	if (MH_EnableHook((LPVOID)pApplyGlow) != MH_OK)
		LOG_AND_RETURN("[-] pApplyGlow hook enabling has failed.\n");

	if (MH_EnableHook((LPVOID)pIsGlowing) != MH_OK)
		LOG_AND_RETURN("[-] pIsGlowing hook enabling has failed.\n");

	m_bIsInit = TRUE;
	return TRUE;
}

bool GlowHook::Shutdown() {
	if (!m_bIsInit)
		return TRUE;

	if (MH_DisableHook((LPVOID)pApplyGlow) != MH_OK)
		LOG_AND_RETURN("[-] pApplyGlow hook disabling has failed.\n");

	if (MH_DisableHook((LPVOID)pIsGlowing) != MH_OK)
		LOG_AND_RETURN("[-] pIsGlowing hook disabling has failed.\n");

	m_bIsInit = FALSE;
	return TRUE;
}

bool __fastcall GlowHook::hkIsGlowing(CGlowProperty* property) {
	if (!(g_CNetworkClientService->m_pCNetworkGameClient->IsInGame()))
		return IsGlowingOrig(property);

	C_BaseEntity* entity = property->m_pParent;
	if (entity == nullptr)
		return IsGlowingOrig(property);

	if (entity->IsWeapon() && !entity->m_hOwnerEntity.IsValid())
		return true;

	if (entity->Schema_DynamicBinding() != g_CSchemaSystem->FindClassByScopedName("client.dll!C_CSPlayerPawn"))
		return IsGlowingOrig(property);

	return true;
}

void __fastcall GlowHook::hkApplyGlow(CGlowProperty* property, CGlowObject* object) {
	ApplyGlowOrig(property, object);

	if (!g_CNetworkClientService->m_pCNetworkGameClient->IsInGame())
		return;

	if (!g_Options.esp_enabled || !g_Options.esp_glow)
		return;

	C_BaseEntity* entity = property->m_pParent;
	if (!entity)
		return;

	Color& color = (*g_Options.col_esp_glow);
	if (entity->IsWeapon() && !entity->m_hOwnerEntity.IsValid()) {
		object->SetColor(color.r(), color.g(), color.b(), color.a() / 100.0f);
		return;
	}
	
	if (!entity->IsPawn())
		return;

	LocalPlayer::Get().Update();
	C_CSPlayerPawn* local_player = LocalPlayer::Get().GetPawn();
	if (!local_player || !LocalPlayer::Get().IsValid())
		return;

	if (entity == local_player)
		return;

	if (g_Options.esp_enemies_only && (local_player->m_iTeamNum == entity->m_iTeamNum))
		return;

	object->SetColor(color.r(), color.g(), color.b(), color.a() / 100.0f);
}
