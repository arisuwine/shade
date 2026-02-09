#pragma once
#include "ihook.hpp"

class CGlowProperty;
class ISource2Client;

enum ClientFrameStage_t : int
{
	FRAME_NET_UPDATE_POSTDATAUPDATE_START = 2,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_FULL_FRAME_UPDATE_ON_REMOVE,
	FRAME_RENDER_START,
	FRAME_RENDER_END,
	FRAME_NET_UPDATE_END,
	FRAME_NET_CREATION,
	FRAME_RESTORE_SERVER_STATE,
	FRAME_SIMULATE_END
};

class CISource2ClientHook {
private:
	using FrameStageNotifyFunc = void(__fastcall*)(ISource2Client*, ClientFrameStage_t);
	static inline FrameStageNotifyFunc m_pFrameStageNotifyOrig;

	static void __fastcall hkFrameStageNotify(ISource2Client* client, ClientFrameStage_t curStage);

public:
	static void Register();
};

