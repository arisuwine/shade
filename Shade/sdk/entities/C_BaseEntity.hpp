#pragma once
#include "../offsets.hpp"

#include "../interfaces/CHandle.hpp"
#include "../interfaces/CEntityInstance.hpp"

class CCollisionProperty;
class CGameSceneNode;

class C_BaseEntity : public CEntityInstance {
public:
	C_BaseEntity() = delete;

	enum TEAM : int {
		SPEC = 1,
		T = 2,
		CT = 3
	};

	SCHEMA	(int,					offsets::C_BaseEntity::m_iHealth,			m_iHealth		);
	SCHEMA	(TEAM,					offsets::C_BaseEntity::m_iTeamNum,			m_iTeamNum		);
	SCHEMA	(CCollisionProperty*,	offsets::C_BaseEntity::m_pCollision,		m_pCollision	);
	SCHEMA	(CGameSceneNode*,		offsets::C_BaseEntity::m_pGameSceneNode,	m_pGameSceneNode);
	SCHEMA_R(CHandle<C_BaseEntity>, offsets::C_BaseEntity::m_hOwnerEntity,		m_hOwnerEntity	);
};