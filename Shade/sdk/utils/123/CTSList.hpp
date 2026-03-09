#pragma once
#include <cstdint>
#include <emmintrin.h>

#define DECL_ALIGN(x) __declspec(align(x))

constexpr auto TSLIST_HEAD_ALIGNMENT = 16;
constexpr auto TSLIST_NODE_ALIGNMENT = 16;

#ifdef _MSC_VER
#define TSLIST_HEAD_ALIGN DECL_ALIGN(TSLIST_HEAD_ALIGNMENT)
#define TSLIST_NODE_ALIGN DECL_ALIGN(TSLIST_NODE_ALIGNMENT)
#define TSLIST_HEAD_ALIGN_POST
#define TSLIST_NODE_ALIGN_POST
#elif defined(__GNUC__)
#define TSLIST_HEAD_ALIGN
#define TSLIST_NODE_ALIGN
#define TSLIST_HEAD_ALIGN_POST DECL_ALIGN(TSLIST_HEAD_ALIGNMENT)
#define TSLIST_NODE_ALIGN_POST DECL_ALIGN(TSLIST_NODE_ALIGNMENT)
#else
#error
#endif

struct TSLIST_NODE_ALIGN TSLNodeBase_t {
    TSLNodeBase_t* Next; // name to match Windows
} TSLIST_NODE_ALIGN_POST;

typedef __m128i int128;

union TSLIST_HEAD_ALIGN TSLHead_t {
    struct Value_t {
        TSLNodeBase_t* Next;
        std::int16_t Depth;
        std::int16_t Sequence;
        std::int32_t Padding;
    } value;

    struct Value32_t {
        TSLNodeBase_t* Next_do_not_use_me;
        std::int32_t DepthAndSequence;
    } value32;

    int128 value64x128;
} TSLIST_HEAD_ALIGN_POST;

class TSLIST_HEAD_ALIGN CTSListBase {
public:
    [[nodiscard]] int Count() const {
        return m_Head.value.Depth;
    }

public:
    TSLHead_t m_Head;
} TSLIST_HEAD_ALIGN_POST;
