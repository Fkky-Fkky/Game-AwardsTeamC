#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/BossParts.h"
#include <random>

using namespace DirectX;

class BossHand : public BossParts{
public:
	BossHand();
	~BossHand() {};
	virtual void Initialize(SimpleMath::Vector3 pos, SimpleMath::Vector3 rote);
	virtual void LoadAssets(LPCWSTR file_name);
	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos);
	virtual void Render();
	//virtual void Attack();
	virtual void SetBossState(int state) { boss_state = state; }

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

protected:
	BoundingOrientedBox collision;
	DX9::MODEL collision_model;

	SimpleMath::Vector3 player_pos_;

};