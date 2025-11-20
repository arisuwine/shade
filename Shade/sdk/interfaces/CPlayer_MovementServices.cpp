#include "CPlayer_MovementServices.hpp"

inline float CPlayer_MovementServices::m_flDuckAmount() const {
	return *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + offsets::CPlayer_MovementServices::m_flDuckAmount);
}