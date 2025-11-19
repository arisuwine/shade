#include "detour_hook.h"
#include <cmath>

using Type = __int64 __fastcall(__int64, __int64);

__int64(__fastcall* prob_ViewMatrixSetupOrig)(__int64 a1, __int64 a2);

void v_sincosf(float x, float* sin_val, float* cos_val) {
	*sin_val = sinf(x);
	*cos_val = cosf(x);
}

std::ofstream log_addr;
__int64 __fastcall prob_ViewMatrixSetup(__int64 a1, __int64 a2) {
	
	float v3 = *(float*)(a1), v4 = *(float*)(a1);


	float value = *reinterpret_cast<float*>(view_matrix_addr);
	LOG("Value: %f\n", value);
	
	float v14, v17, v15, v18, v16, v19;

	v_sincosf(*(float*)(a1), &v14, &v17);
	v_sincosf(v3, &v15, &v18);
	v_sincosf(v4, &v16, &v19);
	
	//LOG("Start\n");
	if ((v18 * v17) == value)
		LOG("a1: %11x, a2: %11x", a1, a2);

	return prob_ViewMatrixSetupOrig(a1, a2);
}

uintptr_t view_matrix_addr;
void hook() {
	HMODULE module = GetModuleHandleA("client.dll");
	MODULEINFO info = { 0 };
	if (!GetModuleInformation(GetCurrentProcess(), module, &info, sizeof(MODULEINFO))) {
		return;
	}

	uintptr_t address = reinterpret_cast<uintptr_t>(info.lpBaseOfDll) + 0x11b9240;
	if (!address) {
		LOG("Invalid address\n");
		return;
	}

	view_matrix_addr = reinterpret_cast<uintptr_t>(info.lpBaseOfDll) + 0x1E32A88;

	prob_ViewMatrixSetupOrig = (Type*)address;
}