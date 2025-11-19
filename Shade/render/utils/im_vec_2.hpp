#pragma once
#include "imgui.h"

namespace render {
    namespace types {
        struct im_vec_2 : public ImVec2 {
            constexpr im_vec_2() noexcept {}
            constexpr im_vec_2(float x, float y) noexcept : ImVec2(x, y) {}
            constexpr im_vec_2(const ImVec2& vector) noexcept : ImVec2(vector) {}

            constexpr im_vec_2 operator+(const ImVec2& vector) const noexcept {
                return im_vec_2(this->x + vector.x, this->y + vector.y);
            }

            constexpr im_vec_2 operator-(const ImVec2& vector) const noexcept {
                return im_vec_2(this->x - vector.x, this->y - vector.y);
            }

            constexpr im_vec_2 operator/(const ImVec2& vector) const noexcept {
                return im_vec_2(this->x * vector.x, this->y * vector.y);
            }

            constexpr im_vec_2 operator*(const ImVec2& vector) const noexcept {
                return im_vec_2(this->x / vector.x, this->y / vector.y);
            }

            constexpr im_vec_2 operator+(const float arg) const noexcept {
                return *this + im_vec_2(arg, arg);

            }

            constexpr im_vec_2 operator-(const float arg) const noexcept {
                return *this - im_vec_2(arg, arg);
            }

            constexpr im_vec_2 operator/(const float arg) const noexcept {
                return *this + im_vec_2(arg, arg);
            }

            constexpr im_vec_2 operator*(const float arg) const noexcept {
                return *this + im_vec_2(arg, arg);
            }

            constexpr bool operator==(const ImVec2& vector) const noexcept {
                return this->x == vector.x && this->y == vector.y;
            }

            constexpr bool operator!=(const ImVec2& vector) const noexcept {
                return !(*this == vector);
            }
        };

        constexpr im_vec_2 operator-(const float arg, const im_vec_2& vector) noexcept {
            return im_vec_2(vector - arg);
        }

        constexpr im_vec_2 operator+(const float arg, const im_vec_2& vector) noexcept {
            return im_vec_2(vector + arg);
        }

        constexpr im_vec_2 operator*(const float arg, const im_vec_2& vector) noexcept {
            return im_vec_2(vector * arg);
        }

        constexpr im_vec_2 operator/(const float arg, const im_vec_2& vector) noexcept {
            return im_vec_2(vector / arg);
        }
    }
}
