#pragma once
#include "../offsets.hpp"

class CModelState {
public:
	SCHEMA(uintptr_t, offsets::client::CModelState::BoneArray, m_BoneArray);
};