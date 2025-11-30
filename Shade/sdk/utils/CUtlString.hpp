#pragma once

struct CUtlString {
	char* string;
	
	char* operator*() const {
		if (is_zero())
			return nullptr;

		return string;
	}

	inline bool is_zero() const {
		return string != nullptr;
	}
};