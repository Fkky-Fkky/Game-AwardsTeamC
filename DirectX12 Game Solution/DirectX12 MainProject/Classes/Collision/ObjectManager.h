#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#include "Classes/Player/Player.h"
#include "Classes/Enemy/Boss/Boss.h"

using namespace DirectX;

class ObjectManager {
public:
	//void SetPlayer(Player* p_);
	//void SetBoss(Boss* b_);
	//Player* GetPlayer() { return player_; }
	//Boss* GetBoss() { return boss_; }
	void Initialize();

private:
	//Player* player_;
	//Boss*  boss_;
};