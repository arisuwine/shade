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

	hooks::AddVMTHook<OnRenderStartFunc>(hook.get(), 4, hkOnRenderStart, &m_pOnRenderStartOrig);

	hooks::g_pHooks.push_back(std::move(hook));
}

void* __fastcall CViewRenderHook::hkOnRenderStart(CViewRender* pViewRender) {
	void* result = m_pOnRenderStartOrig(pViewRender);

	if (g_Unload) {
		pViewRender->m_CurrentView.m_nSomeFlags &= ~2;
		return result;
	}

	ImVec2 ScreenSize = ImGui::GetIO().DisplaySize;

	if (g_Options->misc_aspect_ratio) {
		pViewRender->m_CurrentView.m_flAspectRatio = (ScreenSize.x / ScreenSize.y) * (g_Options->misc_aspect_ratio_value / 100.0f);
		pViewRender->m_CurrentView.m_nSomeFlags |= 2;
	}
	else
		pViewRender->m_CurrentView.m_nSomeFlags &= ~2;

	return result;
}

// CSetupFovHook
void CSetupFovHook::Register() {
	hooks::AddDetour<SetupFovFunc>("CSetupFovHook", reinterpret_cast<void*>(modules::client.Find(FOV_CS_DEBUG)), hkSetupFov, &m_pOverrideFovOrig);
}

float __fastcall CSetupFovHook::hkSetupFov(__int64 a1) {
	if (g_Unload)
		return m_pOverrideFovOrig(a1);

	ImVec2 ScreenSize = ImGui::GetIO().DisplaySize;

	if (g_Options->misc_aspect_ratio && !g_Options->misc_aspect_ratio_vertical) {
		float fov = g_Options->misc_fov ? g_Options->misc_fov_value : m_pOverrideFovOrig(a1);
		return CViewRender::ScaleFOVByWidthRatio(fov, (ScreenSize.x / ScreenSize.y) * (g_Options->misc_aspect_ratio_value / 100.0f) * 0.75f);
	}
	else if (g_Options->misc_fov)
		return g_Options->misc_fov_value;

	return m_pOverrideFovOrig(a1);
}

// CSetupViewModelHook
void CSetupViewModelHook::Register() {
	hooks::AddDetour<SetupViewModelFunc>("CSetupViewModelHook", reinterpret_cast<void*>(modules::client.Find(SETUP_VIEWMODEL)), hkSetupViewModel, &m_pSetupViewModelOrig);
}

void* __fastcall CSetupViewModelHook::hkSetupViewModel(__int64 unk, Vector3D* viewmodel_offsets, float* viewmodel_fov) {
	void* result = m_pSetupViewModelOrig(unk, viewmodel_offsets, viewmodel_fov);

	if (g_Unload)
		return result;

	ImVec2 ScreenSize = ImGui::GetIO().DisplaySize;

	if (g_Options->misc_aspect_ratio && !g_Options->misc_aspect_ratio_vertical) {
		float fov = g_Options->misc_viewmodel_fov ? g_Options->misc_viewmodel_fov_value : *viewmodel_fov;
		*viewmodel_fov = CViewRender::ScaleFOVByWidthRatio(fov, (ScreenSize.x / ScreenSize.y) * (g_Options->misc_aspect_ratio_value / 100.0f) * 0.75f);
	}
	else if (g_Options->misc_viewmodel_fov)
		*viewmodel_fov = g_Options->misc_viewmodel_fov_value;

	if (g_Options->misc_viewmodel_fov) {
		viewmodel_offsets->x = g_Options->misc_viewmodel_fov_x;
		viewmodel_offsets->y = g_Options->misc_viewmodel_fov_y;
		viewmodel_offsets->z = g_Options->misc_viewmodel_fov_z;
	}

	//Vector3D* rotations = reinterpret_cast<Vector3D*>(viewmodel_offsets + 16);

	return result;
}