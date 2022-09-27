/**
* @file Collision.h
* @brief プレイヤーとボスのコリジョン処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

/**
* @brief Collisionクラス定義
*/
class Collision {
public:
	Collision() {
		hand_dmg_flag_reset_time_ = 0.0f;
		player_dmg_flag_r_ = false;
		player_dmg_flag_l_ = false;
		boss_body_dmg_flg_	  = false;
		boss_hand_r_dmg_flag_ = false;
		boss_hand_l_dmg_flag_ = false;
	}
	~Collision() {};

	void Initialize();
	void Update(const float deltaTime, const ObjectManager* const obj_m_);

	/**
	* @brief プレイヤーが右手から攻撃を受けたか
	* 
	* @retval TRUE 受けた
	* @retval FALSE 受けていない
	*/
	bool GetPlayerDmgFlagR() const { return player_dmg_flag_r_; }

	/**
	* @brief プレイヤーが左手から攻撃を受けたか
	* 
	* @retval TRUE 受けた
	* @retval FALSE 受けていない
	*/
	bool GetPlayerDmgFlagL() const { return player_dmg_flag_l_; }

	/**
	* @brief ボスの本体がダメージを受けたか
	* 
	* @retval TRUE 受けた
	* @retval FALSE 受けていない
	*/
	bool IsBossBodyDmg() const { return boss_body_dmg_flg_; }

	/**
	* @brief ボスの手がダメージを受けたか
	* 
	* @retval TRUE 受けた
	* @retval FALSE 受けていない
	*/
	bool IsBossHandDmg() const { return boss_hand_r_dmg_flag_ || boss_hand_l_dmg_flag_; }

private:
	float hand_dmg_flag_reset_time_; /**< 手のダメージフラグを降ろす時間 */
	bool player_dmg_flag_r_; /**< プレイヤーが右手から攻撃を受けたか */
	bool player_dmg_flag_l_; /**< プレイヤーが左手から攻撃を受けたか */
	bool boss_body_dmg_flg_; /**< ボス本体がダメージを受けたか */
	bool boss_hand_r_dmg_flag_; /**< ボス右手がダメージを受けたか*/
	bool boss_hand_l_dmg_flag_; /**< ボス左手がダメージを受けたか*/
};