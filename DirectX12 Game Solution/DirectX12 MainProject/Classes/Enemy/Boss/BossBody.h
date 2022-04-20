#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/BossParts.h"

class BossBody : public BossParts {
public:
	virtual void Initialize();
	virtual void LoadAssets();
	virtual void Render();
};