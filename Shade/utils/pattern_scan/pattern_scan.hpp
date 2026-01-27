#pragma once
#include <vector>
#include <string>
#include <Windows.h>

class PatternScan {
public:
	PatternScan() {};
	PatternScan(HMODULE hModule);
	PatternScan(const std::string_view& module_name);

	uintptr_t Find(const std::string_view& pattern);

private:
	DWORD				m_nModuleSize;
	uintptr_t			m_pBaseAddress;

	std::vector<BYTE>	m_bytes;
	std::string			m_sMask;

	void ParsePattern(const std::string_view& pattern);
};