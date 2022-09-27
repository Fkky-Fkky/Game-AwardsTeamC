#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"

/**
* @brief �l�̏�����
*/
void HandManager::Initialize() {
	hand_l.Initialize();
	hand_r.Initialize();
	std::random_device seed;
	random_engine_	  = std::mt19937(seed());
	random_hand_dist_ = std::uniform_int_distribution<>(ROCK, PAPER);
	
	hand_state_		= ROCK;
	old_hand_state_ = PAPER;
	same_handstate_flag_ = false;
}

/**
* @brief ��̃��f���ǂݍ���
*/
void HandManager::LoadAssets() {
	hand_l.LoadAssets();
	hand_r.LoadAssets();
}

/**
* @brief ��̍X�V
* 
* @param[in] deltaTime ����
*/
void HandManager::Update(const float deltaTime) {
	hand_l.Update(deltaTime);
	hand_r.Update(deltaTime);
}

/**
* @brief ��̕`��
*/
void HandManager::Render()const {
	hand_l.Render();
	hand_r.Render();
}

/**
* @brief ��̏�Ԃ�ύX����(�O�[�E�p�[)
* 
* 2�A��������Ԃ������ꍇ�����Е��̏�Ԃɂ���
* �A���@�����U�����̂݃O�[�ɌŒ肷��
* @param[in] is_rush �s����U�����A���@�����U����
*/
void HandManager::RandomHandState(const bool is_rush) {
	if (same_handstate_flag_) {
		hand_state_ = (old_hand_state_ == ROCK) ? PAPER : ROCK;
		same_handstate_flag_ = false;
	}
	else {
		hand_state_ = random_hand_dist_(random_engine_);
	}

	if (is_rush) {
		hand_state_ = ROCK;
	}

	if (hand_state_ == old_hand_state_) {
		same_handstate_flag_ = true;
	}

	old_hand_state_ = hand_state_;
}