/**
* @file ObjectManager.h
* @brief �v���C���[�ƃ{�X�̃p�����[�^�󂯓n�������N���X
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

class Player;
class Boss;
class Collision;

using namespace DirectX;

/**
* @brief ObjectManager�N���X��`
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
	Player* player_; /**< �v���C���[�i�[ */
	Boss*  boss_; /**< �{�X�i�[ */
	Collision* collision_; /**< �R���W�����i�[ */
};