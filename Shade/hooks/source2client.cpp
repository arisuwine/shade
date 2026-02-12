#include "source2client.hpp"

#include <stdexcept>

#include "hooks.hpp"

#include "../sdk/sdk.hpp"

void CISource2ClientHook::Register() {
	std::unique_ptr<CVMTHook> hook = std::make_unique<CVMTHook>("CISource2ClientHook", g_Source2Client);

	hooks::AddVMTHook<FrameStageNotifyFunc>(hook.get(), 36, hkFrameStageNotify, &m_pFrameStageNotifyOrig);

	hooks::g_pHooks.push_back(std::move(hook));
}

void __fastcall CISource2ClientHook::hkFrameStageNotify(ISource2Client* client, ClientFrameStage_t curStage) {
	m_pFrameStageNotifyOrig(client, curStage);
}
