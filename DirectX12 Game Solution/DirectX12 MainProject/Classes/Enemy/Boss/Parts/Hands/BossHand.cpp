#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"

/**
* @brief ���f���̓ǂݍ���
* 
* ���f���̃T�C�Y�ύX
* �R���W�����̃T�C�Y�ύX
* ���[�V�����̏�����
* @param[in] file_name �ǂݍ��ރt�@�C����
*/
void BossHand::LoadAssets(const LPCWSTR file_name){
	BossParts::LoadAssets(file_name);
	model_->SetScale(HAND_SCALE);

	collision_ = model_->GetBoundingOrientedBox();
	collision_.Extents = SimpleMath::Vector3(
		collision_.Extents.x * COLLSION_SIZE_X_,
		collision_.Extents.y * COLLSION_SIZE_Y_,
		collision_.Extents.z * COLLSION_SIZE_Z_
	);

	for (int i = 0; i < MOTION_MAX_; ++i) {
		model_->SetTrackEnable(i, false);
	}
}

/**
* @brief BossHand�̍X�V
* 
* @param[in] deltaTime ����
*/
void BossHand::Update(const float deltaTime) {
	BossParts::Update(deltaTime);
	timde_delta_ = deltaTime;
	PlayMotion();
	if (is_death_motion_) {
		motion_stop_time_ = std::max(motion_stop_time_ - timde_delta_, 0.0f);
		if (motion_stop_time_ <= 0.0f) {
			model_->SetTrackEnable(motion_track_, false);
		}
	}
}

/**
* @brief ���[�V�������Z�b�g����
* 
* @param[in] hand_motion �Đ����郂�[�V�����̃g���b�N
*/
void BossHand::SetHandMotion(const int hand_motion) {
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

/**
* @brief ���[�V�������Đ�������
*/
void BossHand::MotionStart() {
	MotionReset();
	motion_flag_ = true;
}

/**
* @brief �w�胂�[�V�����ȊO�����Z�b�g����
*/
void BossHand::MotionReset() {
	for (int i = 0; i < MOTION_MAX_; ++i) {
		if (i == motion_track_) {
			continue;
		}
		model_->SetTrackEnable(i, false);
		model_->SetTrackPosition(i, 0.0f);
	}
	motion_time_ = 0.0f;
}

/**
* @brief ���[�V�����̍Đ�
*/
void BossHand::PlayMotion() {
	if (!motion_flag_) {
		return;
	}
	HandMotionAttack();
}

/**
* @brief �U�����[�V�����̊Ǘ�
*/
void BossHand::HandMotionAttack() {
	motion_time_ = std::min(motion_time_ + timde_delta_, motion_time_max_);
	if (motion_time_ >= motion_time_max_) {
		model_->SetTrackEnable(motion_track_, false);
		motion_flag_ = false;
	}
	else {
		model_->SetTrackEnable(motion_track_, true);
	}
}

/**
* @brief �ҋ@���[�V�����̊Ǘ�
*/
void BossHand::HandMotionWait() const {
	model_->SetTrackEnable(WAIT, true);
}

/**
* @brief �{�X���S���̃��[�V�����Ǘ�
*/
void BossHand::PlayDeathMotion() {
	is_death_motion_ = true;
	SetHandMotion(WAIT);
	motion_stop_time_ = STOP_TIME_;
}