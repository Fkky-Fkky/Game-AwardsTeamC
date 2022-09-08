#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

class Collision {
public:
	Collision() {
		hand_dmg_flag_reset_time_ = 0.0f;
		player_dmg_flag_r_ = false;
		player_dmg_flag_l_ = false;
		boss_body_dmg_flg_	  = false;
		boss_hand_r_dmg_flag_ = false;
		boss_hand_l_dmg_flag_ = false;
	}
	~Collision() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m_);
	void Render2D()const;

	bool GetPlayerDmgFlagR() const { return player_dmg_flag_r_; }
	bool GetPlayerDmgFlagL() const { return player_dmg_flag_l_; }
	bool IsBossBodyDmg() const { return boss_body_dmg_flg_; }
	bool IsBossHandRDmg() const { return boss_hand_r_dmg_flag_; }
	bool IsBossHandLDmg() const { return boss_hand_l_dmg_flag_; }

private:
	DX9::SPRITEFONT font;

	float hand_dmg_flag_reset_time_;
	bool player_dmg_flag_r_; 
	bool player_dmg_flag_l_;
	bool boss_body_dmg_flg_;
	bool boss_hand_r_dmg_flag_;
	bool boss_hand_l_dmg_flag_;
};