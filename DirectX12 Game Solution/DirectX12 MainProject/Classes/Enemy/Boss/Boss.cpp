#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Object/ObjectManager.h"

/**
* @brief 値の初期化
*/
void Boss::Initialize() {
	status_.Initialize();
	body_.Initialize();
	action_.Initialize();
}

/**
* @brief 各モデルの読み込み
*/
void Boss::LoadAseets() {
	body_.LoadAssets();
	action_.LoadAssets();
}

/**
* @brief 各パーツの更新
* 
* @param[in] deltaTime 時間
* @param[in] obj_m オブジェクトマネージャー
*/
void Boss::Update(const float deltaTime, const ObjectManager* const obj_m) {
	body_.Update(deltaTime, obj_m, this);
	status_.Update(deltaTime, obj_m);
	action_.Update(deltaTime, obj_m);
}

/**
* @brief 各パーツ描画
*/
void Boss::Render() const {
	body_.Render();
	action_.Render();
}