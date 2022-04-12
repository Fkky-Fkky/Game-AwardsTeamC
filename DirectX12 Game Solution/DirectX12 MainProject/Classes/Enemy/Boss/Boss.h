#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/BossAttack.h"
#include "Classes/Enemy/Boss/BossHandR.h"
#include "Classes/Enemy/Boss/BossHandL.h"

using namespace DirectX;

class Boss {
public:
	Boss();
	~Boss() {};

	void Initialize();
	void LoadAseets();
	void Update(const float deltaTime);
	void Render();
	void Render2D();

private:

	DX9::MODEL boss_body;

	DX9::SPRITEFONT font;

	SimpleMath::Vector3 body_pos;

	float time_delta;
	BossAttack boss_attack;
	BossHandR hand_r;
	BossHandL hand_l;

};