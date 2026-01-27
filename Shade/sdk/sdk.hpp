#pragma once
#include <d3d11.h>

#include "entities/CGameEntitySystem.hpp"

#include "interfaces/ViewMatrix.hpp"
#include "interfaces/CGlowObjectManager.hpp"
#include "interfaces/CShemaSystem.hpp"
#include "interfaces/IVEngineClient.hpp"
#include "interfaces/ICVar.hpp"
#include "interfaces/CViewRender.hpp"
#include "interfaces/ISource2Client.hpp"
#include "interfaces/IGameResourceService.hpp"

#include "services/CGlobalVarsBase.hpp"
#include "services/CNetworkClientService.hpp"

namespace interfaces {
	void Initialize();
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
inline CShemaSystem*			g_CSchemaSystem			= nullptr;
inline CGlobalVarsBase*			gpGlobals				= nullptr;
inline IVEngineClient*			g_EngineClient			= nullptr;
inline ICVar*					g_CVar					= nullptr;
inline CViewRender*				g_CViewRender			= nullptr;
inline ISource2Client*			g_Source2Client			= nullptr;
inline IGameResourceService*	g_GameResourceService	= nullptr;