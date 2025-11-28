#pragma once
#include "../utils/pattern_scan/pattern_scan.hpp"

namespace modules {
	inline pattern_scan overlay_renderer		= GetModuleHandleA("GameOverlayRenderer64.dll");
	inline pattern_scan client					= GetModuleHandleA("client.dll");
	inline pattern_scan engine2					= GetModuleHandleA("engine2.dll");
}