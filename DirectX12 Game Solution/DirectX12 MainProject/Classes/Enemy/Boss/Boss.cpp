#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Object/ObjectManager.h"

void Boss::Initialize() {
	status_.Initialize();
	body_.Initialize();
	action_.Initialize();
}

void Boss::LoadAseets() {
	body_.LoadAssets();
	action_.LoadAssets();
}

void Boss::Update(const float deltaTime, const ObjectManager* const obj_m) {
	body_.Update(deltaTime, obj_m, this);
	status_.Update(deltaTime, obj_m);
	action_.Update(deltaTime, obj_m);
}

void Boss::Render() const {
	body_.Render();
	action_.Render();
}