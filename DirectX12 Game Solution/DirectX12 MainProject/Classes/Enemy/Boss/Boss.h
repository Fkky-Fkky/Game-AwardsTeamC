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
		attack = nullptr;
		attack_state_ = WAIT;
		action_end_flag_ = false;
		beat_effect_ = nullptr;
		hand_state_ = false;
		old_hand_state_ = false;
		same_state_flag_ = false;
		hand_dmg_flag_ = false;
	}

	~Boss() {};

	void Initialize();
	void LoadAseets();
	void Update(const float deltaTime, ObjectManager* obj_m);
	void Render();
	void Render2D();

	void ActionEnd();
	void RandomAttackState();
	void PlaySlapSE();
	void PlayBeatSE();
	void PlayBeatEffect(SimpleMath::Vector3 effect_pos);
	int GetBossHP() { return core.GetBossHP(); }
	bool GetHnadState() { return hand_state_; }
	bool GetLHandAttackFlag() { return hand_l.GetAttackFlag(); }
	bool GetRHandAttackFlag() { return hand_r.GetAttackFlag(); }
	BoundingOrientedBox GetLHandCollision() { return hand_l.GetHandCollision(); }
	BoundingOrientedBox GetRHandCollision() { return hand_r.GetHandCollision(); }
	BoundingOrientedBox GetCoreCollision() { return core.GetCoreCollision(); }

private:
	void SwitchStateAttack();
	void SwitchStateWait();
	void SwitchStateDamage();
	void RandomHandState();

	BossBody body;
	BossCore core;
	BossHandL hand_l;
	BossHandR hand_r;

	BossAttack* attack;
	std::mt19937 random_engine_;
	std::uniform_int_distribution<int> randomDist;
	int attack_state_;

	bool action_end_flag_;
	enum BOSS_STATE {
		WAIT,
		RIGHT_BEAT,
		LEFT_BEAT,
		LEFT_SLAP,
		RIGHT_SLAP,
		DOUBLE_SLAP,
		BEAT_RUSH_R
	};

	EFFECT beat_effect_;

	bool hand_state_;
	bool old_hand_state_;

	enum HAND_STATE {
		ROCK,
		PAPER
	};
	std::uniform_int_distribution<int> random_hand_dist_;
	bool same_state_flag_;
	XAudio::SOUNDEFFECT slap_se_;
	XAudio::SOUNDEFFECT	beat_se_;

	bool hand_dmg_flag_;

	const float HP_NORMAL_MAX_ = 30.0f;
	const float HP_NORMAL_MIN_ = 20.0f;
	const float HP_HARD_MIN_ = 10.0f;
	const float NORMAL_MODE_MAX_	= 3;
	const float HARD_MODE_MAX_		= 5;
	const float VERY_HARD_MODE_MAX_ = 6;
};