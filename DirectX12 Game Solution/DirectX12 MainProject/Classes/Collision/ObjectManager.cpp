#include "Classes/Collision/ObjectManager.h"
#include "Classes/Player/Player.h"
#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Collision/Collision.h"

void ObjectManager::SetPlayer(Player* p_) {
	player_ = p_;
}

void ObjectManager::SetBoss(Boss* b_) {
	boss_ = b_;
}

void ObjectManager::SetCollision(Collision* col_) {
	collision_ = col_;
}

BoundingOrientedBox ObjectManager::GetPlayerCollision() const {
	return player_->GetPlayerCollision();
}

BoundingOrientedBox ObjectManager::GetPlayerAttackCollision() const {
	return player_->GetPlayerAttackCollision();
}

BoundingOrientedBox ObjectManager::GetBossCoreCollision() const {
	return boss_->GetCoreCollision();
}

BoundingOrientedBox ObjectManager::GetBossRHandCollision() const {
	return boss_->GetRHandCollision();
}

BoundingOrientedBox ObjectManager::GetBossLHandCollision() const {
	return boss_->GetLHandCollision();
}

float ObjectManager::GetBossHP() const {
	return boss_->GetBossHP();
}

float ObjectManager::GetPlayerHP() const {
	return player_->GetPlayerHP();
}

bool ObjectManager::GetPlayerAttackFlag() const {
	return player_->IsPlayerAttack();
}

bool ObjectManager::GetPlayerDmgFlag() const {
	if (collision_->GetPlayerDmgFlagR() ||
		collision_->GetPlayerDmgFlagL()) {
		return true;
	}
	else {
		return false;
	}
}

bool ObjectManager::IsPlayerInvincible() const {
	return player_->IsPlayerInvincible();
}

bool ObjectManager::GetBossRAttackFlag() const {
	return boss_->GetRHandAttackFlag();
}

bool ObjectManager::GetBossLAttackFlag() const {
	return boss_->GetLHandAttackFlag();
}

bool ObjectManager::GetBossDmgFlag() const {
	return collision_->GetBossDmgFlag();
}

bool ObjectManager::IsBossHandOpen() const {
	return boss_->GetHandState();
}

bool ObjectManager::IsBossHandRDmg() const {
	return collision_->IsBossHandRDmg();
}

bool ObjectManager::IsBossHandLDmg() const {
	return collision_->IsBossHandLDmg();
}

bool ObjectManager::IsGroundVerticalShake() const {
	return boss_->IsVerticalShake();
}

bool ObjectManager::IsGroundSideShake() const {
	return boss_->IsSideShake();
}

SimpleMath::Vector3 ObjectManager::GetPlayerPos() const {
	return player_->GetPlayerPosition();
}