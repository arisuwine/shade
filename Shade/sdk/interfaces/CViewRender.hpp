#pragma once
#include <cmath>

#include "../offsets.hpp"

#include "../math/vector_3d.hpp"
#include "../math/QAngle.hpp"

#define M_PI 3.14159265358979323846

class CViewSetup
{
public:
	//BYTE	pad01[0x494]; //0x494 ?
	//float	m_flOrthoLeft; // 0x0494
	//float	m_flOrthoTop; // 0x0498
	//float	m_flOrthoRight; // 0x049C
	//float	m_flOrthoBottom; // 0x04A0
	//BYTE	pad02[0x34]; //0x34?
	//float	m_flFov; // 0x04D8
	//float	m_flFovViewmodel; // 0x04DC
	//Vector	m_vecOrigin; // 0x04E0
	//BYTE	pad03[0xC];
	//QAngle	m_angView; // 0x04F8
	//BYTE	pad04[0x14];
	//float	m_flAspectRatio; // 0x0518
	//BYTE	pad05[0x71];
	//BYTE	nSomeFlags;
	PSCHEMA(float,			offsets::client::CViewSetup::m_flFov,			m_flFov			);
	PSCHEMA(float,			offsets::client::CViewSetup::m_flFovViewModel,	m_flFovViewModel);
	PSCHEMA(Vector3D,		offsets::client::CViewSetup::m_vecOrigin,		m_vecOrigin		);
	PSCHEMA(QAngle,			offsets::client::CViewSetup::m_angView,			m_angView		);
	PSCHEMA(float,			offsets::client::CViewSetup::m_flAspectRatio,	m_flAspectRatio	);
	PSCHEMA(BYTE,			offsets::client::CViewSetup::m_nSomeFlags,		m_nSomeFlags	);

	void* operator&() {
		return this;
	}
};

class CViewRender {
public:
	static inline float ScaleFOVByWidthRatio(float fovDegrees, float ratio) {
		float halfAngleRadians = fovDegrees * (0.5f * M_PI / 180.0f);
		float t = tan(halfAngleRadians);
		t *= ratio;
		float retDegrees = (180.0f / M_PI) * atan(t);
		return retDegrees * 2.0f;
	}

	PSCHEMA(CViewSetup,		offsets::client::CViewRender::m_CurrentView,	m_CurrentView	);
};