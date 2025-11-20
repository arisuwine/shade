#pragma once
#include "../offsets.hpp"

class CModelState {
public:
	inline uintptr_t BoneArray() const {
		return *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(this) + offsets::CModelState::BoneArray);
	}
};