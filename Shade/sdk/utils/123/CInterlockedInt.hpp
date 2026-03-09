#pragma once
#include <cstdint>

template <typename T>
class CInterlockedIntT {
public:
    CInterlockedIntT() : m_value(0) {
        static_assert(sizeof(T) == sizeof(int32_t));
    }
    explicit CInterlockedIntT(T value) : m_value(value) {}

    T operator()() const {
        return m_value;
    }
    /* implicit */ operator T() const {
        return m_value;
    }

    bool operator!() const {
        return (m_value == 0);
    }
    bool operator==(T rhs) const {
        return (m_value == rhs);
    }
    bool operator!=(T rhs) const {
        return (m_value != rhs);
    }

    T Get() {
        return m_value;
    }

private:
    volatile T m_value;
};

using CInterlockedInt = CInterlockedIntT<int>;
using CInterlockedUInt = CInterlockedIntT<unsigned>;