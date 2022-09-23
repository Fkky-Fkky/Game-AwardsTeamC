#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include <random>
#include "Base/DX12Effekseer.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"
#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"

using namespace DirectX;

class ObjectManager;

class ActionManager {
public:
	ActionManager() {
		action_		 = nullptr;
		beat_effect_ = nullptr;
		attack_state_ = WAIT;
		boss_hp_	  = 0.0f;
		action_end_flag_	   = false;
		is_vertical_shake_	   = false;
		is_side_shake_		   = false;
		is_switch_state_weak_  = false;
		is_switch_state_death_ = false;
		is_hand_death_		   = false;
	}

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;

	void RandomAttackState();
	void ActionEnd();
	void DeathActionEnd();
	void PlaySlapSE()const;
	void PlayBeatSE()const;
	void PlayBeatEffect(const SimpleMath::Vector3 effect_pos)const;

	void SetVerticalShake(const bool enable) { is_vertical_shake_ = enable; }
	void SetSideShake(const bool enable) { is_side_shake_ = enable; }
	
	bool IsVerticalShake() const { return is_vertical_shake_; }
	bool IsSideShake() const { return is_side_shake_; }
	bool IsHandDeath() const { return is_hand_death_; }
	bool IsHandOpen() const { return hand_.IsHandOpen(); }
	bool IsLHandAttack() const { return hand_.IsLHandAttack(); }
	bool IsRHandAttack() const { return hand_.IsRHandAttack(); }

	BoundingOrientedBox GetLHandCollision() const { return hand_.GetLHandCollision(); }
	BoundingOrientedBox GetRHandCollision() const { return hand_.GetRHandCollision(); }
private:
	void SwitchStateAttack();
	void SwitchStateWait();
	void SwitchStateWeak();
	void SwitchStateDeath();

	boss::BossAction* action_;
	HandManager hand_;

	EFFECT beat_effect_;
	std::mt19937 random_engine_;
	std::uniform_int_distribution<int> random_atk_dist_;

	XAudio::SOUNDEFFECT slap_se_;
	XAudio::SOUNDEFFECT	beat_se_;

	int attack_state_;
	float boss_hp_;
	bool action_end_flag_;
	bool is_vertical_shake_;
	bool is_side_shake_;
	bool is_switch_state_weak_;
	bool is_switch_state_death_;
	bool is_hand_death_;

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
};