#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class Boss {
public:
	Boss();
	~Boss() {};

	void Intialize();
	void LoadAseets();
	void Update(const float deltaTime);
	void Render();
	void Render2D();

private:
	void Attack();
	void RightSlap();
	void LeftSlap();
	void RightBeat();
	void LeftBeat();
	void SusiZanmai();

	DX9::MODEL boss_body;
	DX9::MODEL right_hand;
	DX9::MODEL left_hand;

	BoundingOrientedBox right_hand_obb;
	DX9::MODEL right_hand_obb_model;

	BoundingOrientedBox left_hand_obb;
	DX9::MODEL left_hand_obb_model;

	bool hit_flag;
	DX9::SPRITEFONT font;

	SimpleMath::Vector3 body_pos;
	SimpleMath::Vector3 r_hand_pos;
	SimpleMath::Vector3 l_hand_pos;
	SimpleMath::Vector3 r_hand_rote;
	SimpleMath::Vector3 l_hand_rote;


	float time_delta;
	bool hand_return_flag;
	int boss_state;
	float slap_time;
	float beat_time;
	const float SLAP_SPEED = 11.0f;
	const float SLAP_GRAVITY = 23.0f;
	const float BEAT_SPEED = 23.0f;
	const float BEAT_GRAVITY = 80.0f;
	const float HALF = 0.5f;

	enum BOSS_STATE {
		WAIT,
		RIGHT_SLAP,
		LEFT_SLAP,
		RIGHT_BEAT,
		LEFT_BEAT
	};
	float bezier_t;

};