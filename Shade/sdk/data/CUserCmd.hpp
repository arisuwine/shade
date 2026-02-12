#pragma once
#include <cstdint>

#include "../offsets.hpp"

enum ECommandButtons : uint64_t
{
	IN_ATTACK = 1 << 0,
	IN_JUMP = 1 << 1,
	IN_DUCK = 1 << 2,
	IN_FORWARD = 1 << 3,
	IN_BACK = 1 << 4,
	IN_USE = 1 << 5,
	IN_LEFT = 1 << 7,
	IN_RIGHT = 1 << 8,
	IN_MOVELEFT = 1 << 9,
	IN_MOVERIGHT = 1 << 10,
	IN_SECOND_ATTACK = 1 << 11,
	IN_RELOAD = 1 << 13,
	IN_SPRINT = 1 << 16,
	IN_JOYAUTOSPRINT = 1 << 17,
	IN_SHOWSCORES = 1ULL << 33,
	IN_ZOOM = 1ULL << 34,
	IN_LOOKATWEAPON = 1ULL << 35
};

class CInButtonState {
public:
	SCHEMA(uint64_t, offsets::client::CInButtonState::m_nValue,			m_nValue		);
	SCHEMA(uint64_t, offsets::client::CInButtonState::m_nValueChanged,	m_nValueChanged	);
	SCHEMA(uint64_t, offsets::client::CInButtonState::m_nValueScroll,	m_nValueScroll	);
};

class CUserCmd {
public:
	PSCHEMA(CInButtonState, offsets::client::CUserCmd::m_nButtons,		m_nButtons		);
};