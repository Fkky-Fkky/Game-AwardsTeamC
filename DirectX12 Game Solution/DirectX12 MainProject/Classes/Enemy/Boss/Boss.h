#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"
#include "Classes/Enemy/Boss/Parts/Hands/ActionManager.h"
#include "Classes/Enemy/Boss/Status.h"

using namespace DirectX;

class ObjectManager;

class Boss {
public:
	Boss() {
		is_vertical_shake_ = false;
	}

	~Boss() {};

	void Initialize();
	void LoadAseets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;

	void SetVerticalShake(const bool enable) { is_vertical_shake_ = enable; }

	float GetBossHP() const { return status_.GetBossHP(); }
	bool IsBossWeak() const { return status_.IsWeak(); }
	bool IsBossDeath() const { return body_.IsBodyDeath() && action_.IsHandDeath(); }
	bool IsVerticalShake() const { return action_.IsVerticalShake() || is_vertical_shake_; }
	bool IsSideShake() const { return action_.IsSideShake(); }
	bool IsHandOpen() const { return action_.IsHandOpen(); }
	bool IsLHandAttack() const { return action_.IsLHandAttack(); }
	bool IsRHandAttack() const { return action_.IsRHandAttack(); }
	BoundingOrientedBox GetLHandCollision() const { return action_.GetLHandCollision(); }
	BoundingOrientedBox GetRHandCollision() const { return action_.GetRHandCollision(); }
	BoundingOrientedBox GetBodyCollision() const { return body_.GetBodyCollision(); }

private:
	boss::Status status_;
	boss::BossBody body_;
	ActionManager action_;
	
	bool is_vertical_shake_;
};