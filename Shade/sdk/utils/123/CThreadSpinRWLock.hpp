#pragma once
#include <cstdint>
#include <shared_mutex>

class CThreadSpinRWLock {
public:
    struct LockInfo_t {
        uint32_t m_writerId;
        int32_t m_nReaders;
    };

public:
    //void* m_pThreadSpin;
    //LockInfo_t m_lockInfo;
    //const char* m_pszDebugName;
    std::shared_mutex m_mutex;
};

//static_assert(sizeof(CThreadSpinRWLock) == 0x18);