#pragma once
#include "../offsets.hpp"

#include "CHandle.hpp"
#include "C_BaseEntity.hpp"

class CEntityIdentity;
class C_CSPlayerPawn;

class CBasePlayerController : public C_BaseEntity {};

class CCSPlayerController : public CBasePlayerController {
public:
	PSCHEMA	(CHandle<C_CSPlayerPawn>,	offsets::client::CCSPlayerController::m_hPawn,					m_hPawn					);
	SCHEMA	(const char*,				offsets::client::CCSPlayerController::m_sSanitizedPlayerName,	m_sSanitizedPlayerName	);
};