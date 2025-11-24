#pragma once
#include "../offsets.hpp"
#define MAX_ENTITY_LISTS 64

class CEntityIdentity;

class CConcreteEntityList
{
private:
	struct CList
	{
		CEntityIdentity* m_pHead;
		CEntityIdentity* m_pTail;
		int m_nCount;
	};
public:
	CConcreteEntityList() = delete;

	SCHEMA(CEntityIdentity**,	0x0,	m_pIdentityChunks	);
	SCHEMA(CEntityIdentity*,	0x200,	m_pFirstActiveEntity);
	SCHEMA(CEntityIdentity*,	0x208,	m_usedList_Head		);
};