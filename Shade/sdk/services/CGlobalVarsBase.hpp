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

	SCHEMA(float,					offsets::client::CGlobalVarsBase::m_flRealTime,						m_flRealTime					);
	SCHEMA(int,						offsets::client::CGlobalVarsBase::m_iFrameCount,					m_iFrameCount					);
	SCHEMA(float,					offsets::client::CGlobalVarsBase::m_flAbsoluteFrameTime,			m_flAbsoluteFrameTime			);
	SCHEMA(float,					offsets::client::CGlobalVarsBase::m_flAbsoluteFrameStartTimesTDDev, m_flAbsoluteFrameStartTimesTDDev);
	SCHEMA(int,						offsets::client::CGlobalVarsBase::m_iMaxClients,					m_iMaxClients					);
	SCHEMA(int,						offsets::client::CGlobalVarsBase::m_iUnknown1,						m_iUnknown1						);
	SCHEMA(int,						offsets::client::CGlobalVarsBase::m_iUnknown2,						m_iUnknown2						);
	SCHEMA(int,						offsets::client::CGlobalVarsBase::m_iUnknown3,						m_iUnknown3						);
	SCHEMA(int,						offsets::client::CGlobalVarsBase::m_iUnknown4,						m_iUnknown4						);
	SCHEMA(int,						offsets::client::CGlobalVarsBase::m_iUnknown5,						m_iUnknown5						);
	SCHEMA(FnGlobalVarsWarningFunc, offsets::client::CGlobalVarsBase::m_pfnWarningFunc,					m_pfnWarningFunc				);
	SCHEMA(float,					offsets::client::CGlobalVarsBase::m_flCurTime,						m_flCurTime						);
	SCHEMA(float,					offsets::client::CGlobalVarsBase::m_flFrameTime,					m_flFrameTime					);
	SCHEMA(int,						offsets::client::CGlobalVarsBase::m_iUnknown6,						m_iUnknown6						);
	SCHEMA(int,						offsets::client::CGlobalVarsBase::m_iUnknown7,						m_iUnknown7						);
	SCHEMA(bool,					offsets::client::CGlobalVarsBase::m_bInSimulation,					m_bInSimulation					);
	SCHEMA(bool,					offsets::client::CGlobalVarsBase::m_bEnableAssertions,				m_bEnableAssertions				);
	SCHEMA(int,						offsets::client::CGlobalVarsBase::m_iTickCount,						m_iTickCount					);
	SCHEMA(int,						offsets::client::CGlobalVarsBase::m_iUnknown7,						m_iUnknown8						);
	SCHEMA(int,						offsets::client::CGlobalVarsBase::m_iUnknown7,						m_iUnknown9						);
	SCHEMA(float,					offsets::client::CGlobalVarsBase::m_flSubtickFraction,				m_flSubtickFraction				);
};