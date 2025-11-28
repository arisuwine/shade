#include "../offsets.hpp"
#include "../../utils/vmt/vmt.hpp"

class CNetworkGameClient {
public:
	CNetworkGameClient() = delete;

	auto IsConnected() {
		return CALL_VIRTUAL(this, bool, 14);
	}

	auto IsConnecting() {
		return CALL_VIRTUAL(this, bool, 15);
	}

	auto IsInGame() {
		return CALL_VIRTUAL(this, bool, 18);
	}

	auto IsBackgroundMap() {
		return CALL_VIRTUAL(this, bool, 19);
	}

	auto GetMaxClients() {
		return CALL_VIRTUAL(this, int, 20);
	}
};