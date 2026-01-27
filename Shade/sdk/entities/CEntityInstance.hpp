#pragma once
#include "../offsets.hpp"

#include "../data/SchemaMetaInfoHandle_t.hpp"
#include "../data/SchemaClassInfoData_t.hpp"

#include "../../utils/vmt/vmt.hpp"

class CEntityIdentity;

class CEntityInstance {
public:	
	SCHEMA(CEntityIdentity*, offsets::client::CEntityInstance::m_pEntity, m_pEntity);

	auto Schema_DynamicBinding() {
		SchemaMetaInfoHandle_t<CSchemaClassInfo> result{};

		using fn = void(__fastcall*)(void*, SchemaMetaInfoHandle_t<CSchemaClassInfo>*);

		auto pFunc = vmt::GetVirtual<fn>(this, 44);

		if (pFunc)
			pFunc(this, &result);

		return result;
	}
};
