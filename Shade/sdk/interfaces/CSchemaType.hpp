#pragma once
#include <vector>
#include <string>
#include <format>
#include <algorithm>

#include "../tier1/utlmap.hpp"

// forward declarations

class CSchemaClassInfo;
class CSchemaEnumInfo;
class CSchemaSystemTypeScope;
class CSchemaType;
class CSchemaType_DeclaredClass;

// enums

enum SchemaCollectionManipulatorAction_t
{
	// Returns count of the collection, index1 & index2 is unused
	SCHEMA_COLLECTION_MANIPULATOR_ACTION_GET_COUNT = 0,

	// Returns element from the collection at index1, index2 is unused
	SCHEMA_COLLECTION_MANIPULATOR_ACTION_GET_ELEMENT_CONST,
	SCHEMA_COLLECTION_MANIPULATOR_ACTION_GET_ELEMENT,

	// Swaps elements in a collection, index1 & index2 is first and second elements to swap
	SCHEMA_COLLECTION_MANIPULATOR_ACTION_SWAP_ELEMENTS,
	// Inserts elements to a collection at index1 where index2 is how much elements to insert
	SCHEMA_COLLECTION_MANIPULATOR_ACTION_INSERT_BEFORE,
	// Removes elements from a collection at index1 where index2 is how much elements to remove
	SCHEMA_COLLECTION_MANIPULATOR_ACTION_REMOVE_MULTIPLE,

	// Sets the count of a collection of size index1, index2 is unused
	SCHEMA_COLLECTION_MANIPULATOR_ACTION_SET_COUNT,
};

enum SchemaTypeCategory_t : uint8_t
{
	SCHEMA_TYPE_BUILTIN = 0,
	SCHEMA_TYPE_POINTER,
	SCHEMA_TYPE_BITFIELD,
	SCHEMA_TYPE_FIXED_ARRAY,
	SCHEMA_TYPE_ATOMIC,
	SCHEMA_TYPE_DECLARED_CLASS,
	SCHEMA_TYPE_DECLARED_ENUM,
	SCHEMA_TYPE_INVALID,
};

enum SchemaAtomicCategory_t : uint8_t
{
	SCHEMA_ATOMIC_PLAIN = 0,
	SCHEMA_ATOMIC_T,
	SCHEMA_ATOMIC_COLLECTION_OF_T,
	SCHEMA_ATOMIC_TT,
	SCHEMA_ATOMIC_I,
	SCHEMA_ATOMIC_INVALID,
};

enum SchemaBuiltinType_t
{
	SCHEMA_BUILTIN_TYPE_INVALID = 0,
	SCHEMA_BUILTIN_TYPE_VOID,
	SCHEMA_BUILTIN_TYPE_CHAR,
	SCHEMA_BUILTIN_TYPE_INT8,
	SCHEMA_BUILTIN_TYPE_UINT8,
	SCHEMA_BUILTIN_TYPE_INT16,
	SCHEMA_BUILTIN_TYPE_UINT16,
	SCHEMA_BUILTIN_TYPE_INT32,
	SCHEMA_BUILTIN_TYPE_UINT32,
	SCHEMA_BUILTIN_TYPE_INT64,
	SCHEMA_BUILTIN_TYPE_UINT64,
	SCHEMA_BUILTIN_TYPE_FLOAT32,
	SCHEMA_BUILTIN_TYPE_FLOAT64,
	SCHEMA_BUILTIN_TYPE_BOOL,
	SCHEMA_BUILTIN_TYPE_COUNT,
};

enum SchemaClassFlags_t : uint32_t
{
	SCHEMA_CF1_HAS_VIRTUAL_MEMBERS = (1 << 0),
	SCHEMA_CF1_IS_ABSTRACT = (1 << 1),
	SCHEMA_CF1_HAS_TRIVIAL_CONSTRUCTOR = (1 << 2),
	SCHEMA_CF1_HAS_TRIVIAL_DESTRUCTOR = (1 << 3),
	SCHEMA_CF1_LIMITED_METADATA = (1 << 4),
	SCHEMA_CF1_INHERITANCE_DEPTH_CALCULATED = (1 << 5),
	SCHEMA_CF1_MODULE_LOCAL_TYPE_SCOPE = (1 << 6),
	SCHEMA_CF1_GLOBAL_TYPE_SCOPE = (1 << 7),
	SCHEMA_CF1_CONSTRUCT_ALLOWED = (1 << 8),
	SCHEMA_CF1_CONSTRUCT_DISALLOWED = (1 << 9),
	SCHEMA_CF1_INFO_TAG_MNetworkAssumeNotNetworkable = (1 << 10),
	SCHEMA_CF1_INFO_TAG_MNetworkNoBase = (1 << 11),
	SCHEMA_CF1_INFO_TAG_MIgnoreTypeScopeMetaChecks = (1 << 12),
	SCHEMA_CF1_INFO_TAG_MDisableDataDescValidation = (1 << 13),
	SCHEMA_CF1_INFO_TAG_MClassHasEntityLimitedDataDesc = (1 << 14),
	SCHEMA_CF1_INFO_TAG_MClassHasCustomAlignedNewDelete = (1 << 15),
	SCHEMA_CF1_UNK016 = (1 << 16),
	SCHEMA_CF1_INFO_TAG_MConstructibleClassBase = (1 << 17),
	SCHEMA_CF1_INFO_TAG_MHasKV3TransferPolymorphicClassname = (1 << 18),
};

enum SchemaEnumFlags_t : uint8_t
{
	SCHEMA_EF_IS_REGISTERED = (1 << 0),
	SCHEMA_EF_MODULE_LOCAL_TYPE_SCOPE = (1 << 1),
	SCHEMA_EF_GLOBAL_TYPE_SCOPE = (1 << 2),
};

enum SchemaClassManipulatorAction_t
{
	// Registers pObject in a schemasystem
	SCHEMA_CLASS_MANIPULATOR_ACTION_REGISTER = 0,
	SCHEMA_CLASS_MANIPULATOR_ACTION_REGISTER_PRE,

	// Allocates object on the heap and constructs it in place, pObject is unused
	SCHEMA_CLASS_MANIPULATOR_ACTION_ALLOCATE,
	// Deallocates pObject
	SCHEMA_CLASS_MANIPULATOR_ACTION_DEALLOCATE,

	// Constructs pObject in place
	SCHEMA_CLASS_MANIPULATOR_ACTION_CONSTRUCT_IN_PLACE,
	// Destructs pObject in place
	SCHEMA_CLASS_MANIPULATOR_ACTION_DESCTRUCT_IN_PLACE,

	// Returns schema binding of pObject
	SCHEMA_CLASS_MANIPULATOR_ACTION_GET_SCHEMA_BINDING,
};

// typedefs

typedef int LoggingChannelID_t;
typedef void* (*SchemaCollectionManipulatorFn_t)(SchemaCollectionManipulatorAction_t eAction, void* pCollection, int index1, int index2);
typedef void* (*SchemaClassManipulatorFn_t)(SchemaClassManipulatorAction_t eAction, void* pObject);

// structs

struct SchemaMetadataEntryData_t
{
	const char* m_pszName;
	void* m_pData;
};

struct SchemaAtomicTypeInfo_t {
	const char* m_pszName;
	const char* m_pszTokenName;

	int m_nAtomicID;

	int m_nStaticMetadataCount;
	SchemaMetadataEntryData_t* m_pStaticMetadata;
};

struct SchemaBaseClassInfoData_t
{
	uint32_t m_nOffset;
	CSchemaClassInfo* m_pClass;
};

struct datamap_t
{
	void* dataDesc; // typedescription_t
	int					dataNumFields;
	char const* dataClassName;
	datamap_t* baseMap;

	void* m_pOptimizedDataMap; // optimized_datamap_t
	int					m_nPackedSize;

#if defined(_DEBUG)
	bool				bValidityChecked;
#endif // _DEBUG
};

struct SchemaEnumeratorInfoData_t
{
	const char* m_pszName;

	int64_t m_nValue;

	int m_nStaticMetadataCount;
	SchemaMetadataEntryData_t* m_pStaticMetadata;
};

template <typename T>
struct SchemaMetaInfoHandle_t
{
	SchemaMetaInfoHandle_t() : m_pObj(nullptr) {}
	SchemaMetaInfoHandle_t(T* obj) : m_pObj(obj) {}

	inline T* Get()									const { return m_pObj; }
	bool		operator<	(const SchemaMetaInfoHandle_t& rhs)	const { return m_pObj < rhs.m_pObj; }
	bool		operator==	(const SchemaMetaInfoHandle_t& rhs)	const { return m_pObj == rhs.m_pObj; }
	bool		operator!=	(const SchemaMetaInfoHandle_t& rhs)	const { return m_pObj != rhs.m_pObj; }
	T& operator*	()									const { return *m_pObj; };
	T* operator->	()									const { return m_pObj; };

	T* m_pObj;
};

struct AtomicTypeInfo_T_t
{
	int m_nAtomicID;
	CSchemaType* m_pTemplateType;
	SchemaCollectionManipulatorFn_t m_pfnManipulator;

	bool operator<(const AtomicTypeInfo_T_t& rhs) const
	{
		if (m_nAtomicID != rhs.m_nAtomicID)
			return m_nAtomicID < rhs.m_nAtomicID;

		if (m_pTemplateType != rhs.m_pTemplateType)
			return m_pTemplateType < rhs.m_pTemplateType;

		return (void*)m_pfnManipulator < (void*)rhs.m_pfnManipulator;
	}
};

struct AtomicTypeInfo_CollectionOfT_t
{
	int m_nAtomicID;
	CSchemaType* m_pTemplateType;
	uint64_t m_nFixedBufferCount;
	SchemaCollectionManipulatorFn_t m_pfnManipulator;

	bool operator<(const AtomicTypeInfo_CollectionOfT_t& rhs) const
	{
		if (m_nAtomicID != rhs.m_nAtomicID)
			return m_nAtomicID < rhs.m_nAtomicID;

		if (m_pTemplateType != rhs.m_pTemplateType)
			return m_pTemplateType < rhs.m_pTemplateType;

		if (m_nFixedBufferCount != rhs.m_nFixedBufferCount)
			return m_nFixedBufferCount < rhs.m_nFixedBufferCount;

		return (void*)m_pfnManipulator < (void*)rhs.m_pfnManipulator;
	}
};

struct AtomicTypeInfo_TT_t
{
	bool operator<(const AtomicTypeInfo_TT_t& rhs) const
	{
		if (m_nAtomicID != rhs.m_nAtomicID)
			return m_nAtomicID < rhs.m_nAtomicID;

		if (m_pTemplateType != rhs.m_pTemplateType)
			return m_pTemplateType < rhs.m_pTemplateType;

		return m_pTemplateType2 < rhs.m_pTemplateType2;
	}

	int m_nAtomicID;
	CSchemaType* m_pTemplateType;
	CSchemaType* m_pTemplateType2;
};

struct AtomicTypeInfo_I_t
{
	bool operator<(const AtomicTypeInfo_I_t& rhs) const
	{
		if (m_nAtomicID != rhs.m_nAtomicID)
			return m_nAtomicID < rhs.m_nAtomicID;

		return m_nInteger < rhs.m_nInteger;
	}

	int m_nAtomicID;
	int m_nInteger;
};

struct TypeAndCountInfo_t {
	int m_nElementCount;
	CSchemaType* m_pElementType;
};

template <typename T>
struct SchemaDeclaredTypeEntry_t {
	uint32_t m_Hash1;
	uint32_t m_Hash2;
	uint32_t m_Hash3;
	uint32_t m_Hash4;
	T* m_pData;
};

// CSchemaTypes

class CSchemaType {
public:
	void* vft;									// 0x0
	const char* m_sTypeName;					// 0x8
	CSchemaSystemTypeScope* m_pTypeScope;		// 0x10
	SchemaTypeCategory_t m_eTypeCategory;		// 0x18
	SchemaAtomicCategory_t m_eAtomicCategory;   // 0x19
};

class CSchemaType_Builtin : public CSchemaType
{
public:
	SchemaBuiltinType_t m_eBuiltinType; // int32
	uint8_t m_nSize;
};

class CSchemaType_Ptr : public CSchemaType
{
public:
	CSchemaType* m_pObjectType;
};

class CSchemaType_Atomic : public CSchemaType
{
public:
	SchemaAtomicTypeInfo_t* m_pAtomicInfo;
	int m_nAtomicID;
	uint16_t m_nSize;
	uint8_t m_nAlignment;
};

class CSchemaType_Atomic_T : public CSchemaType_Atomic
{
public:
	CSchemaType* m_pTemplateType;
};

class CSchemaType_Atomic_CollectionOfT : public CSchemaType_Atomic_T
{
public:
	SchemaCollectionManipulatorFn_t m_pfnManipulator;
	uint16_t m_nElementSize;
	uint64_t m_nFixedBufferCount;
};

class CSchemaType_Atomic_TT : public CSchemaType_Atomic_T
{
public:
	CSchemaType* m_pTemplateType2;
};

class CSchemaType_Atomic_I : public CSchemaType_Atomic
{
public:
	int m_nInteger;
};

class CSchemaType_DeclaredClass : public CSchemaType
{
public:
	CSchemaClassInfo* m_pClassInfo;
	bool m_bGlobalPromotionRequired;
};

class CSchemaType_DeclaredEnum : public CSchemaType
{
public:
	CSchemaEnumInfo* m_pEnumInfo;
	bool m_bGlobalPromotionRequired;
};

class CSchemaType_FixedArray : public CSchemaType
{
public:
	int m_nElementCount;
	uint16_t m_nElementSize;
	uint8_t m_nElementAlignment;
	CSchemaType* m_pElementType;
};

class CSchemaType_Bitfield : public CSchemaType
{
public:
	int m_nBitfieldCount;
};

// Info

struct SchemaClassFieldData_t
{
	const char* m_pszName;

	CSchemaType* m_pType;

	int m_nSingleInheritanceOffset;

	int m_nStaticMetadataCount;
	SchemaMetadataEntryData_t* m_pStaticMetadata;

	std::string GetTypeName() const {
		std::string sTypeName = m_pType->m_sTypeName;
		sTypeName.erase(std::remove(sTypeName.begin(), sTypeName.end(), ' '), sTypeName.end());
		return sTypeName;
	}
};

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

	SchemaClassFlags_t m_nClassFlags;
	uint32_t m_nFlags2;

	typedef void* (*SchemaClassManipulatorFn_t)(int eAction, void* pObject);
	SchemaClassManipulatorFn_t m_pfnManipulator;
};

class CSchemaClassInfo : public SchemaClassInfoData_t
{
public:
	std::vector<SchemaClassFieldData_t> GetFields() const {
		if (!m_pFields)
			return {};

		return { m_pFields, m_pFields + m_nFieldCount };
	}

	std::string_view GetModuleName() const {
		if (!m_pszProjectName)
			return {};

		return m_pszProjectName;
	}

	std::string GetName() const {
		if (!m_pszName)
			return "";

		std::string sName = m_pszName;
		std::replace(sName.begin(), sName.end(), ':', '_');

		return sName;
	}

	std::string GetBaseClassName() const {
		if (!m_pBaseClasses || !m_pBaseClasses->m_pClass)
			return {};

		return m_pBaseClasses->m_pClass->GetName();
	}

	std::vector<std::string> GetStringFlags() const {
		std::vector<std::string> flags;

		if (m_nClassFlags & SCHEMA_CF1_HAS_VIRTUAL_MEMBERS)
			flags.emplace_back("Has VTable");

		if (m_nClassFlags & SCHEMA_CF1_IS_ABSTRACT)
			flags.emplace_back("Is Absract");

		if (m_nClassFlags & SCHEMA_CF1_HAS_TRIVIAL_CONSTRUCTOR)
			flags.emplace_back("Has Trivial Constructor");

		if (m_nClassFlags & SCHEMA_CF1_HAS_TRIVIAL_DESTRUCTOR)
			flags.emplace_back("Has Trivial Destructor");

		if (m_nClassFlags & SCHEMA_CF1_CONSTRUCT_ALLOWED)
			flags.emplace_back("Construct Allowed");

		if (m_nClassFlags & SCHEMA_CF1_MODULE_LOCAL_TYPE_SCOPE)
			flags.emplace_back("Local Type Scope");

		if (m_nClassFlags & SCHEMA_CF1_GLOBAL_TYPE_SCOPE)
			flags.emplace_back("Global Type Scope");

		return flags;
	}
};

struct SchemaEnumInfoData_t
{
	CSchemaEnumInfo* m_pSchemaBinding;

	const char* m_pszName;
	const char* m_pszProjectName;

	uint8_t m_nSize;
	uint8_t m_nAlignment;

	uint8_t m_nFlags;

	uint16_t m_nEnumeratorCount;
	uint16_t m_nStaticMetadataCount;

	SchemaEnumeratorInfoData_t* m_pEnumerators;
	SchemaMetadataEntryData_t* m_pStaticMetadata;

	CSchemaSystemTypeScope* m_pTypeScope;

	int64_t m_nMinEnumeratorValue;
	int64_t m_nMaxEnumeratorValue;
};

class CSchemaEnumInfo : public SchemaEnumInfoData_t {
public:
	std::vector<SchemaEnumeratorInfoData_t> GetFields() const {
		if (!m_pEnumerators)
			return {};

		return { m_pEnumerators, m_pEnumerators + m_nEnumeratorCount };
	}

	std::string_view GetModuleName() const {
		if (!m_pszProjectName)
			return {};

		return m_pszProjectName;
	}

	std::string GetName() const {
		if (!m_pszName)
			return "";

		std::string sName = m_pszName;
		std::replace(sName.begin(), sName.end(), ':', '_');

		return sName;
	}

	std::vector<std::string> GetStringFlags() const {
		std::vector<std::string> flags;

		if (m_nFlags & SCHEMA_EF_MODULE_LOCAL_TYPE_SCOPE)
			flags.emplace_back("Local Type Scope");

		if (m_nFlags & SCHEMA_EF_GLOBAL_TYPE_SCOPE)
			flags.emplace_back("Global Type Scope");

		return flags;
	}

	uint8_t GetSize() const {
		return m_nSize;
	}

	int64_t GetMinValue() const {
		return m_nMinEnumeratorValue;
	}
};


template <typename K, typename V>
class CSchemaPtrMap {
public:
	CUtlMap<K, V, uint16_t> m_Map;
};


