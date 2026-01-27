#pragma once
#include <cstdint>
#include <string_view>

using hash_t = uint32_t;

namespace hash {
	constexpr hash_t basis = 0x811C9DC5;
	constexpr hash_t prime = 0x01000193;

	constexpr hash_t Set(const char* str, hash_t last_hash = basis) {
		return *str ? Set(str + 1, (last_hash ^ static_cast<hash_t>(*str)) * prime) : last_hash;
	}

	inline hash_t Get(const std::string_view& str) {
		hash_t hash = basis;

		for (char c : str) {
			hash ^= static_cast<hash_t>(c);
			hash *= prime;
		}

		return hash;
	}
}