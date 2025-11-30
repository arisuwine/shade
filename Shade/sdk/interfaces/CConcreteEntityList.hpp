#pragma once
#include "../offsets.hpp"

class CEntityIdentity;

class CConcreteEntityList
{
private:
public:
	CConcreteEntityList() = delete;

	SCHEMA(CEntityIdentity**,	0x0,	m_pIdentityChunks	);
	SCHEMA(CEntityIdentity*,	0x200,	m_pFirstActiveEntity);
	SCHEMA(CEntityIdentity*,	0x208,	m_usedList_Head		);
};