#include "Classes/Enemy/Boss/Parts/Hands/RightHand/BossHandR.h"

/**
* @brief 座標と回転の初期化
*/
void boss::BossHandR::Initialize() {
	BossParts::Initialize(
		SimpleMath::Vector3(INITIAL_POS_X_, INITIAL_POS_Y_, INITIAL_POS_Z_),
		SimpleMath::Vector3(INITIAL_ROT_X_, -INITIAL_ROT_Y_, 0.0f)
	);
}

/**
* @brief モデルの読み込み
*/
void boss::BossHandR::LoadAssets() {
	BossHand::LoadAssets(L"Boss/boss_hand_R.X");
}

/**
* @brief コリジョンの更新
* 
* @param[in] deltaTime 時間
*/
void boss::BossHandR::Update(const float deltaTime) {
	BossHand::Update(deltaTime);
	collision_.Center	   = model_->GetPosition() + SimpleMath::Vector3(ADD_COLLISION_POS_X_, 0.0f, 0.0f);
	collision_.Orientation = model_->GetRotationQuaternion();
}