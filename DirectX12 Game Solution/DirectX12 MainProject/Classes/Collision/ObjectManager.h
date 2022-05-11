#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class Player;
class Boss;

using namespace DirectX;

class ObjectManager {
public:
	void SetPlayer(Player* p_);
	void SetBoss(Boss* b_);
	BoundingOrientedBox GetPlayerCollision();
	BoundingOrientedBox GetPlayerAttackCollision();
	BoundingOrientedBox GetBossCoreCollision();
	BoundingOrientedBox GetBossRHandCollision();
	BoundingOrientedBox GetBossLHandCollision();
	bool GetPlayerAttackFlag();
	bool GetBossRAttackFlag();
	bool GetBossLAttackFlag();

private:
	Player* player_;
	Boss*  boss_;
};