#include "Classes/Enemy/Boss/BossHandL.h"
#include "Classes/Enemy/Boss/BossAttack.h"

void BossHandL::Initialize() {
	BossParts::Initialize(
		SimpleMath::Vector3(INITIAL_POS_X, 0.0f, 0.0f),
		SimpleMath::Vector3(-30.0f, -5.0f, 0.0f)
	);
	slap_time = 0.0f;
	beat_time = 0.0f;
	time_delta = 0.0f;
	hand_return_flag = false;
}

void BossHandL::LoadAssets() {
	BossParts::LoadAssets(L"Boss/boss_hand_L.X");

	left_hand_obb = model->GetBoundingOrientedBox();
	left_hand_obb.Extents = SimpleMath::Vector3(left_hand_obb.Extents) * 0.2f;

	left_hand_obb_model = DX9::Model::CreateBox(
		DXTK->Device9,
		left_hand_obb.Extents.x,
		left_hand_obb.Extents.y,
		left_hand_obb.Extents.z
	);
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(0.0f, 1.0f, 0.0f, 0.75f);
	left_hand_obb_model->SetMaterial(material);
}

void BossHandL::Update(const float deltaTime) {
	time_delta = deltaTime;
	left_hand_obb.Center = model->GetPosition();
	left_hand_obb.Orientation = model->GetRotationQuaternion();
}

void BossHandL::Render() {
	BossParts::Render();
	left_hand_obb_model->SetPosition(left_hand_obb.Center);
	left_hand_obb_model->SetRotationQuaternion(left_hand_obb.Orientation);
	left_hand_obb_model->Draw();
}

void BossHandL::LeftSlap(BossAttack* bossattack) {
	slap_time += time_delta;
	position.x += SLAP_SPEED * slap_time - HALF * SLAP_GRAVITY * slap_time * slap_time;

	if (position.x <= -300.0f) {
		position.x = 300.0f;
		hand_return_flag = true;
	}

	if (position.x <= INITIAL_POS_X && hand_return_flag) {
		position.x = INITIAL_POS_X;
		slap_time = 0.0f;
		hand_return_flag = false;
		bossattack->SetBossState(0);
	}
}

void BossHandL::LeftBeat(BossAttack* bossattack) {
	beat_time += time_delta;
	rotation.x -= 2.0f * time_delta;
	if (rotation.x <= -31.5f) {
		rotation.x = -31.5f;
	}

	position.y += BEAT_SPEED * beat_time - HALF * BEAT_GRAVITY * beat_time * beat_time;

	if (position.y <= -30.0f) {
		position.y = -30.0f;
		beat_time = 0.0f;
		bossattack->SetBossState(0);
	}
}