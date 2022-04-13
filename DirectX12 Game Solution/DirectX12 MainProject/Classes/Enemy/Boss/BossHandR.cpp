#include "Classes/Enemy/Boss/BossHandR.h"
#include "Classes/Enemy/Boss/BossAttack.h"

void BossHandR::Initialize() {
	BossParts::Initialize(
		SimpleMath::Vector3(INITIAL_POS_X, INITIAL_POS_Y, 0.0f),
		SimpleMath::Vector3(XM_PIDIV4, 5.0f, 0.0f)
	);
	slap_time = 0.0f;
	beat_time = 0.0f;
	time_delta = 0.0f;
	wait_time = 0.0f;
	hand_return_flag = false;
}

void BossHandR::LoadAssets() {
	BossParts::LoadAssets(L"Boss/boss_hand_R.X");

	right_hand_obb = model->GetBoundingOrientedBox();
	right_hand_obb.Extents = SimpleMath::Vector3(right_hand_obb.Extents) * 0.2f;

	right_hand_obb_model = DX9::Model::CreateBox(
		DXTK->Device9,
		right_hand_obb.Extents.x,
		right_hand_obb.Extents.y,
		right_hand_obb.Extents.z
	);
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	right_hand_obb_model->SetMaterial(material);
}

void BossHandR::Update(const float deltaTime) {
	time_delta = deltaTime;
	//if (DXTK->KeyState->Right) {
	//	//r_hand_rote.y += 5.0f * deltaTime;
	//	position.x += 40.0f * deltaTime;
	//}
	//if (DXTK->KeyState->Left) {
	//	//r_hand_rote.y -= 5.0f * deltaTime;
	//	position.x -= 40.0f * deltaTime;
	//}
	//if (DXTK->KeyState->Up) {
	//	//rotation.x += 5.0f * deltaTime;
	//	rotation.x = std::min(rotation.x + 1.0f * time_delta, XM_PIDIV2);
	//}
	//if (DXTK->KeyState->Down) {
	//	//rotation.x -= 5.0f * deltaTime;
	//	rotation.x = std::max(rotation.x - 1.0f * time_delta, -XM_1DIV2PI);
	//}

	right_hand_obb.Center = model->GetPosition();
	right_hand_obb.Orientation = model->GetRotationQuaternion();
}

void BossHandR::Render() {
	BossParts::Render();
	right_hand_obb_model->SetPosition(right_hand_obb.Center);
	right_hand_obb_model->SetRotationQuaternion(right_hand_obb.Orientation);
	right_hand_obb_model->Draw();
}

void BossHandR::RightSlap(BossAttack* bossattack) {
	if (!hand_return_flag) {
		slap_time += time_delta;
		position.x -= SLAP_SPEED * slap_time - HALF * SLAP_GRAVITY * slap_time * slap_time;
		rotation.x = std::min(rotation.x + 1.0f * time_delta, XM_PIDIV2);
	}
	else {
		position.x = std::min(position.x + 10.0f * time_delta, INITIAL_POS_X);
		rotation.x = std::max(rotation.x - 10.0f * time_delta, XM_PIDIV4);
	}


	if (position.x >= 70.0f) {
		position.x = -30.0f;
		hand_return_flag = true;
	}

	if (position.x >= INITIAL_POS_X && hand_return_flag) {
		position.x = INITIAL_POS_X;
		slap_time = 0.0f;
		hand_return_flag = false;
		bossattack->SetBossState(0);
	}
}

void BossHandR::RightBeat(BossAttack* bossattack) {
	//rotation.x -= 2.0f * time_delta;
	//if (rotation.x <= -XM_1DIV2PI) {
	//	rotation.x = -XM_1DIV2PI;
	//}

	if (!hand_return_flag) {
		beat_time += time_delta;
		position.y += BEAT_SPEED * beat_time - HALF * BEAT_GRAVITY * beat_time * beat_time;
		rotation.x = std::max(rotation.x - 1.0f * time_delta, -XM_1DIV2PI);
	}


	if (position.y <= 0.0f) {
		position.y = 0.0f;
		hand_return_flag = true;
	}

	if (hand_return_flag) {
		wait_time += time_delta;
	}

	if (wait_time >= 2.0f) {
		position.y = std::min(position.y + 5.0f * time_delta, INITIAL_POS_Y);
		rotation.x = std::min(rotation.x + 1.0f * time_delta, XM_PIDIV4);
	}

	if (position.y >= INITIAL_POS_Y && hand_return_flag) {
		position.y = INITIAL_POS_Y;
		wait_time = 0.0f;
		beat_time = 0.0f;
		hand_return_flag = false;
		bossattack->SetBossState(0);
	}
}