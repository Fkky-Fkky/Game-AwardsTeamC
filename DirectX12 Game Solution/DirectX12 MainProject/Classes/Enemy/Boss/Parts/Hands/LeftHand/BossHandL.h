/**
* @file BossHandL.h
* @brief ボスの左手処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"

namespace boss {
	/**
	* @brief BossHandLクラス定義
	*/
	class BossHandL : public BossHand {
	public:
		void Initialize();
		void LoadAssets();
		virtual void Update(const float deltaTime);
	private:
		const float INITIAL_POS_X_ = 13.0f; /**< 初期X座標 */
		const float ADD_COLLISION_POS_X_ = 1.0f; /**< コリジョンのX座標 */
	};
}