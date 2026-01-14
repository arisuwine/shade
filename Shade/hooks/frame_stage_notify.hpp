#pragma once
#include "../sdk/modules.hpp"
#include "../sdk/signatures.hpp"

class CGlowProperty;
class ISource2Client;

class FrameStageNotifyHook {
private:
	using FrameStageNotifyFunc = void(__fastcall*)(ISource2Client*, __int64, char);

	static inline uintptr_t pFrameStageNotify = modules::client.find(FRAME_STAGE_NOTIFY);

	static inline FrameStageNotifyFunc	oFrameStageNotify;

	static void __fastcall FrameStageNotifyHk(ISource2Client* client, __int64 edx, char curStage);

	static bool is_init;

public:
	static bool Initialize();
	static bool Shutdown();
};

