#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"
#include <Bezier.h>

void BossHand::Initialize(SimpleMath::Vector3 pos, SimpleMath::Vector3 rote) {
	BossParts::Initialize(pos, rote);
	bezier_t = 0.0f;
	hand_hp_ = HAND_HP_MAX_;
}

void BossHand::LoadAssets(LPCWSTR file_name){
	BossParts::LoadAssets(file_name);
	//model->SetScale(1.0f);

	collision = model_->GetBoundingOrientedBox();
	collision.Extents = SimpleMath::Vector3(
		collision.Extents.x * 0.5f,
		collision.Extents.y * 0.3f,
		collision.Extents.z * 0.5f
	);

	collision_model = DX9::Model::CreateBox(
		DXTK->Device9,
		collision.Extents.x,
		collision.Extents.y,
		collision.Extents.z
	);
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(0.0f, 1.0f, 0.0f, 0.75f);
	collision_model->SetMaterial(material);

	font_ = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
	for (int i = 0; i < MOTION_MAX_; ++i) {
		model_->SetTrackEnable(i, false);
	}
	model_->SetTrackEnable(WAIT, true);
}

void BossHand::Update(const float deltaTime) {
	BossParts::Update(deltaTime);
	timde_delta_ = deltaTime;
	collision.Center = model_->GetPosition();
	collision.Orientation = model_->GetRotationQuaternion();
	PlayMotion();
}

void BossHand::Render(){
	BossParts::Render();

	collision_model->SetPosition(collision.Center);
	collision_model->SetRotationQuaternion(collision.Orientation);
	collision_model->Draw();
}

void BossHand::HandDamageProcess() {
	hand_hp_--;
}

void BossHand::HandHPHeal() {
	hand_hp_ = HAND_HP_MAX_;
}

void BossHand::SetHandMotion(int hand_motion) {
	MotionStart();
	hand_state_ = hand_motion;
}

void BossHand::PlayMotion() {
	if (!motion_flag_) {
		return;
	}
	switch (hand_state_) {
	case ROCK_BACK:		motion_time_max_ = ROCK_BACK_MOTION_TIME_;	break;
	case ROCK:			motion_time_max_ = ROCK_MOTION_TIME_;		break;
	case PAPER_BACK:	motion_time_max_ = ROCK_BACK_MOTION_TIME_;	break;
	case PAPER:			motion_time_max_ = ROCK_MOTION_TIME_;		break;
	case WAIT:			motion_time_max_ = 0.0f;					break;
	}

	if (hand_state_ != WAIT) {
		Rock();
	}
	else {
		HandMotionWait();
	}	
}

void BossHand::Rock() {
	motion_time_ += timde_delta_;
	if (motion_time_ >= motion_time_max_) {
		model_->SetTrackEnable(hand_state_, false);
	}
	else {
		model_->SetTrackEnable(hand_state_, true);
	}
}

void BossHand::MotionReset() {
	for (int i = 0; i < MOTION_MAX_; ++i) {
		model_->SetTrackEnable(i, false);
		model_->SetTrackPosition(i, 0.0f);
	}
	motion_time_ = 0.0f;
}

void BossHand::HandMotionWait() {
	model_->SetTrackEnable(hand_state_, true);
}

void BossHand::MotionStart() {
	MotionReset();
	motion_flag_ = true;
}

void BossHand::Render2D(float pos_x) {
	DX9::SpriteBatch->DrawString(
		font_.Get(),
		SimpleMath::Vector2(pos_x, 150.0f),
		DX9::Colors::Red,
		L"%i", hand_hp_
	);
}


//void BossAttack::SusiZanmai() {
//	r_hand_pos = Bezier::CubicInterpolate(
//		SimpleMath::Vector3(-80.0f, 30.0f, 80.0f),
//		SimpleMath::Vector3(100.0f, 30.0f, 80.0f),
//		SimpleMath::Vector3(-50.0f, 30.0f, 80.0f),
//		SimpleMath::Vector3(-100.0f, -40.0f, 80.0f),
//		bezier_t
//	);
//	l_hand_pos = Bezier::CubicInterpolate(
//		SimpleMath::Vector3(80.0f, 30.0f, 80.0f),
//		SimpleMath::Vector3(-100.0f, 30.0f, 80.0f),
//		SimpleMath::Vector3(50.0f, 30.0f, 80.0f),
//		SimpleMath::Vector3(100.0f, -40.0f, 80.0f),
//		bezier_t
//	);
//	r_hand_rote.x += 1.0f * time_delta;
//	if (r_hand_rote.x >= -28.0f) {
//		r_hand_rote.x = -28.0f;
//	}
//
//	l_hand_rote.x += 1.0f * time_delta;
//	if (l_hand_rote.x >= -28.0f) {
//		l_hand_rote.x = -28.0f;
//	}
//
//	bezier_t += 1.0f / 1.5f * time_delta;//1.5•b‚©‚¯‚ÄƒS[ƒ‹‚ÉŒü‚©‚¤
//	if (r_hand_pos.y <= -40.0f) {
//		bezier_t = 0.0f;
//		boss_state = WAIT;
//	}
//}