#include "frame_stage_notify.hpp"

#include "minhook.h"

#include "../utils/debug.hpp"

#include "../render/render.hpp"

bool FrameStageNotifyHook::is_init = false;
bool FrameStageNotifyHook::Initialize() {
	if (is_init)
		return TRUE;

	if (MH_CreateHook((LPVOID)pFrameStageNotify, &FrameStageNotifyHk, reinterpret_cast<void**>(&oFrameStageNotify)) != MH_OK)
		LOG_AND_RETURN("[-] FrameStageNotifyHk hook creation has failed.\n");

	if (MH_EnableHook((LPVOID)pFrameStageNotify) != MH_OK)
		LOG_AND_RETURN("[-] pFrameStageNotify hook enabling has failed.\n");

	is_init = TRUE;
	return TRUE;
}

bool FrameStageNotifyHook::Shutdown() {
	if (!is_init)
		return TRUE;

	if (MH_DisableHook((LPVOID)pFrameStageNotify) != MH_OK)
		LOG_AND_RETURN("[-] pFrameStageNotify hook disabling has failed.\n");

	is_init = FALSE;
	return TRUE;
}

void __fastcall FrameStageNotifyHook::FrameStageNotifyHk(ISource2Client* client, __int64 edx, char curStage) {
	RenderTarget::Get().BeginScene();
	oFrameStageNotify(client, edx, curStage);
}
