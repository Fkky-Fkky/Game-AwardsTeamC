#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

class Status {
public:
	Status() {
		damage_type_ = HAND;
		hp_ = 0.0f;
		invincible_time_ = 0.0f;
	};

	void Initialize();
	void Update(const float deltaTime, const ObjectManager* const obj_m);

	float GetBossHP() const { return hp_; }
private:
	void DamageProcess();

	int damage_type_;
	float hp_;
	float invincible_time_;
	const float BOSS_HP_MAX_ = 30.0f;
	const float HAND_DAMAGE_ = 1.0f;
	const float BODY_DAMAGE_ = 5.0f;
	const float INVINCIBLE_TIME_MAX_ = 2.0f;

	enum DAMAGE_TYPE_ {
		HAND,
		BODY
	};
};