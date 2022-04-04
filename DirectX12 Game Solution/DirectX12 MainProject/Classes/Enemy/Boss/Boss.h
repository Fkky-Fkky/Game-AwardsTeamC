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

private:
	void Attack();
	void RightSlap();
	void LeftSlap();

	DX9::MODEL boss_body;
	DX9::MODEL right_hand;
	DX9::MODEL left_hand;

	SimpleMath::Vector3 body_pos;
	SimpleMath::Vector3 r_hand_pos;
	SimpleMath::Vector3 l_hand_pos;
	SimpleMath::Vector3 r_hand_rote;

	float time_delta;
	float speed;

	int boss_state;
	float slap_time;
	const float V0 = 5.0f;
	const float GRAVITY = 10.0f;

	enum BOSS_STATE {
		WAIT,
		RIGHT_SLAP,
		LEFT_SLAP
	};


};