#pragma once

#include <optional>
#include <cstring>
#include "assert.h"
//#include "../valve/utlrbtree.hpp"

#define Assert( x ) assert( x )

inline int V_strnicmp1(const char* s1, const char* s2, int n)
{
    Assert(n >= 0);
    Assert(n == 0 || s1 != NULL);
    Assert(n == 0 || s2 != NULL);

    while (n-- > 0)
    {
        int c1 = *s1++;
        int c2 = *s2++;

        if (c1 != c2)
        {
            if (c1 >= 'a' && c1 <= 'z')
                c1 -= ('a' - 'A');
            if (c2 >= 'a' && c2 <= 'z')
                c2 -= ('a' - 'A');
            if (c1 != c2)
                return c1 < c2 ? -1 : 1;
        }
        if (c1 == '\0')
            return 0; // null terminator hit - strings the same
    }

    return 0; // n characters compared the same
}

inline int V_stricmp1(const char* s1, const char* s2) { return V_strnicmp1(s1, s2, INT_MAX); }


typedef const char* PConstChar_t;

class CDefCaselessStringLess
{
public:
    CDefCaselessStringLess() {}
    CDefCaselessStringLess(int i) {}
    inline bool operator()(const PConstChar_t& lhs, const PConstChar_t& rhs) const { return (V_stricmp1(lhs, rhs) < 0); }
    inline bool operator!() const { return false; }
};

template <typename K, typename V, typename I = int, typename KL = StringLess>
class CUtlMap
{
public:
    struct Node_t
    {
        I m_left;
        I m_right;
        I m_parent;
        I m_tag;
        K m_key;
        V m_value;
    };

    auto begin() const { return m_data; }
    auto end() const { return m_data + m_size; }

    std::optional<V> FindByKey(K key) const
    {
        int current = m_root;
        KL less;
        while (current != -1)
        {
            const Node_t& element = m_data[current];
            if (element.m_key == nullptr)
                break;
            if (less(element.m_key, key))
                current = element.m_right;
            else if (less(key, element.m_key))
                current = element.m_left;
            else
                return element.m_value;
        }
        return {};
    }
    char pad0[0x8];
    char pad1[0x8];
    Node_t* m_data;
    char pad2[0x8];  // no idea
    int m_root;
    int m_size;
    char pad3[0x8];  // no idea
};

struct StringLess {
    bool operator()(const char* a, const char* b) const {

        return _stricmp(a, b) < 0;
    }
};



