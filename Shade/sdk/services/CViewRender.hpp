#pragma once
#include <cmath>

#include "../offsets.hpp"

#include "../math/Vector3D.hpp"
#include "../math/QAngle.hpp"

#define M_PI 3.14159265358979323846

class CViewSetup {
public:
	PSCHEMA(float,		0x498, m_flFov			);
	PSCHEMA(float,		0x49C, m_flFovViewModel	);
	PSCHEMA(Vector3D,	0x4E0, m_vecOrigin		);
	PSCHEMA(QAngle,		0x4B8, m_angView		);
	PSCHEMA(float,		0x4D8, m_flAspectRatio	);
	PSCHEMA(BYTE,		0x555, m_nSomeFlags		);

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

	PSCHEMA(CViewSetup,	0x10, m_CurrentView);
};