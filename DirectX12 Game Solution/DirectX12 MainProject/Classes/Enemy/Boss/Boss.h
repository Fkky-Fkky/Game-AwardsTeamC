#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/BossHandL.h"
#include "Classes/Enemy/Boss/BossHandR.h"

using namespace DirectX;

class Boss {
public:
	Boss();
	~Boss() {};

	void Initialize();
	void LoadAseets();
	void Update(const float deltaTime, SimpleMath::Vector3 player_pos);
	void Render();

	bool GetLHandAttackFlag() { return hand_l.GetAttackFlag(); }
	bool GetRHandAttackFlag() { return hand_r.GetAttackFlag(); }
	BoundingOrientedBox GetLHandCollision() { return hand_l.GetLHandCollision(); }
	BoundingOrientedBox GetRHandCollision() { return hand_r.GetRHandCollision(); }

private:
	DX9::MODEL boss_body;

	SimpleMath::Vector3 body_pos;
	DX9::MODEL boss_core;
	SimpleMath::Vector3 core_pos;

	BossHandL hand_l;
	BossHandR hand_r;

};