#pragma once

#include "CTSList.hpp"
#include "CThreadMutex.hpp"
#include "CInterlockedInt.hpp"

enum class MemoryPoolGrowType_t : int32_t {
    UTLMEMORYPOOL_GROW_NONE = 0, // Don't allow new blobs.
    UTLMEMORYPOOL_GROW_FAST = 1, // New blob size is numElements * (i+1)  (ie: the blocks it allocates get larger and larger each time it allocates one).
    UTLMEMORYPOOL_GROW_SLOW = 2, // New blob size is numElements.
    UTLMEMORYPOOL_GROW_RBTREE = 3 // No blobs. All blocks are stored in RBTree.
};

enum MemAllocAttribute_t {
    MemAllocAttribute_Unk0 = 0,
    MemAllocAttribute_Unk1 = 1,
    MemAllocAttribute_Unk2 = 2
};

class CUtlMemoryPoolBase {
public:
    int Count() const {
        return m_BlocksAllocated;
    }

    int GetPeakAlloc() const {
        return m_PeakAlloc;
    }

public:
    struct FreeList_t {
        FreeList_t* m_pNext;
    };

    class CBlob {
    public:
        CBlob* m_pNext;
        int m_NumBytes; // Number of bytes in this blob.
        char m_Data[1];
        char m_Padding[3]; // to int align the struct
    };

    int m_BlockSize;
    int m_BlocksPerBlob;

    MemoryPoolGrowType_t m_GrowMode;

    CInterlockedInt m_BlocksAllocated;
    CInterlockedInt m_PeakAlloc;

    std::uint16_t m_nAlignment;
    std::uint16_t m_NumBlobs;

    CTSListBase m_FreeBlocks;

    MemAllocAttribute_t m_AllocAttribute;

    bool m_bUnk;
    CThreadMutex m_Mutex;

    CBlob* m_pBlobHead;

    int m_TotalSize;
};

//static_assert(sizeof(CUtlMemoryPoolBase) == 0x80);