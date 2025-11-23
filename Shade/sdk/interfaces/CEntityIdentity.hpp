#pragma once
#include <windows.h>

#include "../offsets.hpp"

class CEntityIdentity {
public:
	CEntityIdentity() = delete;

	template <typename T>
	T* m_pInstance() const {
		return *reinterpret_cast<T**>(THIS_ADDR);
	}

	const char* m_name() const {
		return *reinterpret_cast<const char**>(THIS_ADDR + offsets::CEntityIdentity::m_name);
	}

	CEntityIdentity* m_pPrev() const {
		return *reinterpret_cast<CEntityIdentity**>(THIS_ADDR + offsets::CEntityIdentity::m_pPrev);
	}

	CEntityIdentity* m_pNext() const {
		return *reinterpret_cast<CEntityIdentity**>(THIS_ADDR + offsets::CEntityIdentity::m_pNext);
	}

	CEntityIdentity* m_pPrevByClass() const {
		return *reinterpret_cast<CEntityIdentity**>(THIS_ADDR + offsets::CEntityIdentity::m_pPrevByClass);
	}

	CEntityIdentity* m_pNextByClass() const {
		return *reinterpret_cast<CEntityIdentity**>(THIS_ADDR + offsets::CEntityIdentity::m_pNextByClass);
	}
};