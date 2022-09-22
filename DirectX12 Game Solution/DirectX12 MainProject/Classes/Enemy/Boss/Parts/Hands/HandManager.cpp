#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"

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

void HandManager::LoadAssets() {
	hand_l.LoadAssets();
	hand_r.LoadAssets();
}

void HandManager::Update(const float deltaTime) {
	hand_l.Update(deltaTime);
	hand_r.Update(deltaTime);
}

void HandManager::Render()const {
	hand_l.Render();
	hand_r.Render();
}

void HandManager::RandomHandState() {	//��̏�Ԃ�ύX����(�O�[�E�p�[)
	if (same_handstate_flag_) {	//2�A��������Ԃ������ꍇ�����Е��̏�Ԃɂ���
		hand_state_ = (old_hand_state_ == ROCK) ? PAPER : ROCK;
		same_handstate_flag_ = false;
	}
	else {
		hand_state_ = random_hand_dist_(random_engine_);
	}

	//if (attack_state_ == BEAT_RUSH_R) {	//�A���@�����U���̂݃O�[�ɌŒ肷��
	//	hand_state_ = ROCK;
	//}

	if (hand_state_ == old_hand_state_) {
		same_handstate_flag_ = true;
	}

	old_hand_state_ = hand_state_;
}