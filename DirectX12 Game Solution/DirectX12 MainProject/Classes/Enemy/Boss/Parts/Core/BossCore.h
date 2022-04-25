#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/BossParts.h"

class BossCore : public BossParts {
public:
	virtual void Initialize();
	virtual void LoadAssets();
	virtual void Render();
};
