#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"
#include "Classes/Enemy/Boss/Parts/Core/BossCore.h"
#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"
#include "Classes/Enemy/Boss/Status.h"

using namespace DirectX;

class ObjectManager;

class Boss {
public:
	Boss() {
		boss_invincible_time_ = 0.0f;
		time_delta_ = 0.0f;
		is_invincible_ = false;
	}

	~Boss() {};

	void Initialize();
	void LoadAseets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;
	void Render2D()const;

	int GetBossHP() const { return status_.GetBossHP(); }
	bool IsBossWeak() const { return hand_.IsBossWeak(); }
	bool IsVerticalShake() const { return hand_.IsVerticalShake(); }
	bool IsSideShake() const { return hand_.IsSideShake(); }
	bool GetHandState() const { return hand_.GetHandState(); }
	bool GetLHandAttackFlag() const { return hand_.GetLHandAttackFlag(); }
	bool GetRHandAttackFlag() const { return hand_.GetRHandAttackFlag(); }
	BoundingOrientedBox GetLHandCollision() const { return hand_.GetLHandCollision(); }
	BoundingOrientedBox GetRHandCollision() const { return hand_.GetRHandCollision(); }
	BoundingOrientedBox GetBodyCollision() const { return body_.GetBodyCollision(); }

private:

	void HandDamage(const ObjectManager* const obj_m);

	BossBody body_;
	BossCore core_;
	HandManager hand_;
	Status status_;

	float boss_invincible_time_;
	float time_delta_ = 0.0f;
	bool is_invincible_;

	int hand_damage_num_;
};