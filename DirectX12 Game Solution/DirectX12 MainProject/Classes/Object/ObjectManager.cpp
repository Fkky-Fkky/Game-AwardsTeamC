#include "Classes/Object/ObjectManager.h"
#include "Classes/Player/Player.h"
#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Collision/Collision.h"

/**
* @brief プレイヤーの設定
* 
* @param[out] player プレイヤークラス
*/
void ObjectManager::SetPlayer(Player* const player) {
	player_ = player;
}

/**
* @brief ボスの設定
* 
* @param[out] boss ボスクラス
*/
void ObjectManager::SetBoss(Boss* const boss) {
	boss_ = boss;
}

/**
* @brief コリジョンの設定
* 
* @param[out] collision コリジョンクラス
*/
void ObjectManager::SetCollision(Collision* const collision) {
	collision_ = collision;
}

/**
* @brief プレイヤーのコリジョン取得
* 
* @return プレイヤーのコリジョン
*/
BoundingOrientedBox ObjectManager::GetPlayerCollision() const {
	return player_->GetPlayerCollision();
}

/**
* @brief プレイヤーの攻撃コリジョン取得
* 
* @return プレイヤーの攻撃コリジョン 
*/
BoundingOrientedBox ObjectManager::GetPlayerAttackCollision() const {
	return player_->GetPlayerAttackCollision();
}

/**
* @brief ボスのコリジョン取得
* 
* @return ボスのコリジョン
*/
BoundingOrientedBox ObjectManager::GetBossBodyCollision() const {
	return boss_->GetBodyCollision();
}

/**
* @brief ボスの右手コリジョン取得
* 
* @return ボス右手コリジョン
*/
BoundingOrientedBox ObjectManager::GetBossRHandCollision() const {
	return boss_->GetRHandCollision();
}

/**
* @brief ボスの左手コリジョン取得
* 
* @return ボス左手コリジョン
*/
BoundingOrientedBox ObjectManager::GetBossLHandCollision() const {
	return boss_->GetLHandCollision();
}

/**
* @ボスのHP取得
* 
* @return ボスのHP
*/
float ObjectManager::GetBossHP() const {
	return boss_->GetBossHP();
}

/**
* @brief プレイヤーのHP取得
* 
* @return プレイヤーのHP
*/
float ObjectManager::GetPlayerHP() const {
	return player_->GetPlayerHP();
}

/**
* @brief プレイヤーか攻撃しているか
* 
* @retval TRUE 攻撃している
* @retval FALSE 攻撃していない
*/
bool ObjectManager::IsPlayerAttack() const {
	return player_->IsPlayerAttack();
}

/**
* @brief プレイヤーがダメージを受けているか
* 
* @retval TRUE 受けた
* @retval FALSE 受けていない
*/
bool ObjectManager::IsPlayerDmg() const {
	return collision_->GetPlayerDmgFlagR() || collision_->GetPlayerDmgFlagL();
}

/**
* @brief プレイヤーが死んでいるか
* 
* @retval TRUE 死んでいる
* @retval FALSE 死んでいない
*/
bool ObjectManager::IsPlayerDeath() const {
	return player_->IsPlayerDeath();
}

/**
* @brief ボス右手が攻撃しているか
* 
* @retval TRUE 攻撃している
* @retval FALSE 攻撃していない
*/
bool ObjectManager::IsBossRAttack() const {
	return boss_->IsRHandAttack();
}

/**
* @brief ボス左手が攻撃しているか
* 
* @retval TRUE 攻撃している
* @retval FALSE 攻撃していない
*/
bool ObjectManager::IsBossLAttack() const {
	return boss_->IsLHandAttack();
}

/**
* @brief ボス本体がダメージを受けているか
* 
* @retval TRUE 受けた
* @retval FALSE 受けていない
*/
bool ObjectManager::IsBossBodyDmg() const {
	return collision_->IsBossBodyDmg();
}

/**
* @brief ボスの手が開いているか
* 
* @retval TRUE 開いている
* @retval FALSE 握っている
*/
bool ObjectManager::IsBossHandOpen() const {
	return boss_->IsHandOpen();
}

/**
* @brief 手がダメージを受けているか
* 
* @retval TRUE 受けている
* @retval FALSE 受けていない
*/
bool ObjectManager::IsBossHandDmg() const {
	return collision_->IsBossHandDmg();
}

/**
* @brief ボスがウィーク状態か
* 
* @retval TRUE ウィーク状態
* @retval FALSE ウィークではない
*/
bool ObjectManager::IsBossWeak() const {
	return boss_->IsBossWeak();
}

/**
* @brief ボスが死んでいるか
* 
* @retval TRUE 死んでいる
* @retval FALSE 死んでいない
*/
bool ObjectManager::IsBossDeath() const {
	return boss_->IsBossDeath();
}

/**
* @brief カメラ縦揺れするか
* 
* @retval TRUE 揺らす
* @retval FALSE 揺らさない
*/
bool ObjectManager::IsCameraVerticalShake() const {
	return boss_->IsVerticalShake();
}

/**
* @brief カメラ横揺れさせるか
* 
* @retval TRUE 揺らす
* @retval FALSE 揺らさない
*/
bool ObjectManager::IsCameraSideShake() const {
	return boss_->IsSideShake();
}

/**
* @brief プレイヤーの座標取得
* 
* @return プレイヤーの座標
*/
SimpleMath::Vector3 ObjectManager::GetPlayerPos() const {
	return player_->GetPlayerPosition();
}