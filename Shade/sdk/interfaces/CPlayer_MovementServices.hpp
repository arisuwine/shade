#pragma once
#include "../offsets.hpp"

class CPlayer_MovementServices {
public:
	CPlayer_MovementServices() = delete;

	SCHEMA(float, offsets::CPlayer_MovementServices::m_flDuckAmount, m_flDuckAmount);
};