#pragma once
#include "../sdk/modules.hpp"
#include "../sdk/signatures.hpp"

#include "../utils/vmt/vmt.hpp"

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

class ISource2ClientHook {
private:
	using FrameStageNotifyFunc = void(__fastcall*)(ISource2Client*, ClientFrameStage_t);

	static vmt::Shadowing* m_Shadowing;

	static inline FrameStageNotifyFunc FrameStageNotifyOrig;
	static void __fastcall hkFrameStageNotify(ISource2Client* client, ClientFrameStage_t curStage);

	static bool m_bIsInit;

public:
	static bool Initialize();
	static bool Shutdown();

	inline bool IsInitialized() { return m_bIsInit; }
};

