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
	DX9::MODEL stage_;
	DX9::MEDIARENDERER bgm_main_;
	const float STAGE_SCALE_ = 2.0f;
};