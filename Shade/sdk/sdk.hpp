#pragma once
#include <d3d11.h>

#include "entities/CGameEntitySystem.hpp"

#include "interfaces/ViewMatrix.hpp"
#include "interfaces/CSchemaSystem.hpp"
#include "interfaces/IVEngineClient.hpp"
#include "interfaces/ICVar.hpp"
#include "interfaces/ISource2Client.hpp"
#include "interfaces/IGameResourceService.hpp"
#include "interfaces/IEngineServiceMgr.hpp"
#include "interfaces/INetworkClientService.hpp"

#include "services/CViewRender.hpp"
#include "services/CGlowObjectManager.hpp"
#include "services/CGlobalVarsBase.hpp"
#include "services/CCSGOInput.hpp"

namespace globals {
	void Initialize();
}

// D3D11
inline IDXGISwapChain*			g_pSwapChain				= nullptr;
inline ID3D11Device*			g_pDevice					= nullptr;
inline ID3D11DeviceContext*		g_pDeviceContext			= nullptr;
inline ID3D11RenderTargetView*	g_pTargetView				= nullptr;

inline INetworkClientService*	g_pNetworkClientService	= nullptr;
inline IVEngineClient*			g_pEngineClient				= nullptr;
inline ICVar*					g_pCVar						= nullptr;
inline ISchemaSystem*			g_pSchemaSystem				= nullptr;
inline ISource2Client*			g_pSource2Client			= nullptr;
inline IGameResourceService*	g_pGameResourceService		= nullptr;
inline IEngineServiceMgr*		g_pEngineServiceMgr			= nullptr;

inline CGlowObjectManager*		g_pCGlowObjectManager		= nullptr;
inline CGameEntitySystem*		g_pGameEntitySystem		= nullptr;
inline ViewMatrix*				g_pViewMatrix				= nullptr;
inline CGlobalVarsBase*			g_pGlobalVars				= nullptr;
inline CViewRender*				g_pViewRender				= nullptr;
inline CCSGOInput*				g_pCSGOInput				= nullptr;