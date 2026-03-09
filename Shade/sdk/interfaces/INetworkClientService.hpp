#pragma once
#include "../offsets.hpp"

#include "../services/CNetworkGameClient.hpp"

class INetworkClientService {
public:
	SCHEMA(CNetworkGameClient*, 0xA0, m_pCNetworkGameClient);
};