#include "source2client.hpp"

#include <stdexcept>

#include "hooks.hpp"

#include "../sdk/sdk.hpp"

void CISource2ClientHook::Register() {
	std::unique_ptr<CVMTHook> hook = std::make_unique<CVMTHook>("CISource2ClientHook", g_Source2Client);

	m_pFrameStageNotifyOrig = hook->Enable<FrameStageNotifyFunc>(36, hkFrameStageNotify);
	if (!m_pFrameStageNotifyOrig)
		throw std::runtime_error("failed to enable FrameStageNotify hook");

	hooks::g_pHooks.push_back(std::move(hook));
}

void __fastcall CISource2ClientHook::hkFrameStageNotify(ISource2Client* client, ClientFrameStage_t curStage) {
	m_pFrameStageNotifyOrig(client, curStage);
}
