#include "Classes/Enemy/Boss/Parts/BossParts.h"

/**
* @brief 値の初期化
* 
* 仮想関数
* @param[in] pos 座標
* @param[in] rote 回転
*/
void BossParts::Initialize(const SimpleMath::Vector3 pos, const SimpleMath::Vector3 rote) {
	position_ = pos;
	rotation_ = rote;
}

/**
* @brief モデル読み込み
* 
* 仮想関数
* @param[in] file_name 読み込むファイル名
*/
void BossParts::LoadAssets(const LPCWSTR file_name) {
	model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, file_name);
}

/**
* @brief モデルのモーション再生
* 
* 仮想関数
* @param[in] deltaTime 時間
*/
void BossParts::Update(const float deltaTime) {
	model_->AdvanceTime(deltaTime);
}

/**
* @brief モデル描画
* 
* 仮想関数
*/
void BossParts::Render() const {
	model_->SetPosition(position_);
	model_->SetRotation(
		XMConvertToRadians(rotation_.x),
		XMConvertToRadians(rotation_.y),
		XMConvertToRadians(rotation_.z)
	);
	model_->Draw();
}