#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class Player;
class Boss;
class Collision;

using namespace DirectX;

class ObjectManager {
public:
	void SetPlayer(Player* p_);
	void SetBoss(Boss* b_);
	void SetCollision(Collision* col_);
	BoundingOrientedBox GetPlayerCollision();
	BoundingOrientedBox GetPlayerAttackCollision();
	BoundingOrientedBox GetBossCoreCollision();
	BoundingOrientedBox GetBossRHandCollision();
	BoundingOrientedBox GetBossLHandCollision();
	int GetBossHP();
	float GetPlayerHP();
	bool GetPlayerAttackFlag();
	bool GetPlayerDmgFlag();
	bool IsPlayerInvincible();
	bool GetBossRAttackFlag();
	bool GetBossLAttackFlag();
	bool GetBossDmgFlag();
	bool IsBossHandOpen();
	bool IsBossHandRDmg();
	bool IsBossHandLDmg();
	bool IsGroundShake();
	SimpleMath::Vector3 GetPlayerPos();

private:
	Player* player_;
	Boss*  boss_;
	Collision* collision_;
};