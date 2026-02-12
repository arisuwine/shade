#include "ccsgoinput.hpp"

#include <stdexcept>

#include "hooks.hpp"

#include "../sdk/sdk.hpp"

#include "../sdk/entities/C_CSPlayerPawn.hpp"

#include "../sdk/data/CUserCmd.hpp"

#include "../menu/options.hpp"

#include "../features/movement.hpp"

void CCSGOInputHook::Register() {
	std::unique_ptr<CVMTHook> hook = std::make_unique<CVMTHook>("CCSGOInputHook", g_CCSGOInput);

	hooks::AddVMTHook(hook.get(), 22, hkCreateMove, &m_pCreateMoveOrig);

	lg::Success("[+]", "Hook %s initialized successfully.\n", hook->GetName().data());

	hooks::g_pHooks.push_back(std::move(hook));
}

double __fastcall CCSGOInputHook::hkCreateMove(CCSGOInput* input, unsigned int slot, CUserCmd* pCmd) {
	auto result = m_pCreateMoveOrig(input, slot, pCmd);
	if (g_Unload)
		return result;

	C_CSPlayerPawn* pLocalPlayer = LocalPlayer::Get().GetPawn();

	Movement::OnMove(pCmd, pLocalPlayer);

	return result;
}