#include "pattern_scan.hpp"

#include <psapi.h>

#include "../debug.hpp"

void PatternScan::ParsePattern(const std::string_view& pattern) {
	m_bytes.clear();
	m_sMask.clear();
	size_t length = pattern.size();

	for (size_t i = 0; i < length; ) {
		if (pattern[i] == ' ') {
			++i;
			continue;
		}
		else if (pattern[i] == '?') {
			m_bytes.push_back(0);
			m_sMask += '?';

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
			m_bytes.push_back(static_cast<BYTE>(strtoul(byte_str, nullptr, 16)));
			m_sMask += 'x';
		}
		else
			++i;
	}
}

PatternScan::PatternScan(const std::string_view& module_name) {
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

	m_pBaseAddress = reinterpret_cast<uintptr_t>(info.lpBaseOfDll);
	m_nModuleSize = info.SizeOfImage;
}

PatternScan::PatternScan(HMODULE hModule) {
	if (!hModule) {
		LOG("[PATTERN SCAN] HMODULE is invalid argument\n");
		return;
	}

	MODULEINFO info = { 0 };
	if (!GetModuleInformation(GetCurrentProcess(), hModule, &info, sizeof(MODULEINFO))) {
		LOG("[PATTERN SCAN] Failed to get module information: %d\n", GetLastError());
		return;
	}

	m_pBaseAddress = reinterpret_cast<uintptr_t>(info.lpBaseOfDll);
	m_nModuleSize = info.SizeOfImage;
}

uintptr_t PatternScan::Find(const std::string_view& pattern) {
	ParsePattern(pattern);

	uint8_t* base_first_byte = reinterpret_cast<uint8_t*>(m_pBaseAddress);

	for (size_t i = 0; i < m_nModuleSize - m_sMask.size(); ++i) {
		bool found = true;
		for (size_t j = 0; j < m_sMask.size(); ++j) {
			if (m_sMask[j] == 'x' && base_first_byte[i + j] != m_bytes[j]) {
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