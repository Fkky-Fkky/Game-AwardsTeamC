#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/LeftHand/BossHandL.h"
#include "Classes/Enemy/Boss/Parts/Hands/RightHand/BossHandR.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"
#include <random>
#include "Base/DX12Effekseer.h"

using namespace DirectX;

class ObjectManager;

class HandManager {
public:
	HandManager() {
		attack		 = nullptr;
		beat_effect_ = nullptr;
		attack_state_	= WAIT;
		hand_state_		= ROCK;
		old_hand_state_ = PAPER;
		boss_hp_ = 0.0f;
		action_end_flag_	   = false;
		same_handstate_flag_   = false;
		weak_state_start_flag_ = false;
		weak_state_			   = false;
	}
	~HandManager() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;

	void PlaySlapSE()const;
	void PlayBeatSE()const;
	void PlayBeatEffect(const SimpleMath::Vector3 effect_pos)const;

	void RandomAttackState();
	void ActionEnd();
	void WeakStateStart();
	
	void SetWeakState(const bool select);
	bool IsBossWeak() const { return weak_state_; }
	bool IsVerticalShake() const { if (hand_l.IsVerticalShake() || hand_r.IsVerticalShake()) { return true; } else { return false; } }
	bool IsSideShake() const { if (hand_l.IsSideShake() || hand_r.IsSideShake()) { return true; } else { return false; } }
	bool GetHandState() const { return hand_state_; }
	bool GetLHandAttackFlag() const { return hand_l.GetAttackFlag(); }
	bool GetRHandAttackFlag() const { return hand_r.GetAttackFlag(); }

	BoundingOrientedBox GetLHandCollision() const { return hand_l.GetHandCollision(); }
	BoundingOrientedBox GetRHandCollision() const { return hand_r.GetHandCollision(); }
private:
	void RandomHandState();
	void SwitchStateAttack();
	void SwitchStateWait();
	void SwitchStateWeak();

	BossHandL hand_l;
	BossHandR hand_r;
	BossAttack* attack;

	EFFECT beat_effect_;

	std::mt19937 random_engine_;
	std::uniform_int_distribution<int> random_atk_dist_;
	std::uniform_int_distribution<int> random_hand_dist_;

	XAudio::SOUNDEFFECT slap_se_;
	XAudio::SOUNDEFFECT	beat_se_;

	int attack_state_;
	float boss_hp_;
	bool hand_state_;
	bool old_hand_state_;
	bool weak_state_start_flag_;
	bool weak_state_;
	bool action_end_flag_;
	bool same_handstate_flag_;

	const int ATTACK_STATE_MIN_ = 1;
	const int ATTACK_STATE_MAX_ = 6;
	const int NORMAL_MODE_MAX_ = 4;
	const int HARD_MODE_MAX_ = 5;
	const float HP_NORMAL_MAX_ = 30.0f;
	const float HP_NORMAL_MIN_ = 20.0f;
	const float HP_HARD_MIN_ = 10.0f;

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