#pragma once
#include "CEntityIdentity.hpp"

template <typename T, bool ByClass = 0>
class CEntityIterator {
private:
	class Iterator {
	private:
		CEntityIdentity* identity;

	public:
		Iterator(CEntityIdentity* ptr) : identity(ptr) {}

		T* operator*() const {
			return identity->m_pInstance<T>();
		}

		T* operator->() const {
			return identity->m_pInstance<T>();
		}

		Iterator& operator++() {
			identity = ByClass ? identity->m_pNextByClass : identity->m_pNext;
			return *this;
		}

		Iterator operator++(int) {
			Iterator temp = *this;
			++*this;
			return temp;
		}

		Iterator& operator--() {
			identity = ByClass ? identity->m_pPrevByClass : identity->m_pPrev;
			return *this;
		}

		Iterator operator--(int) {
			Iterator temp = *this;
			--*this;
			return temp;
		}

		auto operator<=>(const Iterator&) const = default;
	};

	CEntityIdentity* identity;

public:
	CEntityIterator(CEntityIdentity* ptr) : identity(ptr) {}

	Iterator begin() const {
		return Iterator(identity);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}
};

