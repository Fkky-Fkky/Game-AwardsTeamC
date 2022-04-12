#include "Classes/Enemy/Boss/BossHandR.h"

void BossHandR::Initialize() {
	BossParts::Initialize(
		SimpleMath::Vector3(-80.0f, 30.0f, 80.0f),
		SimpleMath::Vector3(-30.0f, 5.0f, 0.0f)
	);
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
	if (DXTK->KeyState->Right) {
		//r_hand_rote.y += 5.0f * deltaTime;
		position.x += 40.0f * deltaTime;
	}
	if (DXTK->KeyState->Left) {
		//r_hand_rote.y -= 5.0f * deltaTime;
		position.x -= 40.0f * deltaTime;
	}
	if (DXTK->KeyState->Up) {
		rotation.x += 5.0f * deltaTime;
	}
	if (DXTK->KeyState->Down) {
		rotation.x -= 5.0f * deltaTime;
	}

	right_hand_obb.Center = model->GetPosition();
	right_hand_obb.Orientation = model->GetRotationQuaternion();
}

void BossHandR::Render() {
	BossParts::Render();
	right_hand_obb_model->SetPosition(right_hand_obb.Center);
	right_hand_obb_model->SetRotationQuaternion(right_hand_obb.Orientation);
	right_hand_obb_model->Draw();
}

//void BossHandR::RightSlap() {
//	slap_time += time_delta;
//	position.x -= SLAP_SPEED * slap_time - HALF * SLAP_GRAVITY * slap_time * slap_time;
//
//	if (position.x >= 300.0f) {
//		position.x = -300.0f;
//		hand_return_flag = true;
//	}
//
//	if (position.x >= -80.0f && hand_return_flag) {
//		position.x = -80.0f;
//		slap_time = 0.0f;
//		hand_return_flag = false;
//		boss_state = WAIT;
//	}
//}

//void BossHandR::RightBeat() {
//	beat_time += time_delta;
//	rotation.x -= 2.0f * time_delta;
//	if (rotation.x <= -31.5f) {
//		rotation.x = -31.5f;
//	}
//
//	position.y += BEAT_SPEED * beat_time - HALF * BEAT_GRAVITY * beat_time * beat_time;
//
//	if (position.y <= -30.0f) {
//		position.y = -30.0f;
//		beat_time = 0.0f;
//		boss_state = WAIT;
//	}
//}
