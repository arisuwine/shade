#include "../offsets.hpp"

#include "../interfaces/CNetworkGameClient.hpp"

class CNetworkClientService {
public:
	CNetworkClientService() = delete;

	SCHEMA(CNetworkGameClient*, offsets::CNetworkClientService::m_pCNetworkGameClient, m_pCNetworkGameClient);
};