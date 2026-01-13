#pragma once
#include "../offsets.hpp"

class CEntityIdentity;

class CConcreteEntityList
{
private:
public:
	CConcreteEntityList() = delete;

	SCHEMA(CEntityIdentity**,	offsets::client::CConcreteEntityList::m_pIdentityChunks,	m_pIdentityChunks	);
	SCHEMA(CEntityIdentity*,	offsets::client::CConcreteEntityList::m_pFirstActiveEntity,	m_pFirstActiveEntity);
	SCHEMA(CEntityIdentity*,	offsets::client::CConcreteEntityList::m_usedList_Head,		m_usedList_Head		);
};