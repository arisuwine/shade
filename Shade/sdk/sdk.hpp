#pragma once

#include "interfaces/CGameEntitySystem.hpp"
#include "interfaces/ViewMatrix.hpp"
#include "interfaces/CNetworkClientService.hpp"

namespace interfaces {
	void initialize();
	void dump();
}

inline CGameEntitySystem*		g_CGameEntitySystem		= nullptr;
inline ViewMatrix*				g_ViewMatrix			= nullptr;
inline CNetworkClientService*	g_CNetworkClientService = nullptr;