#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

class UI {
public:
	UI() {
		player_side_shake_	   = 0;
		player_vertical_shake_ = 0;
		boss_side_shake_	 = 0;
		boss_vertical_shake_ = 0;
		player_hp_width_ = 0.0f;
		boss_hp_width_	 = 0.0f;
		time_delta_		 = 0.0f;
		old_player_hp_	 = 0.0f;
		old_boss_hp_	 = 0.0f;
		player_shake_time_ = 0.0f;
		boss_shake_time_   = 0.0f;
		is_player_damage_ = false;
		is_boss_damage_	  = false;
		player_hp_pos_ = SimpleMath::Vector3::Zero;
		boss_hp_pos_   = SimpleMath::Vector3::Zero;
	}
	~UI() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render() const;

private:
	void PlayerUIShake();
	void BossUIShake();

	DX9::SPRITE player_hp_top_;
	DX9::SPRITE player_hp_bottom_;
	DX9::SPRITE boss_hp_top_;
	DX9::SPRITE boss_hp_bottom_;
	
	int player_side_shake_;
	int player_vertical_shake_;
	int boss_side_shake_;
	int boss_vertical_shake_;
	float player_hp_width_;
	float boss_hp_width_;
	float time_delta_;
	float old_player_hp_;
	float old_boss_hp_;
	float player_shake_time_;
	float boss_shake_time_;
	bool is_player_damage_;
	bool is_boss_damage_;
	SimpleMath::Vector3 player_hp_pos_;
	SimpleMath::Vector3 boss_hp_pos_;

	enum SHAKE_STATE_ {
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

	const int PLAYER_HP_HIGHT_ = 30;
	const int BOSS_HP_HIGHT_   = 30;
	const float PLAYER_HP_POS_X_ = 50.0f;
	const float PLAYER_HP_POS_Y_ = 680.0f;
	const float BOSS_HP_POS_X_ = 190.0f;
	const float BOSS_HP_POS_Y_ = 30.0f;
	const float PLAYER_HP_WIDTH_DIVIDE_ = 11.3f;	//HPÉQÅ[ÉW1/30ÇÃêî
	const float BOSS_HP_WIDTH_DIVIDE_ = 30.0f;
	const float HP_SPEED_ = 300.0f;
};