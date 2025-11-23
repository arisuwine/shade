#include "sdk.hpp"

void interfaces::initialize() {
	#define GET_OPERAND_EX(type, addr, offset, size) reinterpret_cast<type*>(addr + *((int32_t*)(addr + offset)) + size)
	#define GET_OPERAND(type, addr) GET_OPERAND_EX(type, addr, 3, 7)
	#define DEREFERENCE(type, addr) *reinterpret_cast<type**>(GET_OPERAND(type, addr))

	g_CGameEntitySystem		= DEREFERENCE(CGameEntitySystem,	modules::client.find(GAME_ENTITY_SYSTEM));
	g_ViewMatrix			= GET_OPERAND(ViewMatrix,			modules::client.find(VIEW_MATRIX));
}

void interfaces::dump() {
	#define STRINGIFY(s) #s
	#define PRINT_INTERFACE(name) LOG("%20s: %p\n", STRINGIFY(name), name)

	PRINT_INTERFACE(g_CGameEntitySystem	);
	PRINT_INTERFACE(g_ViewMatrix		);
}