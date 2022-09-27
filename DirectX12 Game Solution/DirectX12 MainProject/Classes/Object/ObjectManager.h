/**
* @file ObjectManager.h
* @brief プレイヤーとボスのパラメータ受け渡し処理クラス
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

class Player;
class Boss;
class Collision;

using namespace DirectX;

/**
* @brief ObjectManagerクラス定義
*/
class ObjectManager {
public:
	void SetPlayer(Player* const player);
	void SetBoss(Boss* const boss);
	void SetCollision(Collision* const collision);
	BoundingOrientedBox GetPlayerCollision()const;
	BoundingOrientedBox GetPlayerAttackCollision()const;
	BoundingOrientedBox GetBossBodyCollision()const;
	BoundingOrientedBox GetBossRHandCollision()const;
	BoundingOrientedBox GetBossLHandCollision()const;
	float GetBossHP()const;
	float GetPlayerHP()const;
	bool IsPlayerAttack()const;
	bool IsPlayerDmg()const;
	bool IsPlayerDeath()const;
	bool IsBossRAttack()const;
	bool IsBossLAttack()const;
	bool IsBossBodyDmg()const;
	bool IsBossHandOpen()const;
	bool IsBossHandDmg()const;
	bool IsBossWeak()const;
	bool IsBossDeath()const;
	bool IsCameraVerticalShake()const;
	bool IsCameraSideShake()const;
	SimpleMath::Vector3 GetPlayerPos()const;

private:
	Player* player_; /**< プレイヤー格納 */
	Boss*  boss_; /**< ボス格納 */
	Collision* collision_; /**< コリジョン格納 */
};