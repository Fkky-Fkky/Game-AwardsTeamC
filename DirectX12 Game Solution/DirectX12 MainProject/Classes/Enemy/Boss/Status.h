#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

class Status {
public:
	Status() {
		hp_ = 0.0f;
		hit_flag_ = false;
	};

	void Initialize();
	void Update(const float deltaTime, const ObjectManager* const obj_m);

	float GetBossHP() const { return hp_; }
private:
	void HitProcessing();

	float hp_;
	bool hit_flag_;
};