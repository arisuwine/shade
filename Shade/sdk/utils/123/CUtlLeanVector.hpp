#pragma once
#include <limits>

#define Assert( _exp ) ((void)0)

template <typename T, typename I>
class CUtlLeanVectorBase {
public:
	enum : I
	{
		EXTERNAL_BUFFER_MARKER = (I{ 1 } << (std::numeric_limits<I>::digits - 1))
	};

	struct {
		I m_nCount;
		I m_nAllocated;
		T* m_pElements;
	};

	bool IsIdxValid(I i) const { return (i >= 0) && (i < m_nCount); }

	int NumAllocated() const { return (m_nAllocated & (~EXTERNAL_BUFFER_MARKER)); }

	T* Base();
	const T* Base() const;
};

template <typename T, typename I>
inline T* CUtlLeanVectorBase<T, I>::Base()
{
	return NumAllocated() ? m_pElements : nullptr;
}

template<typename T, class I>
inline const T* CUtlLeanVectorBase<T, I>::Base() const
{
	return NumAllocated() ? m_pElements : nullptr;
}

template<typename B, typename T, typename I>
class CUtlLeanVectorImpl : public B {
public:
	using ElemType_t	= T;
	using IndexType_t	= I;

	class Iterator_t {
	public:
		Iterator_t(I i) : index(i) {}
		IndexType_t index;

		bool operator==(const Iterator_t it) const { return index == it.index; }
		bool operator!=(const Iterator_t it) const { return index != it.index; }
	};

	ElemType_t& operator[](const Iterator_t& it) { return Element(it.index); }
	const ElemType_t& operator[](const Iterator_t& it) const { return Element(it.index); }

	// element access
	T& operator[](int i);
	const T& operator[](int i) const;
	T& Element(int i);
	const T& Element(int i) const;
	T& Head();
	const T& Head() const;
	T& Tail();
	const T& Tail() const;

	// Returns the number of elements in the vector
	int Count() const;

	static const I INVALID_INDEX = (I)-1; // For use with COMPILE_TIME_ASSERT
	static I InvalidIndex() { return INVALID_INDEX; }
	bool IsIdxAfter(I i, const Iterator_t& it) const { return i > it.index; }
};

//-----------------------------------------------------------------------------
// element access
//-----------------------------------------------------------------------------
template<typename B, typename T, typename I>
inline T& CUtlLeanVectorImpl<B, T, I>::operator[](int i)
{
	Assert(i < this->m_nCount);
	return this->Base()[i];
}

template<typename B, typename T, typename I>
inline const T& CUtlLeanVectorImpl<B, T, I>::operator[](int i) const
{
	Assert(i < this->m_nCount);
	return this->Base()[i];
}

template<typename B, typename T, typename I>
inline T& CUtlLeanVectorImpl<B, T, I>::Element(int i)
{
	Assert(i < this->m_nCount);
	return this->Base()[i];
}

template<typename B, typename T, typename I>
inline const T& CUtlLeanVectorImpl<B, T, I>::Element(int i) const
{
	Assert(i < this->m_nCount);
	return this->Base()[i];
}

template<typename B, typename T, typename I>
inline T& CUtlLeanVectorImpl<B, T, I>::Head()
{
	Assert(this->m_nCount > 0);
	return this->Base()[0];
}

template<typename B, typename T, typename I>
inline const T& CUtlLeanVectorImpl<B, T, I>::Head() const
{
	Assert(this->m_nCount > 0);
	return this->Base()[0];
}

template<typename B, typename T, typename I>
inline T& CUtlLeanVectorImpl<B, T, I>::Tail()
{
	Assert(this->m_nCount > 0);
	return this->Base()[this->m_nCount - 1];
}

template<typename B, typename T, typename I>
inline const T& CUtlLeanVectorImpl<B, T, I>::Tail() const
{
	Assert(this->m_nCount > 0);
	return this->Base()[this->m_nCount - 1];
}

//-----------------------------------------------------------------------------
// Count
//-----------------------------------------------------------------------------
template<typename B, typename T, typename I>
inline int CUtlLeanVectorImpl<B, T, I>::Count() const
{
	return this->m_nCount;
}

template < typename T, typename I = short>
using CUtlLeanVector = CUtlLeanVectorImpl<CUtlLeanVectorBase<T, I>, T, I>;