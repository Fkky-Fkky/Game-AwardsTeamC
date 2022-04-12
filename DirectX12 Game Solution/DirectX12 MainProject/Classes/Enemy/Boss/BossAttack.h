#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/BossHandR.h"
#include "Classes/Enemy/Boss/BossHandL.h"

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
	bool GetHitFlag() { return hit_flag; }
	void SetBossState(int state) { boss_state = state; }
private:

	void SusiZanmai();

	float bezier_t;
	float time_delta;

	bool hit_flag;

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