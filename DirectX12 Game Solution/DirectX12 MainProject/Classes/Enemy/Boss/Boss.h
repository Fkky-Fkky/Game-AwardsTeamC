#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/BossAttack.h"

using namespace DirectX;

class Boss {
public:
	Boss();
	~Boss() {};

	void Initialize();
	void LoadAseets();
	void Update(const float deltaTime, SimpleMath::Vector3 player_pos);
	void Render();

	bool GetRHandAttackFlag() { return boss_attack.GetRHandAttackFlag(); }
	bool GetLHandAttackFlag() { return boss_attack.GetLHandAttackFlag(); }
	BoundingOrientedBox GetRHandCollision() { return boss_attack.GetRHandCollision(); }
	BoundingOrientedBox GetLHandCollision() { return boss_attack.GetLHandCollision(); }

private:
	DX9::MODEL boss_body;


	SimpleMath::Vector3 body_pos;

	BossAttack boss_attack;

};