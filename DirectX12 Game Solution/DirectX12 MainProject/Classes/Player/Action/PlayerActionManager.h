/**
* @file PlayerActionManager.h
* @brief プレイヤー行動処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

#include "Classes/Player/Action/PlayerRightMove.h"
#include "Classes/Player/Action/PlayerLeftMove.h"
#include "Classes/Player/Action/PlayerJump.h"
#include "Classes/Player/Action/PlayerAttack.h"
#include "Classes/Player/Action/PlayerWait.h"
#include "Classes/Player/Action/PlayerActionState.h"
#include "Classes/Player/Action/PlayerDamage.h"
#include "Classes/Player/Action/PlayerDeath.h"

using namespace DirectX;

class ObjectManager;
class Player;

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
* @brief PlayerActionManagerクラス定義
*/
class PlayerActionManager {
public:
	PlayerActionManager() {
		player_action_state_ = PLAYER_STATE::WAIT;
		action_ = nullptr;
		is_switch_state_death_ = false;
	}
	~PlayerActionManager() {};

	void Initialize();
	void Update(const float deltaTime, Player* const player, const ObjectManager* const obj_m);

	void SwitchState(const PLAYER_STATE state, Player* const player);

	/**
	* @brief プレイヤーの攻撃が始まったか
	*
	* @retval TRUE 始まっている
	* @retval FALSE 始まっていない
	*/
	bool IsPlayerAttackStart() const { return attack_.IsPlayerAttackStart(); }

	/**
	* @brief プレイヤーが無敵か
	*
	* @retval TRUE 無敵
	* @retval FALSE 無敵ではない
	*/
	bool IsPlayerInvincible()  const { return dmg_.IsInvincible(); }

	/**
	* @brief プレイヤーが死亡しているか
	*
	* @retval TRUE 死亡している
	* @retval FALSE 死亡していない
	*/
	bool IsPlayerDeath() const { return death_.IsPlayerDeath(); }

private:
	int ConvertToMotion(const PLAYER_STATE player_state)const;

	bool is_switch_state_death_; /**< 死亡状態に切り替えたか */
	PLAYER_STATE player_action_state_; /**< 現在のプレイヤー行動 */

	/**
	* @brief プレイヤーモーション種類
	*/
	enum PLAYER_MOTION {
		WAIT, /**< 待機 */
		ATTACK, /**< 攻撃 */
		MOVE, /**< 移動 */
		JUMP, /**< ジャンプ */
		DAMAGE, /**< ダメージ */
		DEATH /**< 死亡 */
	};

	player::PlayerRightMove      right_move_; /**< プレイヤー右移動クラス */
	player::PlayerLeftMove		 left_move_; /**< プレイヤー左移動クラス */
	player::PlayerJump           jump_; /**< プレイヤージャンプクラス */
	player::PlayerAttack		 attack_; /**< プレイヤー攻撃クラス */
	player::PlayerWait			 wait_; /**< プレイヤー待機クラス */
	player::PlayerDamage		 dmg_; /**< プレイヤーダメージクラス */
	player::PlayerDeath			 death_; /**< プレイヤー死亡クラス */
	player::PlayerActionState*   action_; /**< プレイヤー状態クラス */
};