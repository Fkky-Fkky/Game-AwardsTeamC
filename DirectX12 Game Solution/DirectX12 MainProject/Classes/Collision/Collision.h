#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

class Collision {
public:
	Collision();
	~Collision() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, ObjectManager* obj_m_);
	void Render2D();
	bool GetPlyerDmgFlag() { return player_dmg_flg_; }
	bool GetBossDmgFlag() { return boss_dmg_flg_; }

private:

	bool player_dmg_flg_;
	bool boss_dmg_flg_;
	DX9::SPRITEFONT font;
};