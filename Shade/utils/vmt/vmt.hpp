#pragma once

#define CALL_VIRTUAL(instance, type, index, ...) \
	vmt::call_virtual<type>(instance, index, __VA_ARGS__)

namespace vmt {
	template <typename T>
	T get_virtual(void* instance, size_t index) {
		if (!instance)
			return T{};

		void** vft = *static_cast<void***>(instance);
		if (!vft)
			return T{};

		T method = reinterpret_cast<T>(vft[index]);
		if (!method)
			return T{};

		return method;
	}

	template <typename T, typename... Args>
	T call_virtual(void* instance, size_t index, Args... args) {
		auto pFunc = get_virtual<T(__fastcall*)(void*, Args...)>(instance, index);
		if (!pFunc)
			return T{};

		return pFunc(instance, args...);
	}

	//template <typename T, typename... Args>
	//T call_virtual_stret(void* instance, size_t index, Args... args) {
	//	T result;

	//	using fn = void(__fastcall*)(void*, T*, args);

	//	auto pFunc = vmt::get_virtual<fn>(instance, index);
	//	if (pFunc)
	//		pFunc(this, &result, args);

	//	return result;
	//}
}