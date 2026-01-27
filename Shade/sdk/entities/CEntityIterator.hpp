#pragma once
#include "CEntityIdentity.hpp"

template <typename T, bool ByClass = 0>
class CEntityIterator {
private:
	class Iterator {
	private:
		CEntityIdentity* m_pIdentity;

	public:
		Iterator(CEntityIdentity* ptr) : m_pIdentity(ptr) {}

		T* operator*() const {
			return m_pIdentity->m_pInstance<T>();
		}

		T* operator->() const {
			return m_pIdentity->m_pInstance<T>();
		}

		Iterator& operator++() {
			m_pIdentity = ByClass ? m_pIdentity->m_pNextByClass : m_pIdentity->m_pNext;
			return *this;
		}

		Iterator operator++(int) {
			Iterator temp = *this;
			++*this;
			return temp;
		}

		Iterator& operator--() {
			m_pIdentity = ByClass ? m_pIdentity->m_pPrevByClass : m_pIdentity->m_pPrev;
			return *this;
		}

		Iterator operator--(int) {
			Iterator temp = *this;
			--*this;
			return temp;
		}

		bool operator!=(const Iterator& other) const {
			return m_pIdentity != other.m_pIdentity;
		}

		auto operator<=>(const Iterator&) const = default;
	};

	CEntityIdentity* m_pIdentity;

public:
	CEntityIterator(CEntityIdentity* ptr) : m_pIdentity(ptr) {}

	Iterator begin() const {
		return Iterator(m_pIdentity);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}
};

