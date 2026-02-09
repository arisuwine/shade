#pragma once
#include <memory>
#include <type_traits>
#include <string>
#include <format>
#include <functional>

#include "minhook.h"

#include "../utils/vmt/vmt.hpp"

class IHookBase {
protected:
	void*		m_pDetour;

	bool		m_bIsEnabled;
	std::string m_szName;

	std::function<void()> m_onCreate;
	std::function<void()> m_onDestroy;

public:
	IHookBase() : m_pDetour(nullptr), m_bIsEnabled(false), m_szName(""), m_onCreate(nullptr), m_onDestroy(nullptr) {};

	bool IsEnabled() const { return m_bIsEnabled; }
	std::string_view GetName() const { return m_szName.data(); }

	virtual ~IHookBase() = default;
};

namespace hooks {
	template <typename Func>
	void AddDetour(std::string_view szName, void* pTarget, void* pDetour, Func* ppOriginal, std::function<void()> onCreate = nullptr, std::function<void()> onDestroy = nullptr);
}

class CDetourHook : public IHookBase {
private:
	void* m_pTarget;
	void* m_pOriginal;

	template <typename Func>
	friend void hooks::AddDetour(std::string_view szName, void* pTarget, void* pDetour, Func* ppOriginal, std::function<void()> onCreate, std::function<void()> onDestroy);

public:
	static bool Initialize();
	static bool Uninitialize();

	CDetourHook(std::string_view szName, void* pTarget, void* pDetour, std::function<void()> onCreate = nullptr, std::function<void()> onDestroy = nullptr);

	template <typename Func>
	Func GetOriginal() { return reinterpret_cast<Func>(m_pOriginal); }
	 
	bool Enable();
	bool Disable();

	virtual ~CDetourHook();
};

class CVMTHook : public IHookBase {
private:
	vmt::Shadowing m_Shadowing;

public:
	CVMTHook(std::string_view szName, void* pObject, std::function<void()> onCreate = nullptr, std::function<void()> onDestroy = nullptr);

	template <typename Func>
	Func Enable(size_t iFuncIndex, void* pDetour) {
		if (!IsEnabled())
			return nullptr;

		return m_Shadowing.Hook<Func>(iFuncIndex, pDetour);
	}

	template <typename Func>
	Func GetOriginal(size_t iFuncIndex) { return m_Shadowing.Get<Func>(iFuncIndex); }

	bool Disable(size_t iFuncIndex);

	virtual ~CVMTHook() {
		if (IsEnabled() && m_onDestroy)
			m_onDestroy();

		lg::Success("[-]", "Hook %s removed successfully.\n", m_szName.data());
	}
};