#pragma once
#include "../utils/CUtlString.hpp"
#include "../offsets.hpp"

class CEntityIdentity;

class CCSPlayerController {
public:
	CCSPlayerController() = delete;

	const char* m_sSanitizedPlayerName() const {
		return *reinterpret_cast<const char**>(THIS_ADDR + offsets::CCSPlayerController::m_sSanitizedPlayerName);
	}

	CEntityIdentity* m_pEntity() const {
		return *reinterpret_cast<CEntityIdentity**>(THIS_ADDR + offsets::CCSPlayerController::m_pEntity);
	}
};