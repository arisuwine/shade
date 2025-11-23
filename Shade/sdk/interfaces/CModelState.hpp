#pragma once
#include "../offsets.hpp"

class CModelState {
public:
	CModelState() = delete;

	inline uintptr_t BoneArray() const {
		return *reinterpret_cast<uintptr_t*>(THIS_ADDR + offsets::CModelState::BoneArray);
	}
};