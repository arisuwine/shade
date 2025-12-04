#pragma once
#include "../offsets.hpp"

#include "../math/vector/vector_3d.hpp"

class C_BaseEntity;

class CGlowProperty {
public:
	CGlowProperty() = delete;

	SCHEMA(C_BaseEntity*,	offsets::CGlowProperty::m_pParent,				m_pParent);
	SCHEMA(vector_3d,		offsets::CGlowProperty::m_vGlowColor,			m_vGlowColor);
	SCHEMA(uint32_t,		offsets::CGlowProperty::m_glowColorOverride,	m_glowColorOverride);
	SCHEMA(bool,			offsets::CGlowProperty::m_bGlowing,				m_bGlowing);
};