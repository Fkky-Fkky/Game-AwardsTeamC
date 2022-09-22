#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/LeftHand/BossHandL.h"
#include "Classes/Enemy/Boss/Parts/Hands/RightHand/BossHandR.h"
#include <random>

using namespace DirectX;

class HandManager {
public:
	HandManager() {
		hand_state_		= ROCK;
		old_hand_state_ = PAPER;
		same_handstate_flag_   = false;
	}
	~HandManager() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render()const;

	void RandomHandState();

	bool GetHandState() const { return hand_state_; }
	bool GetLHandAttackFlag() const { return hand_l.GetAttackFlag(); }
	bool GetRHandAttackFlag() const { return hand_r.GetAttackFlag(); }

	boss::BossHandL& GetHandL() { return hand_l; }
	boss::BossHandR& GetHandR() { return hand_r; }
	BoundingOrientedBox GetLHandCollision() const { return hand_l.GetHandCollision(); }
	BoundingOrientedBox GetRHandCollision() const { return hand_r.GetHandCollision(); }
private:
	boss::BossHandL hand_l;
	boss::BossHandR hand_r;

	std::mt19937 random_engine_;
	std::uniform_int_distribution<int> random_hand_dist_;

	bool hand_state_;
	bool old_hand_state_;
	bool same_handstate_flag_;

	enum BOSS_STATE {
		WAIT,
		LEFT_BEAT,
		LEFT_SLAP,
		RIGHT_BEAT,
		RIGHT_SLAP,
		DOUBLE_SLAP,
		BEAT_RUSH_R
	};

	enum HAND_STATE {
		ROCK,
		PAPER
	};
};