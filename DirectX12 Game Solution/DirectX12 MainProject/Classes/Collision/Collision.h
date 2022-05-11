#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include <Classes/Collision/ObjectManager.h>


using namespace DirectX;

class Collision {
public:
	Collision();
	~Collision() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, ObjectManager& obj_m_);
	void Render2D();
	bool GetHitFlag() { return hit_flg_; }
	bool GetHitAttackFlag() { return hit_attack_flg_; }

private:

	bool hit_flg_;
	bool hit_attack_flg_;
	DX9::SPRITEFONT font;
};