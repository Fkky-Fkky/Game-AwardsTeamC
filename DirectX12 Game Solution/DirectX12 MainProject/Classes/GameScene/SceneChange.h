#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

class SceneChange {
public:
	SceneChange() {
		black_alpha_ = 0.0f;
		white_alpha_ = 0.0f;
		wait_time_	 = 0.0f;
		scene_change_flag_ = false;
		is_game_start_ = false;
		is_game_clear_ = false;
	};

	~SceneChange() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, ObjectManager* obj_m);
	void Render2D();

	bool GetSceneChangeFlag() const { return scene_change_flag_; }
	bool IsGameClear() const { return is_game_clear_; }
	bool IsGameStart() const { return is_game_start_; }
private:
	DX9::SPRITE black_;
	DX9::SPRITE white_;

	float black_alpha_;
	float white_alpha_;
	float wait_time_;
	bool scene_change_flag_;
	bool is_game_start_;
	bool is_game_clear_;

	const int WIDTH_MAX_ = 1280;
	const int HIGHT_MAX_ = 720;
	const float ALPHA_SPEED_  = 180.0f;
	const float COLOR_MAX_	  = 255.0f;
	const float SPRITE_POS_Z_ = -10.0f;
	const float PLAYER_DEAD_WAIT_TIME_MAX_ = 1.5f;
	const float BOSS_DEAD_WAIT_TIME_MAX_   = 1.0f;
};