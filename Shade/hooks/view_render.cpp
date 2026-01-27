#include "view_render.hpp"

#include "minhook.h"

#include "../menu/options.hpp"

#include "../sdk/sdk.hpp"

#include "../utils/debug.hpp"

bool ViewRenderHook::m_bIsInit = FALSE;
CViewSetupCache view_setup_cache = {};

bool ViewRenderHook::Initialize() {
	if (m_bIsInit)
		return TRUE;

	if (MH_CreateHook((LPVOID)pOnRenderStart, &hkOnRenderStart, reinterpret_cast<void**>(&OnRenderStartOrig)) != MH_OK)
		LOG_AND_RETURN("[-] hkOnRenderStart hook creation has failed.\n");

	if (MH_EnableHook((LPVOID)pOnRenderStart) != MH_OK)
		LOG_AND_RETURN("[-] pOnRenderStart hook enabling has failed.\n");

	m_bIsInit = FALSE;
	return TRUE;
}

bool ViewRenderHook::Shutdown() {
	if (!m_bIsInit)
		return TRUE;

	if (MH_DisableHook((LPVOID)pOnRenderStart) != MH_OK)
		LOG_AND_RETURN("[-] pOnRenderStart hook disabling has failed.\n");

	m_bIsInit = FALSE;
	return TRUE;
}

void* __fastcall ViewRenderHook::hkOnRenderStart(CViewRender* pViewRender) {
	if (!m_bIsInit) {
		view_setup_cache.m_flFov			= pViewRender->m_CurrentView.m_flFov;
		view_setup_cache.m_flFovViewModel	= pViewRender->m_CurrentView.m_flFovViewModel;
		view_setup_cache.m_angView			= pViewRender->m_CurrentView.m_angView;
		view_setup_cache.m_flAspectRatio	= pViewRender->m_CurrentView.m_flAspectRatio;
		view_setup_cache.m_nSomeFlags		= pViewRender->m_CurrentView.m_nSomeFlags;

		m_bIsInit = TRUE;
	}

	void* result = OnRenderStartOrig(pViewRender);

	pViewRender->m_CurrentView.m_flAspectRatio	= 1600.0f / 900.0f * (g_Options.misc_aspect_ratio / 100.0f);
	pViewRender->m_CurrentView.m_nSomeFlags	|= 0x2;
	//pViewRender->m_CurrentView.m_flFov			= CViewRender::ScaleFOVByWidthRatio(g_Options.misc_fov, pViewRender->m_CurrentView.m_flAspectRatio * 0.75f);
	//pViewRender->m_CurrentView.m_flFovViewModel = CViewRender::ScaleFOVByWidthRatio(g_Options.misc_viewmodel_fov, pViewRender->m_CurrentView.m_flAspectRatio * 0.75f);

	return result;
}

bool OverrideViewModelHook::m_bIsInit = FALSE;
bool OverrideViewModelHook::Initialize() {
	if (m_bIsInit)
		return TRUE;

	if (MH_CreateHook((LPVOID)pCalcViewModel, &hkCalcViewModel, reinterpret_cast<void**>(&CalcViewModelOrig)) != MH_OK)
		LOG_AND_RETURN("[-] hkCalcViewModel hook creation has failed.\n");

	if (MH_EnableHook((LPVOID)pCalcViewModel) != MH_OK)
		LOG_AND_RETURN("[-] pCalcViewModel hook enabling has failed.\n");

	m_bIsInit = FALSE;
	return TRUE;
}

bool OverrideViewModelHook::Shutdown() {
	if (!m_bIsInit)
		return TRUE;

	if (MH_DisableHook((LPVOID)pCalcViewModel) != MH_OK)
		LOG_AND_RETURN("[-] pCalcViewModel hook disabling has failed.\n");

	m_bIsInit = FALSE;
	return TRUE;
}

void* __fastcall OverrideViewModelHook::hkCalcViewModel(__int64 unk, float* offsets, float* fov) {
	//if (!is_init) {
	//	view_setup_cache.m_flFov = pViewRender->m_CurrentView.m_flFov;
	//	view_setup_cache.m_flFovViewModel = pViewRender->m_CurrentView.m_flFovViewModel;
	//	view_setup_cache.m_angView = pViewRender->m_CurrentView.m_angView;
	//	view_setup_cache.m_flAspectRatio = pViewRender->m_CurrentView.m_flAspectRatio;
	//	view_setup_cache.m_nSomeFlags = pViewRender->m_CurrentView.m_nSomeFlags;

	//	is_init = TRUE;
	//}

	void* result = CalcViewModelOrig(unk, offsets, fov);

	//*fov = CViewRender::ScaleFOVByWidthRatio(g_Options.misc_viewmodel_fov, g_CViewRender->m_CurrentView.m_flAspectRatio);

	return result;
}