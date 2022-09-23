#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"
#include "Classes/Object/ObjectManager.h"
#include "Classes/Enemy/Boss/Boss.h"

/**
* @brief 値の初期化
*/
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

/**
* @brief モデルの読み込み
* 
* 当たり判定の設定とモーション再生
*/
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

/**
* @brief Bodyの更新
* 
* @param[in] deltaTime 時間
* @param[out] obj_m オブジェクトマネージャー
* @param[out] boss ボスクラス
*/
void boss::BossBody::Update(const float deltaTime, const ObjectManager* const obj_m, Boss* const boss) {
	BossParts::Update(deltaTime);
	time_delta_ = deltaTime;
	is_weak_ = obj_m->IsBossWeak();
	SimpleMath::Vector3 player_pos_ = obj_m->GetPlayerPos(); /**< プレイヤーの座標 */

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
		rotation_.y = player_pos_.x * -1;
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

/**
* @brief 登場時の動き
*/
void boss::BossBody::AdventAction() {
	position_.y	  = std::max(position_.y - ADVENT_SPEED_ * time_delta_, BODY_START_POS_Y_);
	is_start_pos_ = position_.y <= BODY_START_POS_Y_;
	body_coll_.Center = model_->GetPosition();
	body_coll_.Orientation = model_->GetRotationQuaternion();
}

/**
* @brief ウィーク状態時の動き
*/
void boss::BossBody::WeakAction() {
	if (is_weak_) {
		if (position_.y > BODY_WEAK_POS_Y_) {
			body_jump_time_ += time_delta_;
			body_jump_y_ = JUMP_SPEED_ * body_jump_time_ - HALF_ * GRAVITY_ * body_jump_time_ * body_jump_time_;
			position_.y += body_jump_y_;
		}

		position_.z = std::max(position_.z - MOVE_SPEED_Z_ * time_delta_, BODY_WEAK_POS_Z_);
		rotation_.x = 0.0f;
		rotation_.y = 0.0f;
		if (!shake_set_flag_ && position_.y <= BODY_WEAK_POS_Y_) {
			position_.y = BODY_WEAK_POS_Y_;
			shake_set_flag_ = true;
			is_shake_		= true;
			shake_time_ = SHAKE_TIME_MAX_;
		}
	}
	else {
		position_.y = std::min(position_.y + BODY_UP_SPEED_Y_ * time_delta_, BODY_START_POS_Y_);
		position_.z = std::min(position_.z + MOVE_SPEED_Z_	* time_delta_, BODY_INIT_POS_Z_);
		rotation_.x = std::max(rotation_.x - ROTATION_SPEED_  * time_delta_, BODY_INIT_ROT_X_);
		body_jump_time_ = 0.0f;
		body_jump_y_	= 0.0f;
		shake_set_flag_ = false;
	}
}

/**
* @brief 死亡時の動き
*/
void boss::BossBody::DeathAction() {
	model_->SetTrackEnable(0, false);

	body_jump_time_ += time_delta_;
	body_jump_y_ = JUMP_SPEED_ * body_jump_time_ - HALF_ * GRAVITY_ * body_jump_time_ * body_jump_time_;
	position_.y += body_jump_y_;
	if (position_.y <= BODY_DEATH_POS_Y_) {
		position_.y = BODY_DEATH_POS_Y_;
	}

	position_.z = std::min(position_.z + MOVE_SPEED_Z_  * time_delta_, BODY_INIT_POS_Z_);
	rotation_.x = std::min(rotation_.x + DEATH_ROTATION_SPEED_ * time_delta_, DEATH_ROTATION_X_);

	bool is_death_pos_ = position_.y <= BODY_DEATH_POS_Y_ && position_.z >= BODY_INIT_POS_Z_; /**< 死亡時の座標にいるか */
	bool is_death_rot_ = rotation_.x >= DEATH_ROTATION_X_; /**< 死亡時の回転軸になっているか */
	bool is_body_death_set_ = is_death_pos_ && is_death_rot_; /**< 死亡時の座標と回転になっているか */
	if (is_body_death_set_ && !shake_set_flag_) {
		shake_set_flag_ = true;
		is_shake_		= true;
		shake_time_		= SHAKE_TIME_MAX_;
		is_body_death_	= true;
	}
}