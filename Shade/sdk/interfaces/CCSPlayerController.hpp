#pragma once
#include "../utils/CUtlString.hpp"
#include "../offsets.hpp"

class CCSPlayerController {
public:
	const char* m_sSanitizedPlayerName() const {
		return *reinterpret_cast<const char**>(reinterpret_cast<uintptr_t>(this) + offsets::CCSPlayerController::m_sSanitizedPlayerName);
	}
};