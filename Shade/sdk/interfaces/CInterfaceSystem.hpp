#pragma once
#include <Windows.h>
#include <string_view>

#include "../offsets.hpp"

#include "../../utils/debug.hpp"

namespace CInterfaceSystem {
	template<typename T>
	static T* Get(const std::string_view& module_name, const std::string_view& interface_name){
		HMODULE hModule = GetModuleHandleA(module_name.data());

		if (!hModule)
		{
			return nullptr;
		}

		uintptr_t create_interface = reinterpret_cast<uintptr_t>(GetProcAddress(hModule, "CreateInterface"));

		if (!create_interface)
		{
			return nullptr;
		}

		using interface_callback_fn = void* (__cdecl*)();

		typedef struct _interface_reg_t
		{
			interface_callback_fn callback;
			const char* name;
			_interface_reg_t* flink;
		} interface_reg_t;

		interface_reg_t* interface_list = *reinterpret_cast<interface_reg_t**>(RESOLVE_RIP(uintptr_t, create_interface));

		if (!interface_list)
		{
			return nullptr;
		}

		for (interface_reg_t* it = interface_list; it; it = it->flink)
		{
			if (!strcmp(it->name, interface_name.data()))
			{
				lg::Success("[+]", "Successfully found %s at %p\n", interface_name.data(), it->callback());
				return reinterpret_cast<T*>(it->callback());
			}
		}

		lg::Error("", "Failed to initialize %s in %s\n", interface_name.data(), module_name.data());
		return nullptr;
	}
}