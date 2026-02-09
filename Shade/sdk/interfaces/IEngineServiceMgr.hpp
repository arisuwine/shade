#pragma once
#include "../../utils/vmt/vmt.hpp"

class CSwapChainDx11;

class IEngineServiceMgr {
public:
	auto GetEngineDeviceInfo() {
		return CALL_VIRTUAL(this, __int64, 21);
	}

	CSwapChainDx11* GetEngineSwapChain() {
		return reinterpret_cast<CSwapChainDx11*>(GetEngineDeviceInfo() - 0x18);
	}
};