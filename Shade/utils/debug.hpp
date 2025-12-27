#pragma once

#ifdef _DEBUG
#include <stdio.h>
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#define LOG(...) printf(__VA_ARGS__)
#define LOG_AND_RETURN(...) do { LOG(__VA_ARGS__); return FALSE; } while(0)
#else
#define LOG(...)
#define LOG_AND_RETURN(...) return FALSE
#endif