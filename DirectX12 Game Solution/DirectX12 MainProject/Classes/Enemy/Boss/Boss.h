#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"
#include "Classes/Enemy/Boss/Parts/Core/BossCore.h"

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
		boss_invincible_time_ = 0.0f;
		time_delta_ = 0.0f;
		is_invincible_ = false;
		action_end_flag_	   = false;
		same_handstate_flag_   = false;
		hand_dmg_flag_		   = false;
		weak_state_start_flag_ = false;
		weak_state_			   = false;
	}

	~Boss() {};

	void Initialize();
	void LoadAseets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;
	void Render2D()const;

	int GetBossHP() const { return core.GetBossHP(); }
	bool IsBossWeak() const { return weak_state_; }
	bool IsVerticalShake() const { if (hand_l.IsVerticalShake() || hand_r.IsVerticalShake()) { return true; } else { return false; } }
	bool IsSideShake() const { if (hand_l.IsSideShake() || hand_r.IsSideShake()) { return true; } else { return false; } }
	bool GetHandState() const { return hand_state_; }
	bool GetLHandAttackFlag() const { return hand_l.GetAttackFlag(); }
	bool GetRHandAttackFlag() const { return hand_r.GetAttackFlag(); }
	BoundingOrientedBox GetLHandCollision() const { return hand_l.GetHandCollision(); }
	BoundingOrientedBox GetRHandCollision() const { return hand_r.GetHandCollision(); }
	BoundingOrientedBox GetCoreCollision() const { return core.GetCoreCollision(); }

private:

	void HandDamage(const ObjectManager* const obj_m);

	BossBody body;
	BossCore core;

	float boss_invincible_time_;
	float time_delta_ = 0.0f;
	bool is_invincible_;

	int hand_damage_num_;
};