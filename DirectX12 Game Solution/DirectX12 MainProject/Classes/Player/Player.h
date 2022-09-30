/**
* @file Player.h
* @brief プレイヤーの処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

#include "Classes/Player/PlayerCollision.h"
#include "Classes/Player/PlayerAttackCollision.h"
#include "Classes/Player/PlayerStatus.h"
#include "Classes/Player/Action/PlayerActionManager.h"

using namespace DirectX;

class ObjectManager;

/**
* @brief プレイヤーモーション種類
*/
enum class PLAYER_MOTION {
	WAIT, /**< 待機 */
	ATTACK, /**< 攻撃 */
	MOVE, /**< 移動 */
	JUMP, /**< ジャンプ */
	DAMAGE, /**< ダメージ */
	DEATH /**< 死亡 */
};

/**
* @brief Playerクラス定義
*/
class Player {
public:
	Player() {
		player_motion_track_ = 0;
		jump_motion_time_ = 0.0f;
		death_motion_time_ = 0.0f;
		is_jump_motion_play_ = false;
		is_death_motion_play_ = false;
		pos_ = SimpleMath::Vector3::Zero;
		rot_ = SimpleMath::Vector3::Zero;
	}
	~Player() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;

	/**
	* @brief 座標設定
	* 
	* @param[in] position 座標
	*/
	void SetPlayerPosition(const SimpleMath::Vector3 position) { pos_ = position; }

	/**
	* @brief 回転設定
	* 
	* @param[in] rotation 回転
	*/
	void SetPlayerRotation(const SimpleMath::Vector3 rotation) { rot_ = rotation; }
	void SetMotion(const int player_motion);
	void PlayAtkSE()const;

	/**
	* @biref プレイヤーのHP取得
	* 
	* @return プレイヤーのHP
	*/
	float GetPlayerHP() const { return player_status_.GetPlayerHP(); }

	/**
	* @brief プレイヤーの攻撃が始まったか
	* 
	* @retval TRUE 始まっている
	* @retval FALSE 始まっていない
	*/
	bool IsPlayerAttackStart() const { return action_.IsPlayerAttackStart(); }

	/**
	* @brief プレイヤーが攻撃しているか
	* 
	* @retval TRUE 攻撃している
	* @retval FALSE 攻撃していない
	*/
	bool IsPlayerAttack() const { return player_attack_colision_.IsPlayerAttack(); }

	/**
	* @brief プレイヤーが無敵か
	* 
	* @retval TRUE 無敵
	* @retval FALSE 無敵ではない
	*/
	bool IsPlayerInvincible()  const { return action_.IsPlayerInvincible(); }

	/**
	* @brief プレイヤーが死亡しているか
	* 
	* @retval TRUE 死亡している
	* @retval FALSE 死亡していない
	*/
	bool IsPlayerDeath() const { return action_.IsPlayerDeath(); }

	/**
	* @brief プレイヤーの座標取得
	* 
	* @return プレイヤーの座標
	*/
	SimpleMath::Vector3 GetPlayerPosition() const { return pos_; }

	/**
	* @brief プレイヤーの回転取得
	* 
	* @return プレイヤーの回転
	*/
	SimpleMath::Vector3 GetPlayerRotation() const { return rot_; }

	/**
	* @brief プレイヤーのコリジョン取得 
	* 
	* @return プレイヤーのコリジョン
	*/
	BoundingOrientedBox GetPlayerCollision() const { return player_colision_.GetColision(); }

	/**
	* @brief プレイヤーの攻撃コリジョン取得
	* 
	* @return プレイヤーの攻撃コリジョン
	*/
	BoundingOrientedBox GetPlayerAttackCollision() const { return player_attack_colision_.GetAttackCollision(); }

private:
	void ResetPlayerMotion()const;
	void JumpMotion(const float deltaTime);
	void DeathMotion(const float delaTime);

	DX9::SKINNEDMODEL model_; /**< プレイヤーモデル格納 */

	XAudio::SOUNDEFFECT atk_se_; /**< 攻撃SE格納 */

	int player_motion_track_; /**< モーショントラック格納 */
	float jump_motion_time_; /**< ジャンプモーションの再生時間 */
	float death_motion_time_; /**< 死亡モーションの再生時間 */

	bool is_jump_motion_play_; /**< ジャンプモーション再生するか */
	bool is_death_motion_play_; /**< 死亡モーション再生するか */

	SimpleMath::Vector3 pos_; /**< プレイヤーの座標格納 */
	SimpleMath::Vector3 rot_; /**< プレイヤーの回転格納 */

	const int MOTION_MAX_ = 6; /**< モーションの最大数 */
	const float PLAYER_SCALE_ = 0.02f; /**< プレイヤーモデルの大きさ */
	const float RIGHT_WARD_ = -90.0f; /**< 右向き */

	player::PlayerCollision       player_colision_; /**< プレイヤーコリジョンクラス */
	player::PlayerAttackCollision player_attack_colision_; /**< プレイヤー攻撃コリジョンクラス */
	player::PlayerStatus		 player_status_; /**< プレイヤーステータスクラス */
	PlayerActionManager action_; /**< プレイヤーアクションマネージャークラス */
};