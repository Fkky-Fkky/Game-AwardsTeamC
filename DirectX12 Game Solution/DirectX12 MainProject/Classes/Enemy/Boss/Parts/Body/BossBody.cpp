#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"
#include "Classes/Object/ObjectManager.h"
#include "Classes/Enemy/Boss/Boss.h"

void boss::BossBody::Initialize() {
	BossParts::Initialize(
		SimpleMath::Vector3(0.0f, BODY_INIT_POS_Y_, BODY_INIT_POS_Z_),
		SimpleMath::Vector3(BODY_INIT_ROT_X_, 0.0f, 0.0f)
	);
	time_delta_		= 0.0f;
	shake_time_		= 0.0f;
	body_jump_y_	= 0.0f;
	body_jump_time_ = 0.0f;
	is_weak_  = false;
	is_shake_ = false;
	shake_set_flag_ = false;
	is_body_death_	= false;
	is_shake_reset_ = false;
	is_start_pos_	= false;
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

	model_->SetTrackEnable(0, true);
}

void boss::BossBody::Update(const float deltaTime, const ObjectManager* const obj_m, Boss* const boss) {
	BossParts::Update(deltaTime);
	time_delta_ = deltaTime;
	is_weak_ = obj_m->IsBossWeak();
	SimpleMath::Vector3 player_pos_ = obj_m->GetPlayerPos();

	if (!is_start_pos_) {
		AdventAction();
		return;
	}

	if (boss->GetBossHP() <= 0.0f) {
		if(!is_shake_reset_){
			is_shake_reset_ = true;
			shake_time_ = 0.0f;
			is_shake_ = false;
			shake_set_flag_ = false;
		}
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

void boss::BossBody::AdventAction() {	//登場時の動き
	position.y	  = std::max(position.y - ADVENT_SPEED_ * time_delta_, BODY_START_POS_Y_);
	is_start_pos_ = position.y <= BODY_START_POS_Y_;
	body_coll_.Center = model_->GetPosition();
	body_coll_.Orientation = model_->GetRotationQuaternion();
}

void boss::BossBody::WeakAction() {	//ウィーク状態時の動き
	if (is_weak_) {
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
		position.y = std::min(position.y + BODY_UP_SPEED_Y_ * time_delta_, BODY_START_POS_Y_);
		position.z = std::min(position.z + MOVE_SPEED_Z_	* time_delta_, BODY_INIT_POS_Z_);
		rotation.x = std::max(rotation.x - ROTATION_SPEED_  * time_delta_, BODY_INIT_ROT_X_);
		body_jump_time_ = 0.0f;
		body_jump_y_	= 0.0f;
		shake_set_flag_ = false;
	}
}

void boss::BossBody::DeathAction() {	//HPが0になった時の動き
	model_->SetTrackEnable(0, false);

	body_jump_time_ += time_delta_;
	body_jump_y_ = JUMP_SPEED_ * body_jump_time_ - HALF_ * GRAVITY_ * body_jump_time_ * body_jump_time_;
	position.y += body_jump_y_;
	if (position.y <= BODY_DEATH_POS_Y_) {
		position.y = BODY_DEATH_POS_Y_;
	}

	position.z = std::min(position.z + MOVE_SPEED_Z_  * time_delta_, BODY_INIT_POS_Z_);
	rotation.x = std::min(rotation.x + DEATH_ROTATION_SPEED_ * time_delta_, DEATH_ROTATION_X_);

	bool is_death_pos_ = position.y <= BODY_DEATH_POS_Y_ && position.z >= BODY_INIT_POS_Z_;
	bool is_death_rot_ = rotation.x >= DEATH_ROTATION_X_;
	bool is_body_death_set_ = is_death_pos_ && is_death_rot_;
	if (is_body_death_set_ && !shake_set_flag_) {
		shake_set_flag_ = true;
		is_shake_		= true;
		shake_time_		= SHAKE_TIME_MAX_;
		is_body_death_	= true;
	}
}