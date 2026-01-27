#include "../offsets.hpp"

#include "../interfaces/CNetworkGameClient.hpp"

class CNetworkClientService {
public:
	SCHEMA(CNetworkGameClient*, offsets::engine2::CNetworkClientService::m_pCNetworkGameClient, m_pCNetworkGameClient);
};