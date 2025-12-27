#include "view_render.hpp"

#include "minhook.h"

#include "../menu/options.hpp"

#include "../sdk/sdk.hpp"

#include "../utils/debug.hpp"

bool ViewRenderHook::is_init = FALSE;
CViewSetupCache view_setup_cache = {};
bool ViewRenderHook::initialize() {
	if (is_init)
		return TRUE;

	if (MH_CreateHook((LPVOID)pOnRenderStart, &OnRenderStartHk, reinterpret_cast<void**>(&oOnRenderStart)) != MH_OK)
		LOG_AND_RETURN("[-] OnRenderStartHk hook creation has failed.\n");

	if (MH_EnableHook((LPVOID)pOnRenderStart) != MH_OK)
		LOG_AND_RETURN("[-] pOnRenderStart hook enabling has failed.\n");

	is_init = FALSE;
	return TRUE;
}

bool ViewRenderHook::shutdown() {
	if (!is_init)
		return TRUE;

	if (MH_DisableHook((LPVOID)pOnRenderStart) != MH_OK)
		LOG_AND_RETURN("[-] pOnRenderStart hook disabling has failed.\n");

	is_init = FALSE;
	return TRUE;
}

void* __fastcall ViewRenderHook::OnRenderStartHk(CViewRender* pViewRender) {
	if (!is_init) {
		view_setup_cache.m_flFov			= pViewRender->m_CurrentView.m_flFov;
		view_setup_cache.m_flFovViewModel	= pViewRender->m_CurrentView.m_flFovViewModel;
		view_setup_cache.m_angView			= pViewRender->m_CurrentView.m_angView;
		view_setup_cache.m_flAspectRatio	= pViewRender->m_CurrentView.m_flAspectRatio;
		view_setup_cache.m_nSomeFlags		= pViewRender->m_CurrentView.m_nSomeFlags;

		is_init = TRUE;
	}

	void* result = oOnRenderStart(pViewRender);

	pViewRender->m_CurrentView.m_flAspectRatio	= 2560.0f / 1440.0f * (g_options.misc_aspect_ratio / 100.0f);
	pViewRender->m_CurrentView.m_nSomeFlags	|= 0x2;
	//pViewRender->m_CurrentView.m_flFov			= CViewRender::ScaleFOVByWidthRatio(g_options.misc_fov, pViewRender->m_CurrentView.m_flAspectRatio * 0.75f);
	//pViewRender->m_CurrentView.m_flFovViewModel = CViewRender::ScaleFOVByWidthRatio(g_options.misc_viewmodel_fov, pViewRender->m_CurrentView.m_flAspectRatio * 0.75f);

	
	LOG("Aspect Ratio: %f, FOV: %f, ViewModel FOV: %f, My FOV: %f, My ViewModel FOV: %f, Dif: %f %f\n",
		pViewRender->m_CurrentView.m_flAspectRatio,
		pViewRender->m_CurrentView.m_flFov,
		pViewRender->m_CurrentView.m_flFovViewModel,
		CViewRender::ScaleFOVByWidthRatio(g_options.misc_fov, pViewRender->m_CurrentView.m_flAspectRatio * 0.75f),
		CViewRender::ScaleFOVByWidthRatio(g_options.misc_viewmodel_fov, pViewRender->m_CurrentView.m_flAspectRatio * 0.75f),
		pViewRender->m_CurrentView.m_flFov - CViewRender::ScaleFOVByWidthRatio(g_options.misc_fov, pViewRender->m_CurrentView.m_flAspectRatio * 0.75f),
		pViewRender->m_CurrentView.m_flFovViewModel - CViewRender::ScaleFOVByWidthRatio(g_options.misc_viewmodel_fov, pViewRender->m_CurrentView.m_flAspectRatio * 0.75f));

	return result;
}

bool OverrideViewModelHook::is_init = FALSE;
bool OverrideViewModelHook::initialize() {
	if (is_init)
		return TRUE;

	if (MH_CreateHook((LPVOID)pCalcViewModel, &CalcViewModelHk, reinterpret_cast<void**>(&oCalcViewModel)) != MH_OK)
		LOG_AND_RETURN("[-] CalcViewModelHk hook creation has failed.\n");

	if (MH_EnableHook((LPVOID)pCalcViewModel) != MH_OK)
		LOG_AND_RETURN("[-] pCalcViewModel hook enabling has failed.\n");

	is_init = FALSE;
	return TRUE;
}

bool OverrideViewModelHook::shutdown() {
	if (!is_init)
		return TRUE;

	if (MH_DisableHook((LPVOID)pCalcViewModel) != MH_OK)
		LOG_AND_RETURN("[-] pCalcViewModel hook disabling has failed.\n");

	is_init = FALSE;
	return TRUE;
}

void* __fastcall OverrideViewModelHook::CalcViewModelHk(__int64 unk, float* offsets, float* fov) {
	//if (!is_init) {
	//	view_setup_cache.m_flFov = pViewRender->m_CurrentView.m_flFov;
	//	view_setup_cache.m_flFovViewModel = pViewRender->m_CurrentView.m_flFovViewModel;
	//	view_setup_cache.m_angView = pViewRender->m_CurrentView.m_angView;
	//	view_setup_cache.m_flAspectRatio = pViewRender->m_CurrentView.m_flAspectRatio;
	//	view_setup_cache.m_nSomeFlags = pViewRender->m_CurrentView.m_nSomeFlags;

	//	is_init = TRUE;
	//}

	void* result = oCalcViewModel(unk, offsets, fov);

	//*fov = CViewRender::ScaleFOVByWidthRatio(g_options.misc_viewmodel_fov, g_CViewRender->m_CurrentView.m_flAspectRatio);

	return result;
}