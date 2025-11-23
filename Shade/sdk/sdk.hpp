#pragma once

#include "interfaces/CGameEntitySystem.hpp"
#include "interfaces/ViewMatrix.hpp"
#include "interfaces/CCSPlayerController.hpp"

namespace interfaces {
	void initialize();
	void dump();
}

inline CGameEntitySystem*	g_CGameEntitySystem		= nullptr;
inline ViewMatrix*			g_ViewMatrix			= nullptr;