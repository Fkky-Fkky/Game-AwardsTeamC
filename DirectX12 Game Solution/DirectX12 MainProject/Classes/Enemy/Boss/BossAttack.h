#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class BossAttack {
public:
	BossAttack();
	~BossAttack() {};
	void Intialize();
	void LoadAseets();

	void Update(const float deltaTime);
	void Render();
	void Attack();
	bool GetHitFlag() { return hit_flag; }

private:

	void RightSlap();
	void LeftSlap();
	void RightBeat();
	void LeftBeat();
	void SusiZanmai();

	DX9::MODEL right_hand;
	DX9::MODEL left_hand;

	BoundingOrientedBox right_hand_obb;
	DX9::MODEL right_hand_obb_model;

	BoundingOrientedBox left_hand_obb;
	DX9::MODEL left_hand_obb_model;


	SimpleMath::Vector3 r_hand_pos;
	SimpleMath::Vector3 l_hand_pos;
	SimpleMath::Vector3 r_hand_rote;
	SimpleMath::Vector3 l_hand_rote;

	int boss_state;

	float bezier_t;
	float time_delta;
	float slap_time;
	float beat_time;

	bool hit_flag;
	bool hand_return_flag;

	const float SLAP_SPEED = 11.0f;
	const float SLAP_GRAVITY = 23.0f;
	const float BEAT_SPEED = 23.0f;
	const float BEAT_GRAVITY = 80.0f;
	const float HALF = 0.5f;

	const float R_HAND_INTIAL_POS_X = 80.0f;

	enum BOSS_STATE {
		WAIT,
		RIGHT_SLAP,
		LEFT_SLAP,
		RIGHT_BEAT,
		LEFT_BEAT
	};
};