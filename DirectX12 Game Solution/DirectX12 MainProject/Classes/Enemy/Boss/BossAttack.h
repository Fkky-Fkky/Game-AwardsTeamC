#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/BossParts.h"

using namespace DirectX;

class BossAttack : public BossParts {
public:
	BossAttack();
	~BossAttack() {};
	void Initialize();

	void Update(const float deltaTime);
	//void Render();
	//void Attack();
	bool GetHitFlag() { return hit_flag; }

private:

	void SusiZanmai();

	DX9::MODEL left_hand;

	BoundingOrientedBox left_hand_obb;
	DX9::MODEL left_hand_obb_model;


	SimpleMath::Vector3 l_hand_pos;
	SimpleMath::Vector3 l_hand_rote;


	float bezier_t;
	float time_delta;
	float slap_time;
	float beat_time;

	bool hit_flag;
	bool hand_return_flag;


	const float R_HAND_INTIAL_POS_X = 80.0f;

protected:
	int boss_state;
	enum BOSS_STATE {
		WAIT,
		RIGHT_SLAP,
		LEFT_SLAP,
		RIGHT_BEAT,
		LEFT_BEAT
	};

	const float SLAP_SPEED = 11.0f;
	const float SLAP_GRAVITY = 23.0f;
	const float BEAT_SPEED = 23.0f;
	const float BEAT_GRAVITY = 80.0f;
	const float HALF = 0.5f;

};