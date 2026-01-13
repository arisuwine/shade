#pragma once
#include "../offsets.hpp"

class CPlayer_MovementServices {
public:
	CPlayer_MovementServices() = delete;

	SCHEMA(float, offsets::client::CPlayer_MovementServices::m_flDuckAmount, m_flDuckAmount);
};