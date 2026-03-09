#pragma once
#include <cstdint>
#include <cstddef>

#ifdef _WIN32
typedef uint32_t ThreadId_t;
#else
typedef uint64_t ThreadId_t;
#endif

constexpr auto kTtSizeofCriticalsection = 40;

class CThreadMutex {
public:
    //std::byte m_CriticalSection[kTtSizeofCriticalsection];

    ThreadId_t m_currentOwnerID;
    uint16_t m_lockCount;
    bool m_bTrace;
    const char* m_pDebugName;
};

static_assert(sizeof(CThreadMutex) == 0x10);