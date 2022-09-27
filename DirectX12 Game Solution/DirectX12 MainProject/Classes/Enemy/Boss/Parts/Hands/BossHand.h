/**
* @file BossHand.h
* @brief ボスの手基底クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/BossParts.h"

/**
* @brief BossHandクラス定義
*/
class BossHand : public BossParts{
public:
	BossHand() {
		motion_track_ = 0;
		timde_delta_  = 0.0f;
		motion_time_  = 0.0f;
		motion_time_max_  = 0.0f;
		motion_stop_time_ = 0.0f;
		motion_flag_	 = false;
		attack_flag_	 = false;
		is_death_motion_ = false;
	}

	~BossHand() {};
	virtual void LoadAssets(const LPCWSTR file_name);
	virtual void Update(const float deltaTime);

	void PlayDeathMotion();
	/**
	* @brief 座標の設定
	* 
	* @param[in] position 座標
	*/
	void SetHandPos(const SimpleMath::Vector3 position) { position_ = position; }

	/**
	* @brief 回転の設定
	* 
	* @param[in] rotation 回転
	*/
	void SetHandRote(const SimpleMath::Vector3 rotation) { rotation_ = rotation; }

	/**
	* @brief 攻撃フラグの設定
	* 
	* @param[in] attack_flag 攻撃するか
	*/
	void SetAttackFlag(const bool attack_flag) { attack_flag_ = attack_flag; }

	void SetHandMotion(const int hand_motion);

	/**
	* @brief 攻撃しているか
	* 
	* @retval TRUE 攻撃している
	* @retval FALSE 攻撃していない
	*/
	bool IsAttack() const { return attack_flag_; }

	/**
	* @brief 手のコリジョン取得
	* 
	* @return 手のコリジョン
	*/
	BoundingOrientedBox GetHandCollision() const { return collision_; }

	/**
	* @brief 手の座標取得
	* 
	* @return 手の座標
	*/
	SimpleMath::Vector3 GetHandPos() const { return position_; }

	/**
	* @brief 手の回転取得
	* 
	* @return 手の回転
	*/
	SimpleMath::Vector3 GetRotation() const { return rotation_; }

private:
	void MotionStart();
	void MotionReset();
	void PlayMotion();
	void HandMotionAttack();
	void HandMotionWait()const;

	/**
	* @brief 手のモーション
	*/
	enum HAND_MOTION {
		WAIT, /**< 待機 */
		PAPER, /**< 手を開く */
		PAPER_BACK, /**< 開いた状態から待機に戻る */
		ROCK, /**< 手を握る */
		ROCK_BACK /**< 握る状態から待機に戻る */
	};

	int motion_track_; /**< モーションのトラックを格納 */
	float motion_time_; /**< モーションの再生時間 */
	float motion_time_max_; /**< モーションの最大再生時間 */
	float timde_delta_; /**< 時間 */
	float motion_stop_time_; /**< モーションを止める時間 */
	bool motion_flag_; /**< モーションを再生させるフラグ */
	bool attack_flag_; /**< 攻撃をしているか */
	bool is_death_motion_; /**< 死亡時のモーションを再生しているか */

	const int MOTION_MAX_  = 5; /**< モーションの種類最大値 */
	const float BACK_MOTION_TIME_ = 0.96f; /**< 待機状態に戻るモーションの時間 */
	const float ATK_MOTION_TIME_  = 0.96f; /**< 開くか握る時のモーションの時間 */
	const float COLLSION_SIZE_X_ = 1.7f; /**< コリジョンのXサイズ */
	const float COLLSION_SIZE_Y_ = 0.6f; /**< コリジョンのYサイズ */
	const float COLLSION_SIZE_Z_ = 2.0f; /**< コリジョンのZサイズ */
	const float HAND_SCALE = 0.8f; /**< 手のモデルの大きさ */
	const float STOP_TIME_ = 0.5f; /**< モーションを止める時間 */
protected:

	BoundingOrientedBox collision_; /**< コリジョンを格納 */

	const float INITIAL_POS_Y_ = 50.0f; /**< 手の初期X座標 */
	const float INITIAL_POS_Z_ = 10.0f; /**< 手の初期Z座標 */
	const float INITIAL_ROT_X_ = 30.0f; /**< 手の初期回転X軸 */
	const float INITIAL_ROT_Y_ = 90.0f; /**< 手の初期回転Y軸 */
};