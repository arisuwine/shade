#pragma once
#include "../offsets.hpp"

#include "CHandle.hpp"

class CEntityIdentity;
class C_CSPlayerPawn;

class C_CSPlayerController {
public:
	C_CSPlayerController() = delete;

	PSCHEMA	(CHandle<C_CSPlayerPawn>,	offsets::client::C_CSPlayerController::m_hPawn,					m_hPawn					);
	SCHEMA	(const char*,				offsets::client::C_CSPlayerController::m_sSanitizedPlayerName,	m_sSanitizedPlayerName	);
	SCHEMA	(CEntityIdentity*,			offsets::client::C_CSPlayerController::m_pEntity,				m_pEntity				);
};