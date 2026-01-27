#pragma
#include "../offsets.hpp"

#include "../math/vector_3d.hpp"

#include "../utils/cutlvector.hpp"

class CEntityInstance;

class CGlowObjectManager {
public:
	struct GlowObjectDefinition_t {
		CEntityInstance* m_pEntity;
		Vector3D m_vGlowColor;
		float m_flGlowAlpha;

		bool m_bRenderWhenOccluded;
		bool m_bRenderWhenUnoccluded;
		bool m_bFullBloomRender;
		int m_nFullBloomStencilTestValue;
		int m_nSplitScreenSlot;

		int m_nNextFreeSlot;
	};

	using GlowObjectsVector = CUtlVector<GlowObjectDefinition_t>;

	SCHEMA(GlowObjectsVector, offsets::client::CGlowObjectManager::m_GlowObjectDefinitions, m_GlowObjectDefinitions);
};