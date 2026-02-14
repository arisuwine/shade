#include "glow.hpp"

#include "hooks.hpp"

#include "../sdk/modules.hpp"
#include "../sdk/signatures.hpp"

#include "../sdk/entities/C_CSPlayerPawn.hpp"

#include "../sdk/services/CGlowProperty.hpp"
#include "../sdk/services/CGlowObject.hpp"

#include "../sdk/utils/color.hpp"

#include "../menu/options.hpp"

void CIsGlowingHook::Register() {
	uintptr_t pIsGlowing = modules::client.Find(IS_GLOWING);
	hooks::AddDetour<IsGlowingFunc>("CIsGlowingHook", RESOLVE_RIP_EX(void, pIsGlowing, 1, 5), hkIsGlowing, &m_pIsGlowingOrig);
}

void CApplyGlowHook::Register() {
	uintptr_t pApplyGlow = modules::client.Find(APPLY_GLOW);
	hooks::AddDetour<ApplyGlowFunc>("CApplyGlowHook", RESOLVE_RIP_EX(void, pApplyGlow, 1, 5), hkApplyGlow, &m_pApplyGlowOrig);
}

bool __fastcall CIsGlowingHook::hkIsGlowing(CGlowProperty* property) {
	if (!(g_CNetworkClientService->m_pCNetworkGameClient->IsInGame()))
		return m_pIsGlowingOrig(property);

	C_BaseEntity* entity = property->m_pParent;
	if (!entity)
		return m_pIsGlowingOrig(property);

	if (entity->IsWeapon() && !entity->m_hOwnerEntity.IsValid())
		return true;

	if (entity->Schema_DynamicBinding() != g_CSchemaSystem->FindClassByScopedName("client.dll!C_CSPlayerPawn"))
		return m_pIsGlowingOrig(property);

	return true;
}

void __fastcall CApplyGlowHook::hkApplyGlow(CGlowProperty* property, CGlowObject* object) {
	//lg::Info("[SWAPCHAIN]", "%p\n", g_SwapChain);
	//lg::Info("[SWAPCHAIN]", "%p\n", g_EngineServiceMgr->GetEngineSwapChain());

	m_pApplyGlowOrig(property, object);

	if (!g_CNetworkClientService->m_pCNetworkGameClient->IsInGame())
		return;

	if (!g_Options->esp_enabled || !g_Options->esp_glow)
		return;

	C_BaseEntity* entity = property->m_pParent;
	if (!entity)
		return;

	Color& color = (*g_Options->col_esp_glow);
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

	if (g_Options->esp_enemies_only && (local_player->m_iTeamNum == entity->m_iTeamNum))
		return;

	object->SetColor(color.r(), color.g(), color.b(), color.a() / 100.0f);
}