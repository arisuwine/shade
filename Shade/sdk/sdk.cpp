#include "sdk.hpp"

#include "modules.hpp"
#include "signatures.hpp"

void interfaces::initialize() {
	#define GET_OPERAND_EX(type, addr, offset, size) reinterpret_cast<type*>(addr + *((int32_t*)(addr + offset)) + size)
	#define GET_OPERAND(type, addr) GET_OPERAND_EX(type, addr, 3, 7)
	#define DEREFERENCE(type, addr) *reinterpret_cast<type**>(GET_OPERAND(type, addr))

	g_CGameEntitySystem		= DEREFERENCE(CGameEntitySystem,		modules::client.find(GAME_ENTITY_SYSTEM));
	g_ViewMatrix			= GET_OPERAND(ViewMatrix,				modules::client.find(VIEW_MATRIX));
	g_CNetworkClientService = GET_OPERAND(CNetworkClientService,	modules::engine2.find(NETWORK_CLIENT_SERVICE));
}

void interfaces::dump() {
	#define STRINGIFY(s) #s
	#define PRINT_INTERFACE(name) LOG("%25s: %p\n", STRINGIFY(name), name)

	PRINT_INTERFACE(g_CGameEntitySystem		);
	PRINT_INTERFACE(g_ViewMatrix			);
	PRINT_INTERFACE(g_CNetworkClientService	);
}