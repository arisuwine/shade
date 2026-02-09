#include "view_render.hpp"

#include <stdexcept>

#include "hooks.hpp"

#include "../sdk/sdk.hpp"
#include "../sdk/modules.hpp"
#include "../sdk/signatures.hpp"

#include "../menu/options.hpp"

#include "../utils/debug.hpp"

// СViewRenderHook
void CViewRenderHook::Register() {
	std::unique_ptr<CVMTHook> hook = std::make_unique<CVMTHook>("CViewRenderHook", g_CViewRender);

	m_pOnRenderStartOrig = hook->Enable<OnRenderStartFunc>(4, hkOnRenderStart);
	if (!m_pOnRenderStartOrig)
		throw std::runtime_error("failed to enable OnRenderStart hook");

	hooks::g_pHooks.push_back(std::move(hook));
}

void* __fastcall CViewRenderHook::hkOnRenderStart(CViewRender* pViewRender) {
	void* result = m_pOnRenderStartOrig(pViewRender);

	pViewRender->m_CurrentView.m_flAspectRatio	= 1600.0f / 900.0f * (g_Options->misc_aspect_ratio / 100.0f);
	pViewRender->m_CurrentView.m_nSomeFlags	|= 0x2;
	//pViewRender->m_CurrentView.m_flFov			= CViewRender::ScaleFOVByWidthRatio(g_Options->misc_fov, pViewRender->m_CurrentView.m_flAspectRatio * 0.75f);
	//pViewRender->m_CurrentView.m_flFovViewModel = CViewRender::ScaleFOVByWidthRatio(g_Options->misc_viewmodel_fov, pViewRender->m_CurrentView.m_flAspectRatio * 0.75f);

	return result;
}

// COverrideFovHook
void COverrideFovHook::Register() {
	hooks::AddDetour<OverrideFovFunc>("COverrideFovHook", reinterpret_cast<void*>(modules::client.Find(FOV_CS_DEBUG)), hkOverrideFov, &m_pOverrideFovOrig);
}

float __fastcall COverrideFovHook::hkOverrideFov(__int64 a1, __int64 a2) {
	return m_pOverrideFovOrig(a1, a2);
}

// CSetupViewModelHook
void CSetupViewModelHook::Register() {
	hooks::AddDetour<SetupViewModelFunc>("CSetupViewModelHook", reinterpret_cast<void*>(modules::client.Find(SETUP_VIEWMODEL)), hkSetupViewModel, &m_pSetupViewModelOrig);
}

void* __fastcall CSetupViewModelHook::hkSetupViewModel(__int64 unk, float* offsets, float* fov) {
	//if (!is_init) {
	//	view_setup_cache.m_flFov = pViewRender->m_CurrentView.m_flFov;
	//	view_setup_cache.m_flFovViewModel = pViewRender->m_CurrentView.m_flFovViewModel;
	//	view_setup_cache.m_angView = pViewRender->m_CurrentView.m_angView;
	//	view_setup_cache.m_flAspectRatio = pViewRender->m_CurrentView.m_flAspectRatio;
	//	view_setup_cache.m_nSomeFlags = pViewRender->m_CurrentView.m_nSomeFlags;

	//	is_init = TRUE;
	//}

	void* result = m_pSetupViewModelOrig(unk, offsets, fov);

	//*fov = CViewRender::ScaleFOVByWidthRatio(g_Options->misc_viewmodel_fov, g_CViewRender->m_CurrentView.m_flAspectRatio);

	return result;
}