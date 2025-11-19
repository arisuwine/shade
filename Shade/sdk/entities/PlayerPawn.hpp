#pragma once
#include "../interfaces/CGameEntitySystem.hpp"
#include "../math/vector.hpp"
#include "../offsets.hpp"

class PlayerPawn {
private:
	static uintptr_t entity_system;
	static uintptr_t __fastcall GetPawnByController(const uintptr_t& controller);
	static uintptr_t local_controller_handle;

	struct PawnData {
	private:
		template <typename Type>
		inline Type get_data(const uintptr_t& address, const uintptr_t& offset) const {
			return *reinterpret_cast<Type*>(address + offset);
		}

	public:
		struct CUtlString {
			char string[128];
			CUtlString(const uintptr_t& controller) {
				const char* ptr = reinterpret_cast<const char*>(controller + offsets::CCSPlayerController::m_iszPlayerName);
				if (!ptr || ptr == nullptr) {
					string[0] = '\0';
					return;
				}

				strncpy(string, ptr, sizeof(string) - 1);
				string[sizeof(string) - 1] = '\0';
			}
			CUtlString() {
				string[0] = '\0';
			}
		} name;

		int health;
		int armor;
		int team_num;

		vector_3d origin;

		bool is_scoped;
		bool is_defusing;

		PawnData(const uintptr_t& controller, const uintptr_t& pawn);
		PawnData() {}
	};

	uintptr_t controller, pawn;

	bool empty;
	
public:
	PlayerPawn(size_t idx);
	PlayerPawn() {}

	PawnData data;

	uintptr_t get_address() const;
	bool is_local_player() const;
	bool is_empty() const;
};

