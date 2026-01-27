#pragma once
#include "../utils/pattern_scan/pattern_scan.hpp"

namespace modules {
	inline PatternScan overlay_renderer			= GetModuleHandleA("GameOverlayRenderer64.dll");
	inline PatternScan client					= GetModuleHandleA("client.dll");
	inline PatternScan engine2					= GetModuleHandleA("engine2.dll");
	inline PatternScan schemasystem				= GetModuleHandleA("schemasystem.dll");
}