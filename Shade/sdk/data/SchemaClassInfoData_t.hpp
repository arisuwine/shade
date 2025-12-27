#pragma once
#include <cstdint>

class CSchemaClassInfo;
class SchemaClassFieldData_t;
class SchemaBaseClassInfoData_t;
class datamap_t;
class SchemaMetadataEntryData_t;
class CSchemaSystemTypeScope;
class CSchemaType_DeclaredClass;

struct SchemaClassInfoData_t
{
	CSchemaClassInfo* m_pSchemaBinding;

	const char* m_pszName;
	const char* m_pszProjectName;

	int m_nSize;

	uint16_t m_nFieldCount;
	uint16_t m_nStaticMetadataCount;

	uint8_t m_nAlignment;
	uint8_t m_nBaseClassCount;

	uint16_t m_nMultipleInheritanceDepth;
	uint16_t m_nSingleInheritanceDepth;

	SchemaClassFieldData_t* m_pFields;
	SchemaBaseClassInfoData_t* m_pBaseClasses;
	datamap_t* m_pDataDescMap;
	SchemaMetadataEntryData_t* m_pStaticMetadata;

	CSchemaSystemTypeScope* m_pTypeScope;
	CSchemaType_DeclaredClass* m_pDeclaredClass;

	uint32_t m_nFlags1;
	uint32_t m_nFlags2;

	typedef void* (*SchemaClassManipulatorFn_t)(int eAction, void* pObject);
	SchemaClassManipulatorFn_t m_pfnManipulator;
};

class CSchemaClassInfo : public SchemaClassInfoData_t
{
};