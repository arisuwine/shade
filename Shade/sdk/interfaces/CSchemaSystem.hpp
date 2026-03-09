#pragma once
#include <cstdint>

#include "CSchemaSystemTypeScope.hpp"
#include "CSchemaType.hpp"

#include "../tier1/utlvector.hpp"

#include "../../utils/vmt/vmt.hpp"

struct ClassBindingScopeBlock_t {
public:
	uint64_t m_Hash;
	uint64_t m_pUnknown;
	CSchemaType_DeclaredClass* m_pDeclaredClass;
};

class ISchemaSystem {
public:
	auto FindClassByScopedName(const char* pszScopedName) {
		SchemaMetaInfoHandle_t<CSchemaClassInfo> result{};

		using fn = void(__fastcall*)(void*, SchemaMetaInfoHandle_t<CSchemaClassInfo>*, const char*);

		auto pFunc = vmt::GetVirtual<fn>(this, 16);

		if (pFunc)
			pFunc(this, &result, pszScopedName);

		return result;
	}

	CSchemaSystemTypeScope* FindTypeScopeForModule(const char* pszModuleName, const char** ppszBindingName = NULL) {
		return CALL_VIRTUAL(this, CSchemaSystemTypeScope*, 13, pszModuleName, ppszBindingName);
	}
};

class CSchemaSystem : public ISchemaSystem {
public:
	char pad[0x190];
	CUtlVector<CSchemaSystemTypeScope*> m_TypeScopes;
};