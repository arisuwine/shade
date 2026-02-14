#include "vmt.hpp"

vmt::Shadowing::Shadowing(void* object) : m_pObject(nullptr), m_pVftOrig(nullptr), m_pUserVft(nullptr), m_iVftSize(0), m_bIsInit(FALSE) {
	if (!object) {
		lg::Warn("[VMT]", "Target object is nullptr\n");
		return;
	}
	
	m_pObject = object;
	m_pVftOrig = *reinterpret_cast<uintptr_t**>(m_pObject);

	m_iVftSize = GetFunctionCount();
	if (m_iVftSize == 0) {
		lg::Warn("[VMT]", "Failed to calculate VTable size (count is 0) at address: 0x%p.\n", m_pVftOrig);
		return;
	}

	m_pShadowAlloc = new uintptr_t[m_iVftSize + 1];
	memcpy(m_pShadowAlloc, m_pVftOrig - 1, (m_iVftSize + 1) * sizeof(void*));

	m_pUserVft = m_pShadowAlloc + 1;
	*reinterpret_cast<void**>(object) = m_pUserVft;

	m_bIsInit = true;
}

bool vmt::Shadowing::Rebase(void* pObject, bool RestoreOld) {
	if (!m_bIsInit) {
		lg::Info("[VMT]", "Shadowing not initialized.\n");
		return false;
	}

	if (!pObject) {
		lg::Warn("[VMT]", "Target object is nullptr\n");
		return false;
	}

	if (RestoreOld && m_pObject)
		*reinterpret_cast<uintptr_t**>(m_pObject) = m_pVftOrig;

	std::unordered_map<size_t, uintptr_t> Detours;
	for (auto& [index, func] : m_OriginalFuncs)
		Detours[index] = m_pUserVft[index];

	uintptr_t* pVftOrig = *reinterpret_cast<uintptr_t**>(pObject);
	uintptr_t* pShadowAlloc = new uintptr_t[m_iVftSize + 1];
	memcpy(pShadowAlloc, pVftOrig - 1, (m_iVftSize + 1) * sizeof(void*));

	uintptr_t* pUserVft = pShadowAlloc + 1;

	std::unordered_map<size_t, uintptr_t> OriginalFuncs;
	for (auto& [index, func] : Detours) {
		OriginalFuncs[index] = pUserVft[index];
		pUserVft[index] = func;
	}

	*reinterpret_cast<void**>(pObject) = pUserVft;

	delete[] m_pShadowAlloc;

	m_pObject = pObject;
	m_pVftOrig = pVftOrig;
	m_pShadowAlloc = pShadowAlloc;
	m_pUserVft = pUserVft;
	m_OriginalFuncs = OriginalFuncs;

	return true;
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
		lg::Warn("[VMT]", "Unhook failed: Index out of bounds (Max: %zu)\n", m_iVftSize);
		return false;
	}


	if (m_OriginalFuncs.find(index) == m_OriginalFuncs.end()) {
		lg::Warn("[VMT]", "Unhook failed: No original function found for this index.\n");
		return false;
	}
	
	m_pUserVft[index] = m_OriginalFuncs[index];
	m_OriginalFuncs.erase(index);
	return false;
}

bool vmt::Shadowing::UnHookAll() {
	if (!m_bIsInit)
		return false;

	for (auto& [index, func] : m_OriginalFuncs)
		m_pUserVft[index] = func;

	m_OriginalFuncs.clear();
	return TRUE;
}

bool vmt::Shadowing::Shutdown() {
	if (!m_bIsInit) {
		lg::Info("[VMT]", "Shadowing not initialized.\n");
		return true;
	}
	
	*reinterpret_cast<uintptr_t**>(m_pObject) = m_pVftOrig;

	m_pObject = nullptr;
	m_pVftOrig = nullptr;

	delete[] m_pShadowAlloc;
	m_pShadowAlloc = nullptr;
	m_pUserVft = nullptr;

	m_OriginalFuncs.clear();
	m_bIsInit = false;
	return true;
}

vmt::Shadowing::~Shadowing() {
	Shutdown();
}