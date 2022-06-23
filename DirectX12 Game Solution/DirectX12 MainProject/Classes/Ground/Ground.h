#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class ObjectManager;

using namespace DirectX;

class Ground {
public:
	Ground() {};
	~Ground() {};

	void LoadAssets();
	void Update(const float deltaTime, ObjectManager* object);
	void Render();
	void Render2D();

private:
	DX9::MODEL stage_flooring_;
	DX9::MODEL stage_bed_;
	DX9::MODEL castle;
	DX9::SKINNEDMODEL building_block;
	DX9::MEDIARENDERER bgm_main_;

	const float BED_POS_Y_ = -4.5f;
	const float BED_POS_Z_ = 12.0f;
	const float CASTLE_POS_Y_ = -6.19f;
};