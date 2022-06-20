#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

class Collision {
public:
	Collision() {
		player_dmg_flag_r_ = false;
		player_dmg_flag_l_ = false;
		boss_dmg_flg_	   = false;
		boss_hand_r_dmg_flag_ = false;
		boss_hand_l_dmg_flag_ = false;
		is_boss_hand_open_	  = false;
	}

	~Collision() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, ObjectManager* obj_m_);
	void Render2D();
	bool GetPlayerDmgFlagR() { return player_dmg_flag_r_; }
	bool GetPlayerDmgFlagL() { return player_dmg_flag_l_; }
	bool GetBossDmgFlag() { return boss_dmg_flg_; }

private:

	bool player_dmg_flag_r_; 
	bool player_dmg_flag_l_;
	bool boss_dmg_flg_;
	bool boss_hand_r_dmg_flag_;
	bool boss_hand_l_dmg_flag_;
	bool is_boss_hand_open_;
	DX9::SPRITEFONT font;
};