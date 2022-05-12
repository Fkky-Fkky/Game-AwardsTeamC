#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class ObjectManager;

using namespace DirectX;

class Ground {
public:
	Ground();
	~Ground() {};

	void LoadAssets();
	void Update(ObjectManager* object);
	void Render();
	void Render2D();

private:
	DX9::MODEL stage_flooring_;
	DX9::MODEL stage_bed_;
	//DX9::MEDIARENDERER bg_vortex_;
	DX9::SPRITE crack_[4];

	int crack_level_;

	const float BED_POS_Y_ = -4.5f;
	const float BED_POS_Z_ = 12.0f;
	const float VORTEX_POS_Y_ = -20.0f;
	const float VORTEX_POS_Z_ = 10000.0f;
	const float CRACK_POS_Z_  = 10000.0f;
};