#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

class UI {
public:
	UI();
	~UI() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, ObjectManager* obj_m);
	void Render();

private:
	DX9::SPRITE player_hp_top_;
	DX9::SPRITE player_hp_bottom_;
	DX9::SPRITE boss_hp_top_;
	DX9::SPRITE boss_hp_bottom_;
	float player_hp_width_;
	float boss_hp_width_;

	SimpleMath::Vector3 player_hp_pos_;
	SimpleMath::Vector3 boss_hp_pos_;

	const int PLAYER_HP_HIGHT_ = 30;
	const int BOSS_HP_HIGHT_ = 30;
	const float PLAYER_HP_MAX_WIDTH_ = 340.0f;
	const float PLAYER_HP_WIDTH_DIVIDE_ = 11.3f;	//HPÉQÅ[ÉW1/30ÇÃêî
	const float PLAYER_HP_TOP_POS_Z_ = -1.0f;
	const float BOSS_HP_MAX_WIDTH_ = 900.0f;
	const float BOSS_HP_WIDTH_DIVIDE_ = 30.0f;
	const float PLAYER_HP_POS_X_ = 50.0f;
	const float PLAYER_HP_POS_Y_ = 680.0f;
	const float BOSS_HP_POS_X_ = 190.0f;
	const float BOSS_HP_POS_Y_ = 30.0f;

};