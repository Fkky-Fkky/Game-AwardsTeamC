/**
* @file Boss.h
* @brief ボス関連クラスをまとめて処理するクラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"
#include "Classes/Enemy/Boss/Parts/Hands/ActionManager.h"
#include "Classes/Enemy/Boss/Status.h"

using namespace DirectX;

class ObjectManager;

/**
* @brief Bossクラス定義
*/
class Boss {
public:
	Boss() {
		is_vertical_shake_ = false;
	}

	~Boss() {};

	void Initialize();
	void LoadAseets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;

	/*
	* @brief カメラ縦揺れフラグ設定
	* 
	* @param[in] enable カメラを揺らすか
	*/
	void SetVerticalShake(const bool enable) { is_vertical_shake_ = enable; }

	/**
	* @brief ボスのHP取得
	* 
	* @return ボスのHP
	*/
	float GetBossHP() const { return status_.GetBossHP(); }

	/**
	* @brief ボスのウィーク状態取得
	* 
	* @retval TRUE ウィーク状態
	* @retval FALSE ウィーク状態ではない
	*/	
	bool IsBossWeak() const { return status_.IsWeak(); }

	/**
	* @brief ボスが死んでいるか
	* 
	* @retval TRUE 死んでいる
	* @retval FALSE 死んでいない
	*/
	bool IsBossDeath() const { return body_.IsBodyDeath() && action_.IsHandDeath(); }

	/**
	* @brief カメラを縦揺れさせるか
	* 
	* @retval TRUE 揺らす
	* @retval FALSE 揺らさない
	*/
	bool IsVerticalShake() const { return action_.IsVerticalShake() || is_vertical_shake_; }

	/**
	* @brief カメラを横揺れさせるか
	*
	* @retval TRUE 揺らす
	* @retval FALSE 揺らさない
	*/
	bool IsSideShake() const { return action_.IsSideShake(); }

	/**
	* @brief ボスの手が開いているか
	*
	* @retval TRUE 開いている
	* @retval FALSE 開いていない
	*/
	bool IsHandOpen() const { return action_.IsHandOpen(); }

	/**
	* @brief 左手が攻撃しているか
	*
	* @retval TRUE 攻撃している
	* @retval FALSE 攻撃していない
	*/
	bool IsLHandAttack() const { return action_.IsLHandAttack(); }

	/**
	* @brief 右手が攻撃しているか
	*
	* @retval TRUE 攻撃している
	* @retval FALSE 攻撃していない
	*/
	bool IsRHandAttack() const { return action_.IsRHandAttack(); }

	/**
	* @brief 左手のコリジョン取得
	*
	* @return 左手のコリジョン
	*/
	BoundingOrientedBox GetLHandCollision() const { return action_.GetLHandCollision(); }

	/**
	* @brief 右手のコリジョン取得
	*
	* @return 右手のコリジョン
	*/
	BoundingOrientedBox GetRHandCollision() const { return action_.GetRHandCollision(); }

	/**
	* @brief 本体のコリジョン取得
	*
	* @return 本体のコリジョン
	*/
	BoundingOrientedBox GetBodyCollision() const { return body_.GetBodyCollision(); }

private:
	boss::Status status_; /**< ステータスクラス */
	boss::BossBody body_; /**< ボディークラス */
	ActionManager action_; /**< アクションマネージャークラス */
	
	bool is_vertical_shake_; /**< カメラを縦揺れさせるか */
};