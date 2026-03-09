#pragma once
#include <cstdint>


#include "CUtlLeanVector.hpp"

template <class I>
struct UtlRBTreeLinks_t {
	I m_Left;
	I m_Right;
	I m_Parent;
	I m_Tag;
};

template <class T, class I>
struct UtlRBTreeNode_t : public UtlRBTreeLinks_t<I> {
	T m_Data;
};

template <typename T, typename I = uint16_t, typename L = bool(*)(const T&, const T&), typename M = CUtlLeanVector<UtlRBTreeNode_t<T, I>, I>>
class CUtlRBTree {
public:
	using KeyType_t		= T;
	using ElemType_t	= T;
	using IndexType_t	= I;
	using LessFunc_t	= L;
	using Memory_t		= M;

	using Node_t		= UtlRBTreeNode_t<T, I>;
	using Links_t		= UtlRBTreeLinks_t<I>;

protected:
	enum NodeColor_t {
		RED = 0,
		BLACK
	};

	Links_t const& Links(I i) const {
		static Links_t s_Sentinel = { InvalidIndex(), InvalidIndex(), InvalidIndex(), CUtlRBTree<T, I, L, M>::BLACK };

		return (i != InvalidIndex()) ? *(Links_t*)&m_Elements[i] : *(Links_t*)&s_Sentinel;
	}

	Links_t& Links(I i) {
		return *(Links_t*)&m_Elements[i];
	}

public:
	LessFunc_t	m_LessFunc;

	Memory_t m_Elements;
	IndexType_t m_Root;
	IndexType_t m_NumElements;
	IndexType_t m_FirstTree;

	typename Memory_t::Iterator_t m_LastAlloc;

	Node_t* m_pElements;

public:
	ElemType_t& Element(IndexType_t i) {
		return m_Elements[i].m_Data;
	}

	ElemType_t const& Element(IndexType_t i) const {
		return m_Elements[i].m_Data;
	}

	ElemType_t& operator[](IndexType_t i) {
		return m_Elements[i].m_Data;
	}

	ElemType_t const& operator[](IndexType_t i) const {
		return m_Elements[i].m_Data;
	}

	IndexType_t Parent(IndexType_t i) const {
		return Links(i).m_Parent;
	}

	IndexType_t LeftChild(IndexType_t i) const {
		return Links(i).m_Left;
	}

	IndexType_t RightChild(IndexType_t i) const {
		return Links(i).m_Right;
	}

	bool IsLeftChild(IndexType_t i) const {
		return LeftChild(Parent(i)) == i;
	}

	bool IsRightChild(IndexType_t i) const {
		return RightChild(Parent(i)) == i;
	}

	Memory_t const& Elements() const {
		return m_Elements;
	}

	IndexType_t Find(KeyType_t const& search) const {
		IndexType_t current = m_Root;

		while (current != InvalidIndex()) {
			if (m_LessFunc(search, Element(current)))
				current = LeftChild(current);
			else if (m_LessFunc(Element(current), search))
				current = RightChild(current);
			else
				break;
		}
		return current;
	}

	static IndexType_t InvalidIndex() {
		return (IndexType_t)Memory_t::InvalidIndex();
	}

	bool  IsValidIndex(I i) const;

	// Iteration
	IndexType_t  FirstInorder() const;
	IndexType_t  NextInorder(IndexType_t i) const;
	IndexType_t  PrevInorder(IndexType_t i) const;
	IndexType_t  LastInorder() const;
};

static_assert(sizeof(CUtlRBTree<int>) == 0x28);

template < class T, class I, typename L, class M >
inline	bool CUtlRBTree<T, I, L, M>::IsValidIndex(I i) const
{
	if (!m_Elements.IsIdxValid(i))
		return false;

	if (m_Elements.IsIdxAfter(i, m_Elements.Count() - 1))
		return false; // don't read values that have been allocated, but not constructed

	return LeftChild(i) != i;
}

template < class T, class I, typename L, class M >
I CUtlRBTree<T, I, L, M>::FirstInorder() const
{
	I i = m_Root;
	while (LeftChild(i) != InvalidIndex())
		i = LeftChild(i);
	return i;
}

template < class T, class I, typename L, class M >
I CUtlRBTree<T, I, L, M>::NextInorder(I i) const
{
	Assert(IsValidIndex(i));

	if (RightChild(i) != InvalidIndex())
	{
		i = RightChild(i);
		while (LeftChild(i) != InvalidIndex())
			i = LeftChild(i);
		return i;
	}

	I parent = Parent(i);
	while (IsRightChild(i))
	{
		i = parent;
		if (i == InvalidIndex()) break;
		parent = Parent(i);
	}
	return parent;
}

template < class T, class I, typename L, class M >
I CUtlRBTree<T, I, L, M>::PrevInorder(I i) const
{
	Assert(IsValidIndex(i));

	if (LeftChild(i) != InvalidIndex())
	{
		i = LeftChild(i);
		while (RightChild(i) != InvalidIndex())
			i = RightChild(i);
		return i;
	}

	I parent = Parent(i);
	while (IsLeftChild(i))
	{
		i = parent;
		if (i == InvalidIndex()) break;
		parent = Parent(i);
	}
	return parent;
}

template < class T, class I, typename L, class M >
I CUtlRBTree<T, I, L, M>::LastInorder() const
{
	I i = m_Root;
	while (RightChild(i) != InvalidIndex())
		i = RightChild(i);
	return i;
}