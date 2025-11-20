#pragma once
#include "../offsets.hpp"

class CPlayer_MovementServices {
public:
	inline float m_flDuckAmount() const {
		return *reinterpret_cast<float*>(THIS_ADDR + offsets::CPlayer_MovementServices::m_flDuckAmount);
	}
};