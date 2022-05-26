#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class ObjectManager;

using namespace DirectX;

class Ground {
public:
	Ground() {
		crack_level_ = 0;
	}
	~Ground() {};

	void LoadAssets();
	void Update(const float deltaTime, ObjectManager* object);
	void Render();
	void Render2D();

private:
	DX9::MODEL stage_flooring_;
	DX9::MODEL stage_bed_;
	DX9::SKINNEDMODEL building_block;
	//DX9::SPRITE crack_[4];
	DX9::MEDIARENDERER bgm_main_;

	int crack_level_;

	const float BED_POS_Y_ = -4.5f;
	const float BED_POS_Z_ = 12.0f;
	const float CRACK_POS_Z_  = 10000.0f;
};