#pragma once
#include "../utils/pattern_scan/pattern_scan.hpp"
#include "../utils/singleton.hpp"

#include "../utils/debug.hpp"

namespace modules {
	inline PatternScan overlay_renderer = { "GameOverlayRenderer64.dll" };
	inline PatternScan client = { "client.dll" };
	inline PatternScan engine2 = { "engine2.dll" };
	inline PatternScan schemasystem = { "schemasystem.dll" };
}