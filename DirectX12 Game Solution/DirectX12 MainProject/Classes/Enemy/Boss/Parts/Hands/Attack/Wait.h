/**
* @file Wait.h
* @brief 待機処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief Waitクラス定義
	*/
	class Wait : public BossAction {
	public:
		Wait() {
			wait_time_ = 0.0f;
			max_wait_time_ = 0.0f;
			first_processed_flag_ = false;
		}
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		float wait_time_; /**< 待機時間格納 */
		float max_wait_time_; /**< 最大待機時間格納 */
		bool first_processed_flag_; /**< 一度だけ処理するフラグ */
		const float HP_NORMAL_MAX_ = 30.0f; /**< HP3/3最大値 */
		const float HP_NORMAL_MIN_ = 20.0f; /**< HP3/3最小値 */
		const float HP_HARD_MIN_ = 10.0f; /**< HP2/3最小値 */
		const float MAX_WAIT_TIME_NORMAL_ = 1.0f; /**< HP3/3時の待機時間 */
		const float MAX_WAIT_TIME_HARD_ = 0.7f; /**< HP2/3時の待機時間 */
		const float MAX_WAIT_TIME_VERY_HARD_ = 0.5f; /**< HP1/3時の待機時間 */
	};
}