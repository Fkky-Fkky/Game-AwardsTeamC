#include "Classes/Collision/ObjectManager.h"
#include "Classes/Player/Player.h"
#include "Classes/Enemy/Boss/Boss.h"

void ObjectManager::SetPlayer(Player* p_) {
	player_ = p_;
}

void ObjectManager::SetBoss(Boss* b_) {
	boss_ = b_;
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

float ObjectManager::GetPlayerHP() {
	return player_->GetPlayerHP();
}

bool ObjectManager::GetPlayerAttackFlag() {
	return player_->AttackFlag();
}

bool ObjectManager::GetBossRAttackFlag() {
	return boss_->GetRHandAttackFlag();
}

bool ObjectManager::GetBossLAttackFlag() {
	return boss_->GetLHandAttackFlag();
}