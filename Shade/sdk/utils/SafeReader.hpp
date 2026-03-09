#pragma once
#include <Windows.h>
#include <optional>

namespace SafeReader {
    template <typename T>
    __declspec(noinline) bool IsValid(void* p, size_t offset = 0) {
        __try {
            uintptr_t target = reinterpret_cast<uintptr_t>(p) + offset;
            T result = *reinterpret_cast<T*>(target);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }
    }

    static __declspec(noinline) bool IsValidString(const char* str) {
        __try {
            for (size_t i = 0; i < 256; i++)
                if (str[i] == '\0')
                    return true;

            return false;
        }
        __except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION
            ? EXCEPTION_EXECUTE_HANDLER
            : EXCEPTION_CONTINUE_SEARCH) {
            return false;
        }
    }

    //template <typename T>
    //std::optional<T> SafeRead(void* p, size_t offset = 0) {
    //    T buffer;
    //    if (IsValid<T>(p, offset, &buffer))
    //        return buffer;

    //    return std::nullopt;
    //}

    //static std::optional<std::string_view> SafeReadString(const char* str) {
    //    if (IsValidString(str))
    //        return std::string_view(str);

    //    return std::nullopt;
    //}
}