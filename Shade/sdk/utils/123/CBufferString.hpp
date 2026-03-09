#pragma once

#include "tier0/platform.h"
#include "strtools.h"
#include "utlstring.h"

class CFormatStringElement;
class IFormatOutputStream;

#define Assert( _exp ) ((void)0)

/*
	Main idea of CBufferString is to provide stack allocated string
	with the ability to convert to the heap allocation if allowed.

	By default CBufferString provides 8 bytes of stack allocation and could be increased by
	using CBufferStringN<SIZE> where custom stack SIZE could be used.

	Example usage of CBufferStringN class:

	* Basic buffer allocation:
	```
		CBufferStringN<256> buff;
		buff.Insert(0, "Hello World!");
		printf("Result: %s\n", buff.Get());
	```
	additionaly the heap allocation of the buffer could be disabled. If the heap allocation is disabled and
	if the buffer capacity is not enough to perform the growing operation, the app would exit with an Assert;

	* Most, if not all the functions would ensure the buffer capacity and enlarge it when needed.
	In case of stack allocated buffers, if the requested size exceeds stack size, it would switch to heap allocation instead.
*/

class CBufferString
{
public:
	enum EAllocationOption_t
	{
		UNK1 = -1,
		UNK2 = 0,
		UNK3 = (1 << 1),
		UNK4 = (1 << 8),
		UNK5 = (1 << 9)
	};

	enum EAllocationFlags_t
	{
		LENGTH_MASK = (1 << 30) - 1,
		FLAGS_MASK = ~LENGTH_MASK,

		// Flags in m_nLength
		// Means it tried to grow larger than static size and heap allocation was disabled
		OVERFLOWED_MARKER = (1 << 30),
		// Means it owns the heap buffer and it needs to be cleaned up
		FREE_HEAP_MARKER = (1 << 31),

		// Flags in m_nAllocatedSize
		// Means it uses stack allocated buffer
		STACK_ALLOCATED_MARKER = (1 << 30),
		// Allows the buffer to grow beyond the static size on the heap
		ALLOW_HEAP_ALLOCATION = (1 << 31)
	};

public:
	CBufferString(bool bAllowHeapAllocation = true) :
		m_nLength(0),
		m_nAllocatedSize((bAllowHeapAllocation* ALLOW_HEAP_ALLOCATION) | STACK_ALLOCATED_MARKER | sizeof(m_szString)),
		m_pString(nullptr)
	{
	}

	CBufferString(const char* pString, bool bAllowHeapAllocation = true) :
		CBufferString(bAllowHeapAllocation)
	{
		Insert(0, pString);
	}

protected:
	CBufferString(size_t nAllocatedSize, bool bAllowHeapAllocation = true) :
		m_nLength(0),
		m_nAllocatedSize((bAllowHeapAllocation* ALLOW_HEAP_ALLOCATION) | STACK_ALLOCATED_MARKER | (nAllocatedSize + sizeof(m_szString))),
		m_pString(nullptr)
	{
		Assert(nAllocatedSize > 8);
	}

public:
	CBufferString(const CBufferString& other) : CBufferString() { *this = other; }
	CBufferString& operator=(const CBufferString& src)
	{
		Clear();
		Insert(0, src.Get());
		return *this;
	}

	~CBufferString() { Purge(); }

	void SetHeapAllocationState(bool state)
	{
		if (state)
			m_nAllocatedSize |= ALLOW_HEAP_ALLOCATION;
		else
			m_nAllocatedSize &= ~ALLOW_HEAP_ALLOCATION;
	}

	int AllocatedNum() const { return m_nAllocatedSize & LENGTH_MASK; }
	int Length() const { return m_nLength & LENGTH_MASK; }

	bool CanHeapAllocate() const { return (m_nAllocatedSize & ALLOW_HEAP_ALLOCATION) != 0; }
	bool IsStackAllocated() const { return (m_nAllocatedSize & STACK_ALLOCATED_MARKER) != 0; }
	bool ShouldFreeMemory() const { return (m_nLength & FREE_HEAP_MARKER) != 0; }
	bool IsOverflowed() const { return (m_nLength & OVERFLOWED_MARKER) != 0; }

	bool IsInputStringUnsafe(const char* pData) const
	{
		return ((void*)pData >= this && (void*)pData < &this[1]) ||
			(!IsAllocationEmpty() && pData >= Base() && pData < (Base() + AllocatedNum()));
	}

	bool IsAllocationEmpty() const { return AllocatedNum() == 0; }

protected:
	char* Base() { return IsStackAllocated() ? m_szString : (!IsAllocationEmpty() ? m_pString : nullptr); }
	const char* Base() const { return const_cast<CBufferString*>(this)->Base(); }

public:
	const char* Get() const { auto base = Base(); return base ? base : StringFuncs<char>::EmptyString(); }

	void Clear()
	{
		if (!IsAllocationEmpty())
			Base()[0] = '\0';

		m_nLength &= ~LENGTH_MASK;
	}

public:
	const char* AppendConcat(int, const char* const*, const int*, bool bIgnoreAlignment = false);
	const char* AppendConcat(const char*, const char*, ...) FMTFUNCTION(3, 4);
	const char* AppendConcatV(const char*, const char*, va_list, bool bIgnoreAlignment = false);
	const char* Concat(const char*, const char*, ...) FMTFUNCTION(3, 4);

	int AppendFormat(const char* pFormat, ...) FMTFUNCTION(2, 3);
	int AppendFormatV(const char* pFormat, va_list pData);

	const char* AppendRepeat(char cChar, int nChars, bool bIgnoreAlignment = false);

	// Given a path and a filename, composes "path\filename", inserting the (OS correct) separator if necessary
	const char* ComposeFileName(const char* pPath, const char* pFile, char cSeparator);

	const char* ConvertIn(unsigned int const* pData, int nSize, bool bIgnoreAlignment = false);
	const char* ConvertIn(wchar_t const* pData, int nSize, bool bIgnoreAlignment = false);

	// Make path end with extension if it doesn't already have an extension
	const char* DefaultExtension(const char* extension);

	// Does string end with 'pSuffix'? (case sensitive/insensitive variants)
	bool EndsWith(const char* pSuffix) const;
	bool EndsWith_FastCaseInsensitive(const char* pSuffix) const;

	// Ensures the nCapacity condition is met and grows the local buffer if needed.
	// Returns pResultingBuffer pointer to the newly allocated data, as well as resulting capacity that was allocated in bytes.
	int EnsureCapacity(int nCapacity, char** pResultingBuffer, bool bIgnoreAlignment = false, bool bForceGrow = false);
	int EnsureAddedCapacity(int nCapacity, char** pResultingBuffer, bool bIgnoreAlignment = false, bool bForceGrow = false);

	char* EnsureLength(int nCapacity, bool bIgnoreAlignment = false, int* pNewCapacity = nullptr);
	char* EnsureOwnedAllocation(CBufferString::EAllocationOption_t eAlloc);

	const char* EnsureTrailingSlash(char cSeparator, bool bDontAppendIfEmpty = true);

	const char* ExtendPath(const char* pPath, char cSeparator);

	const char* ExtractFileBase(const char* pPath);

	// Copy out the file extension into dest
	const char* ExtractFileExtension(const char* pPath);

	// Copy out the path except for the stuff after the final pathseparator
	const char* ExtractFilePath(const char* pPath, bool);


	const char* ExtractFirstDir(const char* pPath);

	// Force slashes of either type to be = separator character
	const char* FixSlashes(char cSeparator = CORRECT_PATH_SEPARATOR);

	// Fixes up a file name, removing dot slashes, fixing slashes, converting to lowercase, etc.
	const char* FixupPathName(char cSeparator);

	int Format(const char* pFormat, ...) FMTFUNCTION(2, 3);
	void FormatTo(IFormatOutputStream* pOutputStream, CFormatStringElement pElement) const;

protected:
	// Returns aligned size based on capacity requested
	static int GetAllocChars(int nSize, int nCapacity);

public:
	// Inserts the nCount bytes of data from pBuf buffer at nIndex position.
	// If nCount is -1, it would count the bytes of the input buffer manualy.
	// Returns the resulting char buffer (Same as to what CBufferString->Get() returns).
	const char* Insert(int nIndex, const char* pBuf, int nCount = -1, bool bIgnoreAlignment = false);

	char* GetInsertPtr(int nIndex, int nChars, bool bIgnoreAlignment = false, int* pNewCapacity = nullptr);
	char* GetReplacePtr(int nIndex, int nOldChars, int nNewChars, bool bIgnoreAlignment = false, int* pNewCapacity = nullptr);

	int GrowByChunks(int, int);

	// If pPath is a relative path, this function makes it into an absolute path
	// using the current working directory as the base, or pStartingDir if it's non-NULL.
	// Returns NULL if it runs out of room in the string, or if pPath tries to ".." past the root directory.
	const char* MakeAbsolutePath(const char* pPath, const char* pStartingDir);

	// Same as MakeAbsolutePath, but also does separator fixup
	const char* MakeFixedAbsolutePath(const char* pPath, const char* pStartingDir, char cSeparator = CORRECT_PATH_SEPARATOR);

	// Creates a relative path given two full paths
	// The first is the full path of the file to make a relative path for.
	// The second is the full path of the directory to make the first file relative to
	// Returns NULL if they can't be made relative (on separate drives, for example)
	const char* MakeRelativePath(const char* pFullPath, const char* pDirectory);

	// Copies data from pOther and then purges it
	void MoveFrom(CBufferString& pOther);

	void Purge(int nAllocatedBytesToPreserve = 0);

	char* Relinquish(CBufferString::EAllocationOption_t eAlloc);

	const char* RemoveAt(int nIndex, int nChars);
	const char* RemoveAtUTF8(int nByteIndex, int nCharacters);

	const char* RemoveDotSlashes(char cSeparator);
	int RemoveWhitespace();

	const char* RemoveFilePath();
	const char* RemoveFirstDir(CBufferString* pRemovedDir);
	const char* RemoveToFileBase();

	bool RemovePartialUTF8Tail(bool);
	const char* RemoveTailUTF8(int nIndex);

	int Replace(char cFrom, char cTo);
	int Replace(const char* pMatch, const char* pReplace, bool bDontUseStrStr = false);

	const char* ReplaceAt(int nIndex, int nOldChars, const char* pData, int nDataLen = -1, bool bIgnoreAlignment = false);
	const char* ReplaceAt(int nIndex, const char* pData, int nDataLen = -1, bool bIgnoreAlignment = false);

	const char* ReverseChars(int nIndex, int nChars);

	// Strips any current extension from path and ensures that extension is the new extension
	const char* SetExtension(const char* extension);

	char* SetLength(int nLen, bool bIgnoreAlignment = false, int* pNewCapacity = nullptr);
	void SetPtr(char* pBuf, int nBufferChars, int, bool, bool);

	// Frees the buffer (if it was heap allocated) and writes "~DSTRCT" to the local buffer.
	void SetUnusable();

	const char* ShortenPath(bool);

	bool StartsWith(const char* pMatch) const;
	bool StartsWith_FastCaseInsensitive(const char* pMatch) const;

	const char* StrAppendFormat(const char* pFormat, ...) FMTFUNCTION(2, 3);
	const char* StrFormat(const char* pFormat, ...) FMTFUNCTION(2, 3);

	const char* StripExtension();
	const char* StripTrailingSlash();

	void ToLowerFast(int nStart);
	void ToUpperFast(int nStart);

	const char* Trim(const char* pTrimChars = "\t\r\n ");
	const char* TrimHead(const char* pTrimChars = "\t\r\n ");
	const char* TrimTail(const char* pTrimChars = "\t\r\n ");

	const char* TruncateAt(int nIndex, bool bIgnoreAlignment = false);
	const char* TruncateAt(const char* pStr, bool bIgnoreAlignment = false);

	int UnicodeCaseConvert(int, EStringConvertErrorPolicy eErrorPolicy);

private:
	int m_nLength;
	int m_nAllocatedSize;

	union
	{
		char* m_pString;
		char m_szString[8];
	};
};

template<size_t SIZE>
class CBufferStringN : public CBufferString
{
public:
	static const size_t DATA_SIZE = ALIGN_VALUE(SIZE - sizeof(char[8]), 8);

	CBufferStringN(bool bAllowHeapAllocation = true) : CBufferString(DATA_SIZE, bAllowHeapAllocation), m_FixedData{} {}
	CBufferStringN(const char* pString, bool bAllowHeapAllocation = true) : CBufferStringN(bAllowHeapAllocation)
	{
		Insert(0, pString);
	}

	~CBufferStringN() { PurgeN(); }

	// Should be preferred over CBufferString::Purge as it preserves stack space correctly
	void PurgeN() { Purge(DATA_SIZE); }

private:
	char m_FixedData[DATA_SIZE];
};

// AMNOTE: CBufferStringN name is preferred to be used, altho CBufferStringGrowable is left as a small bcompat
template <size_t SIZE>
using CBufferStringGrowable = CBufferStringN<SIZE>;