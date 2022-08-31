#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class ObjectManager;

using namespace DirectX;

class Ground {
public:
	Ground() { 
		mist_pos_ = SimpleMath::Vector3::Zero; 
	}
	~Ground() {};

	void LoadAssets();
	void Update(const float deltaTime, ObjectManager* object);
	void Render();
	void Render2D();

private:
	DX9::MODEL stage_;
	DX9::SPRITE bg_;
	DX9::SPRITE mist_;
	DX9::MEDIARENDERER bgm_main_;

	SimpleMath::Vector3 mist_pos_;
	const float STAGE_POS_X_ = 35.0f;
	const float STAGE_POS_Z_ = -40.0f;
	const float STAGE_SCALE_ = 7.0f;
	const float BOSS_BG_POS_Z_ = 10000.0f;
	const float MIST_POS_Z_ = 9999.0f;
};