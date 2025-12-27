#pragma once
#include <vector>
#include <string>
#include <Windows.h>

class pattern_scan {
public:
	pattern_scan() {};
	pattern_scan(HMODULE hModule);
	pattern_scan(const std::string_view& module_name);

	uintptr_t find(const std::string_view& pattern);

private:
	DWORD module_size;
	uintptr_t base_address;

	std::vector<BYTE> bytes;
	std::string mask;

	void parse_pattern(const std::string_view& pattern);
};