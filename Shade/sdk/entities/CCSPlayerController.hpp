#pragma once
#include "../offsets.hpp"

#include "../interfaces/CHandle.hpp"

class CEntityIdentity;
class CCSPlayerPawn;

class CCSPlayerController {
public:
	CCSPlayerController() = delete;

	SCHEMA_R(CHandle<CCSPlayerPawn>,	offsets::CCSPlayerController::m_hPawn,					m_hPawn					);
	SCHEMA	(const char*,				offsets::CCSPlayerController::m_sSanitizedPlayerName,	m_sSanitizedPlayerName	);
	SCHEMA	(CEntityIdentity*,			offsets::CCSPlayerController::m_pEntity,				m_pEntity				);
};