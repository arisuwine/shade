#pragma once
#include <cstdint>

#include "../data/SchemaMetaInfoHandle_t.hpp"
#include "../data/SchemaClassInfoData_t.hpp"

#include "../../utils/vmt/vmt.hpp"

class IAppSystem {};

class ISchemaSystem : public IAppSystem {};

class CShemaSystem : public ISchemaSystem {
public:
	auto FindClassByScopedName(const char* pszScopedName) {
		SchemaMetaInfoHandle_t<CSchemaClassInfo> result{};

		using fn = void(__fastcall*)(void*, SchemaMetaInfoHandle_t<CSchemaClassInfo>*, const char*);

		auto pFunc = vmt::GetVirtual<fn>(this, 16);

		if (pFunc)
			pFunc(this, &result, pszScopedName);

		return result;
	}
};