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
	void Update(const float deltaTime, ObjectManager obj_m);
	void Render();

private:
	DX9::SPRITE player_hp_top_;
	DX9::SPRITE player_hp_bottom_;

	const int PLAYER_HP_HIGHT = 71;
	const float PLAYER_HP_MAX_WIDTH = 1021.0f;

};