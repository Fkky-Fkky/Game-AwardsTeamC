#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/BossAttack.h"

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

	DX9::MODEL boss_body;

	DX9::SPRITEFONT font;

	SimpleMath::Vector3 body_pos;

	float time_delta;
	BossAttack boss_attack;
};