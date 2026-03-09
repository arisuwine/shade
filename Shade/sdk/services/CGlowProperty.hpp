#pragma once
#include "../offsets.hpp"

#include "../math/Vector3D.hpp"

class C_BaseEntity;

class CGlowProperty {
public:
	SCHEMA(C_BaseEntity*,	0x8,				m_pParent);
	SCHEMA(Vector3D,		0x18,			m_vGlowColor);
	SCHEMA(uint32_t,		0x40,	m_glowColorOverride);
	SCHEMA(bool,			0x51,				m_bGlowing);
};