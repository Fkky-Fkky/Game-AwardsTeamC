/**
* @file Player.h
* @brief プレイヤーの処理クラス
* @author 吹上純平
*/

#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#include "Classes/Player/PlayerRightMove.h"
#include "Classes/Player/PlayerLeftMove.h"
#include "Classes/Player/PlayerJump.h"
#include "Classes/Player/PlayerAttack.h"
#include "Classes/Player/PlayerColision.h"
#include "Classes/Player/PlayerAttackColision.h"
#include "Classes/Player/PlayerWait.h"
#include "Classes/Player/PlayerActionState.h"
#include "Classes/Player/PlayerDamage.h"
#include "Classes/Player/PlayerDeath.h"
#include "Classes/Player/PlayerStatus.h"

using namespace DirectX;

class ObjectManager;

/**
* @brief プレイヤーの状態種類
*/
enum class PLAYER_STATE {
	WAIT, /**< 待機 */
	RIGHT_MOVE, /**< 右移動 */
	LEFT_MOVE, /**< 左移動 */
	JUMP, /**< ジャンプ */
	ATTACK, /**< 攻撃 */
	DAMAGE, /**< ダメージ */
	DEATH /**< 死亡 */
};

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
		player_action_state_ = PLAYER_STATE::WAIT;
		player_motion_track_ = 0;
		player_action_ = nullptr;
		jump_motion_time_ = 0.0f;
		death_motion_time_ = 0.0f;
		is_jump_motion_play_ = false;
		is_death_motion_play_ = false;
		is_switch_state_death_ = false;
		pos_ = SimpleMath::Vector3::Zero;
		rot_ = SimpleMath::Vector3::Zero;
	}
	~Player() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;

	void SwitchState(const PLAYER_STATE state);
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
	void SetMotion(const PLAYER_MOTION player_motion);
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
	bool IsPlayerAttackStart() const { return player_attack_.IsPlayerAttackStart(); }

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
	bool IsPlayerInvincible()  const { return player_dmg_.IsInvincible(); }

	/**
	* @brief プレイヤーが死亡しているか
	* 
	* @retval TRUE 死亡している
	* @retval FALSE 死亡していない
	*/
	bool IsPlayerDeath() const { return player_death_.IsPlayerDeath(); }

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
	PLAYER_MOTION ConvertToMotion(const PLAYER_STATE player_state)const;

	DX9::SKINNEDMODEL model_; /**< プレイヤーモデル格納 */

	XAudio::SOUNDEFFECT atk_se_; /**< 攻撃SE格納 */

	PLAYER_STATE player_action_state_; /**< 現在のプレイヤー行動 */
	int player_motion_track_; /**< モーショントラック格納 */
	float jump_motion_time_; /**< ジャンプモーションの再生時間 */
	float death_motion_time_; /**< 死亡モーションの再生時間 */

	bool is_jump_motion_play_; /**< ジャンプモーション再生するか */
	bool is_death_motion_play_; /**< 死亡モーション再生するか */
	bool is_switch_state_death_; /**< 死亡状態に切り替えたか */

	SimpleMath::Vector3 pos_; /**< プレイヤーの座標格納 */
	SimpleMath::Vector3 rot_; /**< プレイヤーの回転格納 */

	const int MOTION_MAX_ = 6; /**< モーションの最大数 */
	const float PLAYER_SCALE_ = 0.02f; /**< プレイヤーモデルの大きさ */
	const float RIGHT_WARD_ = -90.0f; /**< 右向き */

	player::PlayerRightMove      player_right_move_; /**< プレイヤー右移動クラス */
	player::PlayerLeftMove		 player_left_move_; /**< プレイヤー左移動クラス */
	player::PlayerJump           player_jump_; /**< プレイヤージャンプクラス */
	player::PlayerAttack		 player_attack_; /**< プレイヤー攻撃クラス */
	player::PlayerColision       player_colision_; /**< プレイヤーコリジョンクラス */
	player::PlayerAttackColision player_attack_colision_; /**< プレイヤー攻撃コリジョンクラス */
	player::PlayerWait			 player_wait_; /**< プレイヤー待機クラス */
	player::PlayerDamage		 player_dmg_; /**< プレイヤーダメージクラス */
	player::PlayerDeath			 player_death_; /**< プレイヤー死亡クラス */
	player::PlayerActionState*	 player_action_; /**< プレイヤー状態クラス */
	player::PlayerStatus		 player_status_; /**< プレイヤーステータスクラス */
};