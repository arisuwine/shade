#pragma once
#define MAX_ENTITY_LISTS 64

class CEntityIdentity;

class CConcreteEntityList
{
	struct CList
	{
		CEntityIdentity* m_pHead;
		CEntityIdentity* m_pTail;
		int m_nCount;
	};
public:
	CEntityIdentity* m_pIdentityChunks[MAX_ENTITY_LISTS];
	CEntityIdentity* m_pFirstActiveEntity;
	CConcreteEntityList::CList m_usedList;

	inline CEntityIdentity* m_pHead() const {
		return *reinterpret_cast<CEntityIdentity**>(m_usedList.m_pHead);
	}
};