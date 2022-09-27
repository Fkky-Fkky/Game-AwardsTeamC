/**
* @file HandManager.h
* @brief 手を管理するクラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/LeftHand/BossHandL.h"
#include "Classes/Enemy/Boss/Parts/Hands/RightHand/BossHandR.h"
#include <random>

using namespace DirectX;

/**
* @brief HandManagerクラス定義
*/
class HandManager {
public:
	HandManager() {
		hand_state_		= ROCK;
		old_hand_state_ = PAPER;
		same_handstate_flag_   = false;
	}
	~HandManager() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render()const;

	void RandomHandState(const bool is_rush);

	/**
	* @brief 手を開いているか
	* 
	* @retval TRUE 手を開いている
	* @retval FALSE 手を握っている
	*/
	bool IsHandOpen() const { return hand_state_; }

	/**
	* @brief 左手が攻撃しているか
	* 
	* @retval TRUE 攻撃している
	* @retval FALSE 攻撃していない
	*/
	bool IsLHandAttack() const { return hand_l.IsAttack(); }

	/**
	* @brief 右手が攻撃しているか
	* 
	* @retval TRUE 攻撃している
	* @retval FALSE 攻撃していない
	*/
	bool IsRHandAttack() const { return hand_r.IsAttack(); }

	/**
	* @brief 左手取得
	* 
	* @return BossHandL
	*/
	boss::BossHandL& GetHandL() { return hand_l; }

	/**
	* @brief 右手取得
	* 
	* @return BossHandR
	*/
	boss::BossHandR& GetHandR() { return hand_r; }

	/**
	* @brief 左手のコリジョン取得
	* 
	* @return 左手のコリジョン
	*/
	BoundingOrientedBox GetLHandCollision() const { return hand_l.GetHandCollision(); }

	/**
	* @brief 右手のコリジョン取得
	* 
	* @return 右手のコリジョン
	*/
	BoundingOrientedBox GetRHandCollision() const { return hand_r.GetHandCollision(); }
private:
	boss::BossHandL hand_l; /**< ボス左手クラス */
	boss::BossHandR hand_r; /**< ボス右手クラス */

	std::mt19937 random_engine_; /**< ランダムエンジン */
	std::uniform_int_distribution<int> random_hand_dist_; /**< 手の状態同一分布 */

	bool hand_state_; /**< 手の状態を格納 */
	bool old_hand_state_; /**< ひとつ前の手の状態を格納 */
	bool same_handstate_flag_; /** 手の状態が前と同じか */

	/**< 手の状態 */
	enum HAND_STATE {
		ROCK, /** <手を握っている(グー) */
		PAPER /** <手を開いている(パー) */
	};
};