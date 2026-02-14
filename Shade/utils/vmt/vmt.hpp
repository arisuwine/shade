#pragma once
#include <Windows.h>
#include <unordered_map>

#include "../debug.hpp"

#define CALL_VIRTUAL(instance, type, index, ...) \
	vmt::CallVirtual<type>(instance, index, __VA_ARGS__)

namespace vmt {
	template <typename T>
	T GetVirtual(void* instance, size_t index) {
		if (!instance)
			return T{};

		void** vft = *static_cast<void***>(instance);
		if (!vft)
			return T{};

		T method = reinterpret_cast<T>(vft[index]);
		if (!method)
			return T{};

		return method;
	}

	template <typename T, typename... Args>
	T CallVirtual(void* instance, size_t index, Args... args) {
		auto pFunc = GetVirtual<T(__fastcall*)(void*, Args...)>(instance, index);
		if (!pFunc)
			return T{};

		return pFunc(instance, args...);
	}

	//template <typename T, typename... Args>
	//T call_virtual_stret(void* instance, size_t index, Args... args) {
	//	T result;

	//	using fn = void(__fastcall*)(void*, T*, args);

	//	auto pFunc = vmt::get_virtual<fn>(instance, index);
	//	if (pFunc)
	//		pFunc(this, &result, args);

	//	return result;
	//}

	class Shadowing {
	private:
		void*		m_pObject;
		uintptr_t*	m_pVftOrig;
		uintptr_t*	m_pShadowAlloc;
		uintptr_t*	m_pUserVft;

		size_t		m_iVftSize;
		bool		m_bIsInit;

		std::unordered_map<size_t, uintptr_t> m_OriginalFuncs;

		size_t	GetFunctionCount();

	public:
		Shadowing() : m_pObject(nullptr), m_pVftOrig(nullptr), m_pUserVft(nullptr), m_iVftSize(0), m_bIsInit(FALSE) {};
		Shadowing(void* object); 
		~Shadowing();

		template <typename T>
		T			Hook(size_t index, void* hook_func);

		template <typename T>
		T			Get(size_t index) const;

		bool		Rebase(void* object, bool RestoreOld = false);

		bool		UnHook(size_t index);
		bool		UnHookAll();
		bool		Shutdown();

		inline bool IsInitialized() const { return m_bIsInit; };
	};
}

template <typename T>
T vmt::Shadowing::Hook(size_t index, void* hook_func) {
	if (!hook_func) {
		lg::Warn("[VMT]", "Hook failed: Hook function pointer is null.\n");
		return nullptr;
	}

	if (!m_bIsInit)
		return nullptr;

	if (index >= m_iVftSize) {
		lg::Warn("[VMT]", "Hook failed: Index %zu out of bounds (Size: %zu)\n", index, m_iVftSize);
		return nullptr;
	}

	if (m_OriginalFuncs.find(index) == m_OriginalFuncs.end())
		m_OriginalFuncs[index] = m_pUserVft[index];

	m_pUserVft[index] = reinterpret_cast<uintptr_t>(hook_func);

	return reinterpret_cast<T>(m_OriginalFuncs[index]);
}

template <typename T>
T vmt::Shadowing::Get(size_t index) const {
	if (!m_bIsInit)
		return nullptr;

	auto it = m_OriginalFuncs.find(index);
	if (it != m_OriginalFuncs.end())
		return reinterpret_cast<T>(it->second);
}