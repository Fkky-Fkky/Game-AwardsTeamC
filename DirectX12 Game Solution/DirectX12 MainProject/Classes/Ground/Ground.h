#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class ObjectManager;

using namespace DirectX;

class Ground {
public:
	Ground() { 
		mist_pos_ = SimpleMath::Vector3(MIST_INIT_POS_X_, 0.0f, MIST_INIT_POS_Z_);
		bg_change_flag_ = false;
		enemy_bg_alpha_ = COLOR_MAX_;
		miset_speed_ = MIST_MOVE_SPEED_SLOW_;
	}
	~Ground() {};

	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;
	void Render2D()const;

private:
	DX9::MODEL stage_;
	DX9::SPRITE boss_bg_;
	DX9::SPRITE enemy_bg_;
	DX9::SPRITE mist_;
	DX9::MEDIARENDERER bgm_main_;

	SimpleMath::Vector3 mist_pos_;
	bool bg_change_flag_;
	float enemy_bg_alpha_;
	float miset_speed_;

	const float STAGE_POS_X_ = 35.0f;
	const float STAGE_POS_Z_ = -40.0f;
	const float STAGE_SCALE_ = 7.0f;
	const float BOSS_BG_POS_Z_ = 10000.0f;
	const float ENEMY_BG_POS_Z_ = 9999.0f;
	const float MIST_INIT_POS_Z_ = 9998.0f;
	const float MIST_INIT_POS_X_ = -1280.0f;
	const float MIST_MOVE_SPEED_SLOW_ = 100.0f;
	const float MIST_MOVE_SPEED_QUICK_ = 200.0f;
	const float ADD_MIST_SPEED_  = 80.0f;
	const float ADD_ALPHA_SPEED_ = 300.0f;
	const float COLOR_MAX_ = 255.0f;
	const float SPRITE_WIDTH_ = 1280.0f;
	const float SPRITE_HIGHT_ = 720.0f;
	const float BOSS_HP_HALF_ = 15.0f;
};