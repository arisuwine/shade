#include "source2client.hpp"

#include "minhook.h"

#include "../utils/debug.hpp"

#include "../render/render.hpp"

#include "../features/esp.hpp"

#include "../sdk/sdk.hpp"

vmt::Shadowing* ISource2ClientHook::m_Shadowing = nullptr;
bool			ISource2ClientHook::m_bIsInit	= FALSE;

bool ISource2ClientHook::Initialize() {
	if (m_bIsInit)
		return TRUE;

	m_Shadowing = new vmt::Shadowing(g_Source2Client);
	if (!m_Shadowing->IsInitialized())
		LOG_AND_RETURN("[-] vmt Shadowing has failed at ISource2ClientHook.\n");

	FrameStageNotifyOrig = m_Shadowing->Hook<FrameStageNotifyFunc>(36, hkFrameStageNotify);
	if (!FrameStageNotifyOrig)
		LOG_AND_RETURN("[-] vmt Hooking has failed at ISource2ClientHook.\n");

	m_bIsInit = TRUE;
	return TRUE;
}

bool ISource2ClientHook::Shutdown() {
	if (!m_bIsInit)
		return TRUE;

	m_Shadowing->Shutdown();

	m_bIsInit = FALSE;
	return TRUE;
}

void __fastcall ISource2ClientHook::hkFrameStageNotify(ISource2Client* client, ClientFrameStage_t curStage) {
	FrameStageNotifyOrig(client, curStage);
}
