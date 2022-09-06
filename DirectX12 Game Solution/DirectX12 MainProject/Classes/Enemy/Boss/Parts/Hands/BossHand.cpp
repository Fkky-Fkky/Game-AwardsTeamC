#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"
#include <Bezier.h>

void BossHand::Initialize(const SimpleMath::Vector3 pos, const SimpleMath::Vector3 rote) {
	BossParts::Initialize(pos, rote);
	bezier_t = 0.0f;
	hand_hp_ = HAND_HP_MAX_;
}

void BossHand::LoadAssets(const LPCWSTR file_name){
	BossParts::LoadAssets(file_name);
	model_->SetScale(0.8f);

	collision = model_->GetBoundingOrientedBox();
	collision.Extents = SimpleMath::Vector3(
		collision.Extents.x * 1.7f,
		collision.Extents.y * 0.8f,
		collision.Extents.z * 2.0f
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
	//model_->SetTrackEnable(WAIT, true);
}

void BossHand::Update(const float deltaTime) {
	BossParts::Update(deltaTime);
	timde_delta_ = deltaTime;
	collision.Center = model_->GetPosition() + SimpleMath::Vector3(-1.5f, 0.0f, 0.0f);
	collision.Orientation = model_->GetRotationQuaternion();
	PlayMotion();
}

void BossHand::Render() const {
	BossParts::Render();

	collision_model->SetPosition(collision.Center);
	collision_model->SetRotationQuaternion(collision.Orientation);
	collision_model->Draw();
}

void BossHand::Render2D(const float pos_x) const {
	DX9::SpriteBatch->DrawString(
		font_.Get(),
		SimpleMath::Vector2(pos_x, 150.0f),
		DX9::Colors::Red,
		L"%i", hand_hp_
	);
}

void BossHand::HandDamageProcess() {	//手にダメージを与える
	hand_hp_--;
}

void BossHand::HandHPHeal() {	//手のHPを全回復する
	hand_hp_ = HAND_HP_MAX_;
}

void BossHand::SetHandMotion(const int hand_motion) {	//モーションをセットする
	motion_track_ = hand_motion;
	switch (motion_track_) {
	case ROCK_BACK:
	case PAPER_BACK:
		motion_time_max_ = BACK_MOTION_TIME_;
		break;
	case ROCK:
	case PAPER:
		motion_time_max_ = ATK_MOTION_TIME_;
		break;
	}
	MotionStart();
	if (motion_track_ == WAIT) {
		HandMotionWait();
		motion_flag_ = false;
	}
}

void BossHand::MotionStart() {	//モーションを再生させる
	MotionReset();
	motion_flag_ = true;
}

void BossHand::MotionReset() {	//指定モーション以外をリセットする
	for (int i = 0; i < MOTION_MAX_; ++i) {
		if (i == motion_track_) {
			continue;
		}
		model_->SetTrackEnable(i, false);
		model_->SetTrackPosition(i, 0.0f);
	}
	motion_time_ = 0.0f;
}

void BossHand::PlayMotion() {	//モーション再生
	if (!motion_flag_) {
		return;
	}
	HandMotionAttack();
}

void BossHand::HandMotionAttack() {	//攻撃モーション
	motion_time_ = std::min(motion_time_ + timde_delta_, motion_time_max_);
	if (motion_time_ >= motion_time_max_) {
		model_->SetTrackEnable(motion_track_, false);
		motion_flag_ = false;
	}
	else {
		model_->SetTrackEnable(motion_track_, true);
	}
}

void BossHand::HandMotionWait() const {	//待機モーション
	model_->SetTrackEnable(WAIT, true);
}