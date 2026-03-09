#pragma once
#include "../offsets.hpp"

enum GlobalVarsUsageWarning_t
{
	GV_RENDERTIME_CALLED_DURING_SIMULATION,
	GV_CURTIME_CALLED_DURING_RENDERING
};

class CGlobalVarsBase {
public:
	using FnGlobalVarsWarningFunc = void(*)(GlobalVarsUsageWarning_t);

	SCHEMA(float,					0x0,	m_flRealTime					);
	SCHEMA(int,						0x4,	m_iFrameCount					);
	SCHEMA(float,					0x8,	m_flAbsoluteFrameTime			);
	SCHEMA(float,					0xC,	m_flAbsoluteFrameStartTimesTDDev);
	SCHEMA(int,						0x10,	m_iMaxClients					);
	SCHEMA(int,						0x14,	m_iUnknown1						);
	SCHEMA(int,						0x18,	m_iUnknown2						);
	SCHEMA(int,						0x1C,	m_iUnknown3						);
	SCHEMA(int,						0x20,	m_iUnknown4						);
	SCHEMA(int,						0x24,	m_iUnknown5						);
	SCHEMA(FnGlobalVarsWarningFunc, 0x28,	m_pfnWarningFunc				);
	SCHEMA(float,					0x30,	m_flCurTime						);
	SCHEMA(float,					0x34,	m_flFrameTime					);
	SCHEMA(int,						0x38,	m_iUnknown6						);
	SCHEMA(int,						0x3C,	m_iUnknown7						);
	SCHEMA(bool,					0x40,	m_bInSimulation					);
	SCHEMA(bool,					0x41,	m_bEnableAssertions				);
	SCHEMA(int,						0x44,	m_iTickCount					);
	SCHEMA(int,						0x48,	m_iUnknown8						);
	SCHEMA(int,						0x4C,	m_iUnknown9						);
	SCHEMA(float,					0x50,	m_flSubtickFraction				);
};