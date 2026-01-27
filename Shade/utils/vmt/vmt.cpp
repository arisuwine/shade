#include "vmt.hpp"

vmt::Shadowing::Shadowing(void* object) : m_pObject(nullptr), m_pVftOrig(nullptr), m_pUserVft(nullptr), m_iVftSize(0), m_bIsInit(FALSE) {
	if (!object) {
		LOG("[VMT SHADOWING] Object Pointer is nullptr.\n");
		return;
	}
	
	m_pObject = object;
	m_pVftOrig = *reinterpret_cast<uintptr_t**>(m_pObject);

	m_iVftSize = GetFunctionCount();
	if (m_iVftSize == 0) {
		LOG("[VMT SHADOWING] Failed to calculate VTable size of size os 0: %p.\n", m_pVftOrig);
		return;
	}

	m_pShadowAlloc = new uintptr_t[m_iVftSize + 1];
	memcpy(m_pShadowAlloc, m_pVftOrig - 1, (m_iVftSize + 1) * sizeof(void*));

	m_pUserVft = m_pShadowAlloc + 1;
	*reinterpret_cast<void**>(object) = m_pUserVft;

	m_bIsInit = TRUE;
}

size_t vmt::Shadowing::GetFunctionCount() {
	if (!m_pVftOrig)
		return 0;

	size_t vft_size = 0; 
	MEMORY_BASIC_INFORMATION memory_info;
	while (true) {
		uintptr_t func_ptr = m_pVftOrig[vft_size];
		if (!func_ptr)
			break;

		if (!VirtualQuery((LPCVOID)func_ptr, &memory_info, sizeof(memory_info)))
			break;

		#define PAGE_EXECUTABLE (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)
		#define PAGE_SECURE (PAGE_GUARD | PAGE_NOACCESS)

		if (memory_info.State != MEM_COMMIT || memory_info.Protect & PAGE_SECURE || !(memory_info.Protect & PAGE_EXECUTABLE))
			break;

		vft_size++;
	}

	return vft_size;
}

bool vmt::Shadowing::UnHook(size_t index) {
	if (!m_bIsInit)
		return FALSE;

	if (index >= m_iVftSize) {
		LOG("[VMT SHADOWING] Unable to unhook. Index is greater than Virtual Function Table Size. Max Size: %zu\n", m_iVftSize);
		return FALSE;
	}

	if (m_OriginalFuncs.find(index) == m_OriginalFuncs.end()) {
		LOG("[VMT SHADOWING] Unable to find original function.\n");
		return FALSE;
	}
	
	m_pUserVft[index] = m_OriginalFuncs[index];
	m_OriginalFuncs.erase(index);
	return TRUE;
}

bool vmt::Shadowing::UnHookAll() {
	if (!m_bIsInit)
		return FALSE;

	for (auto& [index, func] : m_OriginalFuncs)
		m_pUserVft[index] = func;

	m_OriginalFuncs.clear();
	return TRUE;
}

bool vmt::Shadowing::Shutdown() {
	if (!m_bIsInit) {
		LOG("[VMT SHADOWING] VMT is not hooked.\n");
		return TRUE;
	}
	
	*reinterpret_cast<uintptr_t**>(m_pObject) = m_pVftOrig;

	m_pObject = nullptr;
	m_pVftOrig = nullptr;

	delete[] m_pShadowAlloc;
	m_pShadowAlloc = nullptr;
	m_pUserVft = nullptr;

	m_OriginalFuncs.clear();
	m_bIsInit = FALSE;
	return TRUE;
}

vmt::Shadowing::~Shadowing() {
	Shutdown();
}