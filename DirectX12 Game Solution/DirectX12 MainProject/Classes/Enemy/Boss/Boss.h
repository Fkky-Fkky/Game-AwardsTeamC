#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"
#include "Classes/Enemy/Boss/Parts/Core/BossCore.h"
#include "Classes/Enemy/Boss/Parts/Hands/LeftHand/BossHandL.h"
#include "Classes/Enemy/Boss/Parts/Hands/RightHand/BossHandR.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"
#include <random>
#include "Base/DX12Effekseer.h"

using namespace DirectX;

class ObjectManager;

class Boss {
public:
	Boss() {
		attack		 = nullptr;
		beat_effect_ = nullptr;
		attack_state_	= WAIT;
		hand_state_		= ROCK;
		old_hand_state_ = PAPER;
		action_end_flag_	   = false;
		same_handstate_flag_   = false;
		hand_dmg_flag_		   = false;
		weak_state_start_flag_ = false;
		weak_state_			   = false;
	}

	~Boss() {};

	void Initialize();
	void LoadAseets();
	void Update(const float deltaTime, ObjectManager* obj_m);
	void Render();
	void Render2D();

	void ActionEnd();
	void WeakStateStart();
	void RandomAttackState();
	void SetWeakState(bool select);
	void PlaySlapSE();
	void PlayBeatSE();
	void PlayBeatEffect(SimpleMath::Vector3 effect_pos);
	int GetBossHP() { return core.GetBossHP(); }
	bool IsBossWeak() { return weak_state_; }
	bool IsVerticalShake() { if (hand_l.IsVerticalShake() || hand_r.IsVerticalShake()) { return true; } else { return false; } }
	bool IsSideShake() { if (hand_l.IsSideShake() || hand_r.IsSideShake()) { return true; } else { return false; } }
	bool GetHandState() { return hand_state_; }
	bool GetLHandAttackFlag() { return hand_l.GetAttackFlag(); }
	bool GetRHandAttackFlag() { return hand_r.GetAttackFlag(); }
	BoundingOrientedBox GetLHandCollision() { return hand_l.GetHandCollision(); }
	BoundingOrientedBox GetRHandCollision() { return hand_r.GetHandCollision(); }
	BoundingOrientedBox GetCoreCollision() { return core.GetCoreCollision(); }

private:
	void SwitchStateAttack();
	void SwitchStateWait();
	void SwitchStateDamage();
	void SwitchStateWeak();
	void RandomHandState();

	BossBody body;
	BossCore core;
	BossHandL hand_l;
	BossHandR hand_r;
	BossAttack* attack;

	std::mt19937 random_engine_;
	std::uniform_int_distribution<int> random_atk_dist_;
	std::uniform_int_distribution<int> random_hand_dist_;

	EFFECT beat_effect_;

	XAudio::SOUNDEFFECT slap_se_;
	XAudio::SOUNDEFFECT	beat_se_;

	int attack_state_;
	bool hand_state_;
	bool old_hand_state_;

	bool action_end_flag_;
	bool same_handstate_flag_;
	bool hand_dmg_flag_;
	bool weak_state_start_flag_;
	bool weak_state_;

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

	const int NORMAL_MODE_MAX_	  = 4;
	const int HARD_MODE_MAX_	  = 5;
	const int ATTACK_STATE_MIN_ = 1;
	const int ATTACK_STATE_MAX_ = 6;
	const float HP_NORMAL_MAX_ = 30.0f;
	const float HP_NORMAL_MIN_ = 20.0f;
	const float HP_HARD_MIN_   = 10.0f;
};