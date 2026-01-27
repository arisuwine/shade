#pragma once
#include "../offsets.hpp"

#include "../math/vector_3d.hpp"

class C_BaseEntity;

class CGlowProperty {
public:
	SCHEMA(C_BaseEntity*,	offsets::client::CGlowProperty::m_pParent,				m_pParent);
	SCHEMA(Vector3D,		offsets::client::CGlowProperty::m_vGlowColor,			m_vGlowColor);
	SCHEMA(uint32_t,		offsets::client::CGlowProperty::m_glowColorOverride,	m_glowColorOverride);
	SCHEMA(bool,			offsets::client::CGlowProperty::m_bGlowing,				m_bGlowing);
};