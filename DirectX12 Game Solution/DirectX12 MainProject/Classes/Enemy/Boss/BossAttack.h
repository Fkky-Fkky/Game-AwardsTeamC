#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/BossHandR.h"
#include "Classes/Enemy/Boss/BossHandL.h"
#include <random>

using namespace DirectX;

class BossAttack{
public:
	BossAttack();
	~BossAttack() {};
	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();
	void Attack();
	void SetBossState(int state) { boss_state = state; }

	bool GetRHandAttackFlag() { return hand_r.GetAttackFlag(); }
	bool GetLHandAttackFlag() { return hand_l.GetAttackFlag(); }
	BoundingOrientedBox GetRHandCollision() { return hand_r.GetRHandCollision(); }
	BoundingOrientedBox GetLHandCollision() { return hand_l.GetLHandCollision(); }

private:

	void SusiZanmai();
	void RandomAction();

	float bezier_t;
	float time_delta;


	std::mt19937 randomEngine;
	std::uniform_int_distribution<int> randomDist;
	float wait_time;

	int boss_state;
	enum BOSS_STATE {
		WAIT,
		RIGHT_SLAP,
		LEFT_SLAP,
		RIGHT_BEAT,
		LEFT_BEAT
	};

	BossHandR hand_r;
	BossHandL hand_l;

};