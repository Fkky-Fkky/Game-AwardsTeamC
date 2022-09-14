#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"
#include "Classes/Collision/ObjectManager.h"
#include "Classes/Enemy/Boss/Boss.h"

void boss::BossBody::Initialize() {
	BossParts::Initialize(
		SimpleMath::Vector3(0.0f, BODY_INIT_POS_Y_, BODY_INIT_POS_Z_),
		SimpleMath::Vector3(BODY_INIT_ROT_X_, 0.0f, 0.0f)
	);
	time_delta_ = 0.0f;
	shake_time_ = 0.0f;
	body_jump_time_ = 0.0f;
	is_weak_ = false;
	shake_set_flag_ = false;
}

void boss::BossBody::LoadAssets() {
	BossParts::LoadAssets(L"Boss/boss_head.x");
	model_->SetScale(BODY_SCALE_);
	body_coll_ = model_->GetBoundingOrientedBox();
	body_coll_.Extents = SimpleMath::Vector3(
		body_coll_.Extents.x * COLLISION_SIZE_X_,
		body_coll_.Extents.y,
		body_coll_.Extents.z * COLLISION_SIZE_Z_
	);
	coll_model_ = DX9::Model::CreateBox(
		DXTK->Device9,
		body_coll_.Extents.x,
		body_coll_.Extents.y,
		body_coll_.Extents.z
	);
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	coll_model_->SetMaterial(material);

	model_->SetTrackEnable(0, true);
}

void boss::BossBody::Update(const float deltaTime, const ObjectManager* const obj_m, Boss* const boss) {
	BossParts::Update(deltaTime);
	time_delta_ = deltaTime;
	is_weak_ = obj_m->IsBossWeak();
	SimpleMath::Vector3 player_pos_ = obj_m->GetPlayerPos();
	if (boss->GetBossHP() <= 0.0f) {
		DeathAction();
	}
	else {
		rotation.y = player_pos_.x * -1;
		WeakAction();
	}

	if (is_shake_) {
		shake_time_ = std::max(shake_time_ - deltaTime, 0.0f);
	}
	if (shake_time_ <= 0.0f) {
		is_shake_ = false;
	}

	boss->SetVerticalShake(is_shake_);
	body_coll_.Center = model_->GetPosition();
	body_coll_.Orientation = model_->GetRotationQuaternion();
}

void boss::BossBody::Render() const {
	BossParts::Render();
	coll_model_->SetPosition(body_coll_.Center);
	coll_model_->SetRotationQuaternion(body_coll_.Orientation);
	//coll_model_->Draw();
}

void boss::BossBody::WeakAction() {	//ウィーク状態時の動き
	const float BODY_UP_SPEED_Y_= 10.0f;
	const float MOVE_SPEED_Z_	= 20.0f;
	const float ROTATION_SPEED_ = 10.0f;
	if (is_weak_) {
		const float SHAKE_TIME_MAX_ = 0.2f;
		if (position.y > BODY_WEAK_POS_Y_) {
			body_jump_time_ += time_delta_;
			body_jump_y_ = JUMP_SPEED_ * body_jump_time_ - HALF_ * GRAVITY_ * body_jump_time_ * body_jump_time_;
			position.y += body_jump_y_;
		}

		position.z = std::max(position.z - MOVE_SPEED_Z_ * time_delta_, BODY_WEAK_POS_Z_);
		rotation.x = 0.0f;
		rotation.y = 0.0f;
		if (!shake_set_flag_ && position.y <= BODY_WEAK_POS_Y_) {
			position.y = BODY_WEAK_POS_Y_;
			shake_set_flag_ = true;
			is_shake_		= true;
			shake_time_ = SHAKE_TIME_MAX_;
		}
	}
	else {
		position.y = std::min(position.y + BODY_UP_SPEED_Y_ * time_delta_, BODY_INIT_POS_Y_);
		position.z = std::min(position.z + MOVE_SPEED_Z_	* time_delta_, BODY_INIT_POS_Z_);
		rotation.x = std::max(rotation.x - ROTATION_SPEED_  * time_delta_, BODY_INIT_ROT_X_);
		body_jump_time_ = 0.0f;
		body_jump_y_	= 0.0f;
		shake_set_flag_ = false;
	}
}

void boss::BossBody::DeathAction() {	//HPが0になった時の動き
	const float SHAKE_TIME_MAX_	   = 0.2f;
	const float ROTAION_SPEED_	   = 200.0f;
	const float DEATH_ROTATION_X_  = 40.0f;
	model_->SetTrackEnable(0, false);

	body_jump_time_ += time_delta_;
	body_jump_y_ = JUMP_SPEED_ * body_jump_time_ - HALF_ * GRAVITY_ * body_jump_time_ * body_jump_time_;
	position.y += body_jump_y_;

	rotation.x = std::min(rotation.x + ROTAION_SPEED_ * time_delta_, DEATH_ROTATION_X_);
	if (position.y <= BODY_WEAK_POS_Y_) {
		position.y = BODY_WEAK_POS_Y_;
		if (!shake_set_flag_) {
			shake_set_flag_ = true;
			is_shake_		= true;
			shake_time_		= SHAKE_TIME_MAX_;
			is_body_death_	= true;
		}
	}
}