#pragma once
#include "../offsets.hpp"

class CModelState {
public:
	CModelState() = delete;

	SCHEMA(uintptr_t, offsets::CModelState::BoneArray, BoneArray);
};