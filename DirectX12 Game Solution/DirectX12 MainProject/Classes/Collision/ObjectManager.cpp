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

BoundingOrientedBox ObjectManager::GetPlayerCollision() {
	return player_->GetPlayerCollision();
}

BoundingOrientedBox ObjectManager::GetPlayerAttackCollision() {
	return player_->GetPlayerAttackCollision();
}

BoundingOrientedBox ObjectManager::GetBossCoreCollision() {
	return boss_->GetCoreCollision();
}

BoundingOrientedBox ObjectManager::GetBossRHandCollision() {
	return boss_->GetRHandCollision();
}

BoundingOrientedBox ObjectManager::GetBossLHandCollision() {
	return boss_->GetLHandCollision();
}

float ObjectManager::GetBossHP() {
	return boss_->GetBossHP();
}

float ObjectManager::GetPlayerHP() {
	return player_->GetPlayerHP();
}

bool ObjectManager::GetPlayerAttackFlag() {
	return player_->IsPlayerAttack();
}

bool ObjectManager::GetPlayerDmgFlag() {
	if (collision_->GetPlayerDmgFlagR() ||
		collision_->GetPlayerDmgFlagL()) {
		return true;
	}
	else {
		return false;
	}
}

bool ObjectManager::IsPlayerInvincible() {
	return player_->IsPlayerInvincible();
}

bool ObjectManager::GetBossRAttackFlag() {
	return boss_->GetRHandAttackFlag();
}

bool ObjectManager::GetBossLAttackFlag() {
	return boss_->GetLHandAttackFlag();
}

bool ObjectManager::GetBossDmgFlag() {
	return collision_->GetBossDmgFlag();
}

bool ObjectManager::IsBossHandOpen() {
	return boss_->GetHandState();
}

bool ObjectManager::IsBossHandRDmg() {
	return collision_->IsBossHandRDmg();
}

bool ObjectManager::IsBossHandLDmg() {
	return collision_->IsBossHandLDmg();
}

bool ObjectManager::IsGroundVerticalShake() {
	return boss_->IsVerticalShake();
}

bool ObjectManager::IsGroundSideShake() {
	return boss_->IsSideShake();
}

SimpleMath::Vector3 ObjectManager::GetPlayerPos() {
	return player_->GetPlayerPosition();
}