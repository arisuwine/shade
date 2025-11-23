#pragma once
#include "../interfaces/CGameEntitySystem.hpp"
#include "../interfaces/CCollisionProperty.hpp"
#include "../interfaces/CPlayer_MovementServices.hpp"
#include "../interfaces/CGameSceneNode.hpp"
#include "../interfaces/CModelState.hpp"
#include "../interfaces/CCSPlayerController.hpp"

#include "../math/vector.hpp"
#include "../offsets.hpp"

class CCSPlayerPawn {
private:
	template <typename Type>
	inline Type get_data(const uintptr_t& offset) const {
		return *reinterpret_cast<Type*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

public:
	CCSPlayerPawn(size_t idx);
	CCSPlayerPawn() {}

	enum TEAM : int {
		SPEC = 1,
		T = 2,
		CT = 3
	};

	const char*					m_sSanitizedPlayerName()	const;
	int							m_iHealth()					const;
	int							m_ArmorValue()				const;
	TEAM						m_iTeamNum()				const;
	vector_3d					m_vOldOrigin()				const;
	bool						m_bIsScoped()				const;
	bool						m_bIsDefusing()				const;
	CCollisionProperty*			m_pCollision()				const;
	CPlayer_MovementServices*	m_pMovementServices()		const;
	CGameSceneNode*				m_pGameSceneNode()			const;
};

class LocalPlayer {
private:
	static uintptr_t handle;
	static uintptr_t controller;

	CCSPlayerPawn* pawn;

	LocalPlayer() : pawn(nullptr) {}

public:

	static LocalPlayer& get() {
		static LocalPlayer instance;
		return instance;
	}

	inline void initialize() {
		if (!handle)
			handle = modules::client.find(LOCAL_PLAYER_CONTROLLER);

		if (!controller)
			controller = *reinterpret_cast<uintptr_t*>(handle + *((int32_t*)(handle + 3)) + 7);
	}

	void update() {
		initialize();
		pawn = reinterpret_cast<CCSPlayerPawn*>(CGameEntitySystem::GetPawnByController(controller));
	}

	CCSPlayerPawn* get_pawn() const {
		return pawn;
	}

	uintptr_t get_controller() const {
		return controller;
	}
};