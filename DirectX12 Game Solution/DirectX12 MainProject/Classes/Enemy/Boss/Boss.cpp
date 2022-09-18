#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Collision/ObjectManager.h"

void Boss::Initialize() {
	body_.Initialize();
	hand_.Initialize();
	status_.Initialize();
}

void Boss::LoadAseets() {
	body_.LoadAssets();
	hand_.LoadAssets();
}

void Boss::Update(const float deltaTime, const ObjectManager* const obj_m) {
	body_.Update(deltaTime, obj_m, this);
	hand_.Update(deltaTime, obj_m);
	status_.Update(deltaTime, obj_m);
}

void Boss::Render() const {
	body_.Render();
	hand_.Render();
}