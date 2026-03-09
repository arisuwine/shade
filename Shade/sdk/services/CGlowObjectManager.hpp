#pragma
#include "../offsets.hpp"

#include "../math/Vector3D.hpp"

#include "../tier1/utlvector.hpp"

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

	char pad[0x20];
	//SCHEMA(GlowObjectsVector, 0x20, m_GlowObjectDefinitions);
	CUtlVector<GlowObjectDefinition_t> m_GlowObjectDefinitions;
};