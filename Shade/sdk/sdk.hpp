#pragma once
#include <d3d11.h>

#include "interfaces/CGameEntitySystem.hpp"
#include "interfaces/ViewMatrix.hpp"
#include "interfaces/CNetworkClientService.hpp"
#include "interfaces/CGlowObjectManager.hpp"

namespace interfaces {
	void initialize();
	void dump();
}

// D3D11
inline ID3D11Device*			g_Device				= nullptr;
inline ID3D11DeviceContext*		g_DeviceContext			= nullptr;
inline ID3D11RenderTargetView*	g_TargetView			= nullptr;

// In-Game Interfaces
inline CGlowObjectManager*		g_CGlowObjectManager	= nullptr;
inline CGameEntitySystem*		g_CGameEntitySystem		= nullptr;
inline ViewMatrix*				g_ViewMatrix			= nullptr;
inline CNetworkClientService*	g_CNetworkClientService = nullptr;