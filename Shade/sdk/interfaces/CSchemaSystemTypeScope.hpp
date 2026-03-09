#pragma once
#include <cstdint>

#include "CSchemaType.hpp"
#include "../tier1/utltshash.hpp"

class ISchemaSystemTypeScope {
public:
	//virtual CSchemaClassInfo* InstallSchemaClassBinding(const char* pszModuleName, CSchemaClassInfo* pClassInfo) = 0; // 0
	//virtual CSchemaEnumInfo* InstallSchemaEnumBinding(const char* pszModuleName, CSchemaEnumInfo* pEnumInfo) = 0; // 1

	//virtual SchemaMetaInfoHandle_t<CSchemaClassInfo> 					FindDeclaredClass(const char* pszClassName) = 0; // 2
	//virtual SchemaMetaInfoHandle_t<CSchemaEnumInfo> 					FindDeclaredEnum(const char* pszEnumName) = 0; // 3

	//virtual SchemaMetaInfoHandle_t<CSchemaType_Builtin> 				FindBuiltinTypeByName(const char* pszBuiltinName) = 0; // 4

	//virtual SchemaMetaInfoHandle_t<CSchemaType_Builtin> 				Type_Builtin(SchemaBuiltinType_t eBuiltinType) = 0; // 5
	//virtual SchemaMetaInfoHandle_t<CSchemaType_Ptr>						Type_Ptr(CSchemaType* pObjectType) = 0; // 6
	//virtual SchemaMetaInfoHandle_t<CSchemaType_Atomic>					Type_Atomic(const char* pszAtomicName, uint16_t nSize, uint8_t nAlignment) = 0; // 7
	//virtual SchemaMetaInfoHandle_t<CSchemaType_Atomic_T>				Type_Atomic_T(const char* pszAtomicName, uint16_t nSize, uint8_t nAlignment, CSchemaType* pTemplateType) = 0; // 8
	//virtual SchemaMetaInfoHandle_t<CSchemaType_Atomic_CollectionOfT> 	Type_Atomic_CollectionOfT(const char* pszAtomicName, uint16_t nSize, uint8_t nAlignment, uint16_t nElementSize, CSchemaType* pTemplateType, uint64_t nFixedBufferCount, SchemaCollectionManipulatorFn_t manipulator) = 0; // 9
	//virtual SchemaMetaInfoHandle_t<CSchemaType_Atomic_TT>				Type_Atomic_TT(const char* pszAtomicName, uint16_t nSize, uint8_t nAlignment, CSchemaType* pTemplateType, CSchemaType* pTemplateType2) = 0; // 10
	//virtual SchemaMetaInfoHandle_t<CSchemaType_Atomic_I>				Type_Atomic_I(const char* pszAtomicName, uint16_t nSize, uint8_t nAlignment, int nInteger) = 0; // 11
	//virtual SchemaMetaInfoHandle_t<CSchemaType_DeclaredClass>			Type_DeclaredClass(const char* pszClassName) = 0; // 12
	//virtual SchemaMetaInfoHandle_t<CSchemaType_DeclaredEnum>			Type_DeclaredEnum(const char* pszEnumName) = 0; // 13
	//virtual SchemaMetaInfoHandle_t<CSchemaType_FixedArray>				Type_FixedArray(CSchemaType* pElementType, int nElementCount, uint16_t nElementSize, uint8_t nElementAlignment) = 0; // 14
	//virtual SchemaMetaInfoHandle_t<CSchemaType_FixedArray>				Type_FixedArray_Multidimensional(CSchemaType* pElementType, uint16_t nElementSize, uint8_t nElementAlignment, ...) = 0; // 15
	//virtual SchemaMetaInfoHandle_t<CSchemaType_Bitfield>				Type_Bitfield(int nSize) = 0; // 16

	//virtual SchemaMetaInfoHandle_t<CSchemaType_Atomic>					FindType_Atomic(int nAtomicID) = 0; // 17
	//virtual SchemaMetaInfoHandle_t<CSchemaType_Atomic_T>				FindType_Atomic_T(int nAtomicID, CSchemaType* pTemplateType) = 0; // 18
	//virtual SchemaMetaInfoHandle_t<CSchemaType_Atomic_CollectionOfT> 	FindType_Atomic_CollectionOfT(int nAtomicID, CSchemaType* pTemplateType, SchemaCollectionManipulatorFn_t manipulator) = 0; // 19
	//virtual SchemaMetaInfoHandle_t<CSchemaType_Atomic_TT> 				FindType_Atomic_TT(int nAtomicID, CSchemaType* pTemplateType, CSchemaType* pTemplateType2) = 0; // 20
	//virtual SchemaMetaInfoHandle_t<CSchemaType_Atomic_I> 				FindType_Atomic_I(int nAtomicID, int nInteger) = 0; // 21

	//virtual CSchemaType_DeclaredClass* FindType_DeclaredClass(const char* pszClassName) = 0; // 22
	//virtual CSchemaType_DeclaredEnum* FindType_DeclaredEnum(const char* pszEnumName) = 0; // 23

	//virtual CSchemaClassInfo* FindRawClassBinding(const char* pszClassName) = 0; // 24
	//virtual CSchemaClassInfo* FindRawClassBinding(unsigned int nClassID) = 0; // 25
	//virtual CSchemaEnumInfo* FindRawEnumBinding(const char* pszEnumName) = 0; // 26
	//virtual CSchemaEnumInfo* FindRawEnumBinding(unsigned int nEnumID) = 0; // 27

	//virtual const char* GetScopeName() = 0; // 28
	//virtual bool 														IsGlobalScope() = 0; // 29

	//virtual void 														MarkClassAsRequiringGlobalPromotion(const CSchemaClassInfo* pClassInfo) = 0; // 30
	//virtual void 														MarkEnumAsRequiringGlobalPromotion(const CSchemaEnumInfo* pEnumInfo) = 0; // 31

	//virtual void 														ResolveAtomicInfoThreadsafe(const SchemaAtomicTypeInfo_t** ppAtomicInfo, const char* pszAtomicName, int nAtomicID) = 0; // 32
	//virtual void 														ResolveEnumInfoThreadsafe(const CSchemaEnumInfo** ppEnumInfo, const char* pszEnumName) = 0; // 33
	//virtual void 														ResolveClassInfoThreadsafe(const CSchemaClassInfo** ppClassInfo, const char* pszClassName) = 0; // 34
};

class CSchemaSystemTypeScope
{
public:
	void*																				__vftable; //0x0000
	char																				m_ScopeName[256]; //0x0008
	CSchemaSystemTypeScope*																m_pParentScope;
	bool																				m_bBuiltinTypesInitalized; //0x0110
	CSchemaType_Builtin																	m_BuiltinTypes[14]; //0x0118
	CSchemaPtrMap<CSchemaType*, CSchemaType_Ptr*>										m_Ptr; //0x0348
	CSchemaPtrMap<int, CSchemaType_Atomic*>												m_Atomic; //0x0378
	CSchemaPtrMap<AtomicTypeInfo_T_t, CSchemaType_Atomic_T*>							m_Atomic_T; //0x03A8
	CSchemaPtrMap<AtomicTypeInfo_CollectionOfT_t, CSchemaType_Atomic_CollectionOfT*>	m_Atomic_CollectionOfT; //0x03D8
	CSchemaPtrMap<AtomicTypeInfo_TT_t, CSchemaType_Atomic_TT*>							m_Atomic_TT; //0x0408
	CSchemaPtrMap<AtomicTypeInfo_I_t, CSchemaType_Atomic_I*>							m_Atomic_I; //0x0438
	//char pad1[0x30];
	CSchemaPtrMap<uint16_t, CSchemaType_DeclaredClass*>									m_DeclaredClass; //0x0468
	CSchemaPtrMap<uint16_t, CSchemaType_DeclaredEnum*>									m_DeclaredEnum; //0x0498
	CSchemaPtrMap<int, const SchemaAtomicTypeInfo_t*>									m_AtomicTypeInfo; //0x04C8
	CSchemaPtrMap<TypeAndCountInfo_t, CSchemaType_FixedArray*>							m_FixedArray; //0x04F8
	CSchemaPtrMap<int, CSchemaType_Bitfield*>											m_Bitfield; //0x0528
	char																				pad_04A8[0xB8];
	CUtlTSHash<CSchemaClassInfo*, 256, uint32_t>										m_ClassBindings; //0x0560
	CUtlTSHash<CSchemaEnumInfo*, 256, uint32_t>											m_EnumBindings; //0x1DD0

	std::string_view GetName() const {
		return m_ScopeName;
	}
};