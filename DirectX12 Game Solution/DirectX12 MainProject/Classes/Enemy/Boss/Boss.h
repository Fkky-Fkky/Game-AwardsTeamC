#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"
#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"
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
	void Render2D()const;

	void SetVerticalShake(const bool enable) { is_vertical_shake_ = enable; }

	float GetBossHP() const { return status_.GetBossHP(); }
	bool IsBossWeak() const { return status_.IsWeak(); }
	bool IsBossDeath() const { return body_.IsBodyDeath(); }
	bool IsVerticalShake() const { if (hand_.IsVerticalShake() || is_vertical_shake_)  return true;  else return false; }
	bool IsSideShake() const { return hand_.IsSideShake(); }
	bool GetHandState() const { return hand_.GetHandState(); }
	bool GetLHandAttackFlag() const { return hand_.GetLHandAttackFlag(); }
	bool GetRHandAttackFlag() const { return hand_.GetRHandAttackFlag(); }
	BoundingOrientedBox GetLHandCollision() const { return hand_.GetLHandCollision(); }
	BoundingOrientedBox GetRHandCollision() const { return hand_.GetRHandCollision(); }
	BoundingOrientedBox GetBodyCollision() const { return body_.GetBodyCollision(); }

private:
	boss::Status status_;
	boss::BossBody body_;
	HandManager hand_;
	
	bool is_vertical_shake_;
};