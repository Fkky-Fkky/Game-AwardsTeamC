#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include <Classes/Enemy/Boss/Boss.h>

using namespace DirectX;

class Ground {
public:
	Ground() {};
	~Ground() {};

	void LoadAssets();
	void Update(Boss* boss);
	void Render();
	void Render2D();

private:
	DX9::MODEL stage_flooring_;
	DX9::MODEL stage_cloud_;
	DX9::MEDIARENDERER bg_vortex_;

	const float CLOUD_POS_Y_  = -2.0f;
	const float VORTEX_POS_Y_ = -20.0f;
	const float VORTEX_POS_Z_ = 10000.0f;
};