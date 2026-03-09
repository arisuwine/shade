#pragma once
#include "../offsets.hpp"

class CModelState {
public:
	SCHEMA(uintptr_t, 0x80, m_BoneArray);
};