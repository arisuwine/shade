#include "view_matrix.hpp"

uintptr_t view_matrix::get_address() {
	uintptr_t address = handle + *((int32_t*)(handle + 3)) + 7;
	return address;
}

matrix4x4 view_matrix::get_matrix() {
	return *reinterpret_cast<matrix4x4*>(get_address());
}
