#include "pattern_scan.hpp"

#include <psapi.h>

#include "../debug.hpp"

void pattern_scan::parse_pattern(const std::string_view& pattern) {
	bytes.clear();
	mask.clear();
	size_t length = pattern.size();

	for (size_t i = 0; i < length; ) {
		if (pattern[i] == ' ') {
			++i;
			continue;
		}
		else if (pattern[i] == '?') {
			bytes.push_back(0);
			mask += '?';

			if (i + 1 < length && pattern[i + 1] == '?')
				++i;
			++i;
		}
		else if (isxdigit(pattern[i])) {
			char byte_str[3] = { 0 };
			byte_str[0] = pattern[i];

			if (i + 1 < length && isxdigit(pattern[i + 1])) {
				byte_str[1] = pattern[i + 1];
				++i;
			}

			++i;
			bytes.push_back(static_cast<BYTE>(strtoul(byte_str, nullptr, 16)));
			mask += 'x';
		}
		else
			++i;
	}
}

pattern_scan::pattern_scan(const std::string_view& module_name) {
	HMODULE hModule;
	if (!(hModule = GetModuleHandleA(module_name.data()))) {
		LOG("[PATTERN SCAN] Module Name is invalid argument\n");
		return;
	}

	MODULEINFO info = { 0 };
	if (!GetModuleInformation(GetCurrentProcess(), hModule, &info, sizeof(MODULEINFO))) {
		LOG("[PATTERN SCAN] Failed to get module information: %d\n", GetLastError());
		return;
	}

	base_address = reinterpret_cast<uintptr_t>(info.lpBaseOfDll);
	module_size = info.SizeOfImage;
}

pattern_scan::pattern_scan(HMODULE hModule) {
	if (!hModule) {
		LOG("[PATTERN SCAN] HMODULE is invalid argument\n");
		return;
	}

	MODULEINFO info = { 0 };
	if (!GetModuleInformation(GetCurrentProcess(), hModule, &info, sizeof(MODULEINFO))) {
		LOG("[PATTERN SCAN] Failed to get module information: %d\n", GetLastError());
		return;
	}

	base_address = reinterpret_cast<uintptr_t>(info.lpBaseOfDll);
	module_size = info.SizeOfImage;
}

uintptr_t pattern_scan::find(const std::string_view& pattern) {
	parse_pattern(pattern);

	uint8_t* base_first_byte = reinterpret_cast<uint8_t*>(base_address);

	for (size_t i = 0; i < module_size - mask.size(); ++i) {
		bool found = true;
		for (size_t j = 0; j < mask.size(); ++j) {
			if (mask[j] == 'x' && base_first_byte[i + j] != bytes[j]) {
				found = false;
				break;
			}
		}

		if (found) {
			return reinterpret_cast<uintptr_t>(base_first_byte + i);
		}
	}

	return NULL;
}