/**
* @file ActionManager.h
* @brief ボスの攻撃を管理するクラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"
#include <random>
#include "Base/DX12Effekseer.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"
#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"

using namespace DirectX;

class ObjectManager;

/**
* @brief ActionManager定義
*/
class ActionManager {
public:
	ActionManager() {
		action_		 = nullptr;
		beat_effect_ = nullptr;
		attack_state_ = WAIT;
		boss_hp_	  = 0.0f;
		action_end_flag_	   = false;
		is_vertical_shake_	   = false;
		is_side_shake_		   = false;
		is_switch_state_weak_  = false;
		is_switch_state_death_ = false;
		is_hand_death_		   = false;
	}

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;

	void RandomAttackState();
	void ActionEnd();
	void DeathActionEnd();
	void PlaySlapSE()const;
	void PlayBeatSE()const;
	void PlayBeatEffect(const SimpleMath::Vector3 effect_pos)const;

	/**
	* @brief カメラ縦揺れ設定
	* 
	* @param[in] eneable カメラを縦揺れさせるか
	*/
	void SetVerticalShake(const bool enable) { is_vertical_shake_ = enable; }

	/**
	* @brief カメラ横揺れ設定
	* 
	* @param[in] enable カメラを横揺れさせるか
	*/
	void SetSideShake(const bool enable) { is_side_shake_ = enable; }
	
	/**
	* @brief カメラを縦揺れさせるか
	* 
	* @retval TRUE 揺らす
	* @retval FALSE 揺らさない
	*/
	bool IsVerticalShake() const { return is_vertical_shake_; }

	/**
	* @brief カメラを横揺れさせるか
	* 
	* @retval TRUE 揺らす
	* @retval FALSE 揺らさない
	*/
	bool IsSideShake() const { return is_side_shake_; }

	/**
	* @brief 手が死んでいるか
	* 
	* @retval TRUE 死んでいる
	* @retval FALSE 死んでいない
	*/
	bool IsHandDeath() const { return is_hand_death_; }

	/**
	* @brief 手が開いているか
	* 
	* @retval TRUE 開いている(パー)
	* @retval FALSE 握っている(グー)
	*/
	bool IsHandOpen() const { return hand_.IsHandOpen(); }

	/**
	* @brief 左手が攻撃しているか
	* 
	* @retval TRUE 攻撃している
	* @retval FALSE 攻撃していない
	*/
	bool IsLHandAttack() const { return hand_.IsLHandAttack(); }

	/**
	* @brief 右手が攻撃しているか
	* 
	* @retval TRUE 攻撃している
	* @retval FALSE 攻撃していない
	*/
	bool IsRHandAttack() const { return hand_.IsRHandAttack(); }

	/**
	* @brief 左手のコリジョン取得
	* 
	* @return 左手のコリジョン
	*/
	BoundingOrientedBox GetLHandCollision() const { return hand_.GetLHandCollision(); }

	/**
	* @brief 右手のコリジョン取得
	* 
	* @return 右手のコリジョン
	*/
	BoundingOrientedBox GetRHandCollision() const { return hand_.GetRHandCollision(); }
private:
	void SwitchStateAttack();
	void SwitchStateWait();
	void SwitchStateWeak();
	void SwitchStateDeath();

	boss::BossAction* action_; /**< ボスアクションクラス */
	HandManager hand_; /**< ハンドマネージャークラス */

	EFFECT beat_effect_; /**< 叩きつけエフェクト格納 */
	std::mt19937 random_engine_; /**< ランダムエンジン */
	std::uniform_int_distribution<int> random_atk_dist_; /**< 攻撃の種類同一分布 */

	XAudio::SOUNDEFFECT slap_se_; /**< 薙ぎ払いSE格納 */
	XAudio::SOUNDEFFECT	beat_se_; /**< 叩きつけSE格納 */

	int attack_state_; /**< 攻撃の種類格納 */
	float boss_hp_; /**< ボスのHP格納 */
	bool action_end_flag_; /**< 行動終了フラグ */
	bool is_vertical_shake_; /**< カメラ縦揺れさせるか */
	bool is_side_shake_; /**< カメラ横揺れさせるか*/
	bool is_switch_state_weak_; /**< ウィーク状態に切り替えたか */
	bool is_switch_state_death_; /**< 死亡状態に切り替えたか */
	bool is_hand_death_; /**< 手が死亡しているか */

	const int ATTACK_STATE_MIN_ = 1; /**< 攻撃の種類最小値 */
	const int ATTACK_STATE_MAX_ = 6; /**< 攻撃の種類最大値 */
	const int NORMAL_MODE_MAX_ = 4; /**< ボスHP3/3時攻撃の種類最大値 */
	const int HARD_MODE_MAX_ = 5; /**< ボスのHP2/3時攻撃の種類最大値 */
	const float HP_NORMAL_MAX_ = 30.0f; /**< ボスのHP3/3最大値 */
	const float HP_NORMAL_MIN_ = 20.0f; /**< ボスのHP3/3最小値 */
	const float HP_HARD_MIN_ = 10.0f; /**< ボスのHP2/3最小値 */

	/**
	* @brief ボスの行動種類
	*/
	enum BOSS_STATE {
		WAIT, /**< 待機状態 */
		LEFT_BEAT, /**< 左叩きつけ攻撃 */
		LEFT_SLAP, /**< 左薙ぎ払い攻撃 */
		RIGHT_BEAT, /**< 右叩きつけ攻撃 */
		RIGHT_SLAP, /**< 右薙ぎ払い攻撃 */
		DOUBLE_SLAP, /**< 両手薙ぎ払い攻撃 */
		BEAT_RUSH_R /**< 連続叩きつけ攻撃 */
	};
};