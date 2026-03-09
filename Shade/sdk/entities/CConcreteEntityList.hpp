#pragma once
#include "../offsets.hpp"

#define MAX_ENTITY_LISTS 64 // 0x3F

class CEntityIdentity;

class CConcreteEntityList {
public:
	struct CList
	{
		CEntityIdentity* m_pHead;
		CEntityIdentity* m_pTail;
		int m_nCount;
	};
public:
	CEntityIdentity* m_pIdentityChunks[MAX_ENTITY_LISTS];
	CEntityIdentity* m_pFirstActiveEntity; // 512
	CConcreteEntityList::CList m_usedList;	// 520
	CConcreteEntityList::CList m_dormantList; // 544
	CConcreteEntityList::CList m_freeNetworkableList; // 568
	CConcreteEntityList::CList m_freeNonNetworkableList; // 592
	uint32_t m_nNetworkableEntityLimit; // 0x268
	uint32_t m_nNonNetworkableEntityLimit; // 0x26c
	uint32_t m_nMaxPlayers;
	char pad[2048];
};