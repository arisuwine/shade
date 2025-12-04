#pragma
#include "../offsets.hpp"

#include "../math/vector/vector_3d.hpp"

#include "../../utils/valve/utlvector.hpp"

class CEntityInstance;

class CGlowObjectManager {
public:
	CGlowObjectManager() = delete;

	struct GlowObjectDefinition_t {
		CEntityInstance* m_pEntity;
		vector_3d m_vGlowColor;
		float m_flGlowAlpha;

		bool m_bRenderWhenOccluded;
		bool m_bRenderWhenUnoccluded;
		bool m_bFullBloomRender;
		int m_nFullBloomStencilTestValue;
		int m_nSplitScreenSlot;

		int m_nNextFreeSlot;
	};

	using GlowObjectsVector = CUtlVector<GlowObjectDefinition_t>;

	SCHEMA(GlowObjectsVector, offsets::CGlowObjectManager::m_GlowObjectDefinitions, m_GlowObjectDefinitions);
};