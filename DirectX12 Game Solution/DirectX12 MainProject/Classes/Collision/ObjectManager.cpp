#include "Classes/Collision/ObjectManager.h"

void ObjectManager::Initialize() {

}

void ObjectManager::SetPlayer(Player* p_) {
	player_ = p_;
}

void ObjectManager::SetBoss(Boss* b_) {
	boss_ = b_;
}