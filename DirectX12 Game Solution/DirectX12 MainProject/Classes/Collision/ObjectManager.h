#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class Player;
class Boss;
class Collision;

using namespace DirectX;

class ObjectManager {
public:
	void SetPlayer(Player* const p_);
	void SetBoss(Boss* const b_);
	void SetCollision(Collision* const col_);
	BoundingOrientedBox GetPlayerCollision()const;
	BoundingOrientedBox GetPlayerAttackCollision()const;
	BoundingOrientedBox GetBossCoreCollision()const;
	BoundingOrientedBox GetBossRHandCollision()const;
	BoundingOrientedBox GetBossLHandCollision()const;
	float GetBossHP()const;
	float GetPlayerHP()const;
	bool GetPlayerAttackFlag()const;
	bool GetPlayerDmgFlag()const;
	bool IsPlayerInvincible()const;
	bool GetBossRAttackFlag()const;
	bool GetBossLAttackFlag()const;
	bool GetBossDmgFlag()const;
	bool IsBossHandOpen()const;
	bool IsBossHandRDmg()const;
	bool IsBossHandLDmg()const;
	bool IsGroundVerticalShake()const;
	bool IsGroundSideShake()const;
	SimpleMath::Vector3 GetPlayerPos()const;

private:
	Player* player_;
	Boss*  boss_;
	Collision* collision_;
};