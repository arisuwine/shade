#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include <psapi.h>

#define PS_LOGGING

#ifdef PS_LOGGING
#include <stdio.h>
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif

class pattern_scan {
public:
	pattern_scan() {};
	pattern_scan(HMODULE hModule);
	pattern_scan(const std::string_view& pattern);

	uintptr_t find(const std::string_view& pattern);

private:
	DWORD module_size;
	uintptr_t base_address;

	std::vector<BYTE> bytes;
	std::string mask;

	void parse_pattern(const std::string_view& pattern);
};