#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

class SceneChange {
public:
	SceneChange() {
		scene_change_flag_ = false;
	};

	~SceneChange() {};
	void Update(ObjectManager* obj_m);
	bool GetSceneChangeFlag() { return scene_change_flag_; }
private:

	bool scene_change_flag_;
};