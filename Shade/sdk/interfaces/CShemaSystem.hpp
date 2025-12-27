#pragma once
#include <cstdint>

#include "../data/SchemaMetaInfoHandle_t.hpp"
#include "../data/SchemaClassInfoData_t.hpp"

#include "../../utils/vmt/vmt.hpp"

class IAppSystem {
public:
	IAppSystem() = delete;
};

class ISchemaSystem : public IAppSystem {
public:
	ISchemaSystem() = delete;
};

class CShemaSystem : public ISchemaSystem {
public:
	CShemaSystem() = delete;

	auto FindClassByScopedName(const char* pszScopedName) {
		SchemaMetaInfoHandle_t<CSchemaClassInfo> result{};

		using fn = void(__fastcall*)(void*, SchemaMetaInfoHandle_t<CSchemaClassInfo>*, const char*);

		auto pFunc = vmt::get_virtual<fn>(this, 16);

		if (pFunc)
			pFunc(this, &result, pszScopedName);

		return result;
	}
};