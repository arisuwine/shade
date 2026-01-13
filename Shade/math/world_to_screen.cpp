#include "world_to_screen.hpp"

#include "../sdk/sdk.hpp"
#include "../sdk/math/matrix.hpp"
#include "../sdk/math/vector.hpp"

bool math::WorldToScreen(const vector_3d& in, vector_2d& out) {
    matrix4x4 matrix_v = g_ViewMatrix->m_Matrix;

    if (in.is_zero())
        return 0;

    out.x = matrix_v.matrix[0][0] * in.x + matrix_v.matrix[0][1] * in.y + matrix_v.matrix[0][2] * in.z + matrix_v.matrix[0][3];
    out.y = matrix_v.matrix[1][0] * in.x + matrix_v.matrix[1][1] * in.y + matrix_v.matrix[1][2] * in.z + matrix_v.matrix[1][3];

    float w = matrix_v.matrix[3][0] * in.x + matrix_v.matrix[3][1] * in.y + matrix_v.matrix[3][2] * in.z + matrix_v.matrix[3][3];

    if (w < 0.01f)
        return 0;

    float inv_w = 1.0f / w;
    out.x *= inv_w;
    out.y *= inv_w;

    float x = 1600.0f * 0.5f;
    float y = 900.0f * 0.5f;

    x += 0.5f * out.x * 1600.0f + 0.5f;
    y -= 0.5f * out.y * 900.0f + 0.5f;

    out.x = x;
    out.y = y;

    return 1;
}