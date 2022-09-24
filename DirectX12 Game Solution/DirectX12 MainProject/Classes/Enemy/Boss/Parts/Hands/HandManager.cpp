#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"

/**
* @brief 値の初期化
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
* @brief 手のモデル読み込み
*/
void HandManager::LoadAssets() {
	hand_l.LoadAssets();
	hand_r.LoadAssets();
}

/**
* @brief 手の更新
* 
* @param[in] deltaTime 時間
*/
void HandManager::Update(const float deltaTime) {
	hand_l.Update(deltaTime);
	hand_r.Update(deltaTime);
}

/**
* @brief 手の描画
*/
void HandManager::Render()const {
	hand_l.Render();
	hand_r.Render();
}

/**
* @brief 手の状態を変更する(グー・パー)
* 
* 2連続同じ状態だった場合もう片方の状態にする
* 連続叩きつけ攻撃時のみグーに固定する
* @param[in] is_rush 行われる攻撃が連続叩きつけ攻撃か
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