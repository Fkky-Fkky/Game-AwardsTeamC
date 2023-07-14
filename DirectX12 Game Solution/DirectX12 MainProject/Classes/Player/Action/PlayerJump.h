/**
* @file PlayerJump.h
* @brief プレイヤージャンプ処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Player/Action/PlayerActionState.h"

namespace player {
	/**
	* @brief PlayerJumpクラス定義
	*/
	class PlayerJump : public PlayerActionState {
	public:
		PlayerJump() {
			action_state_ = READY;
			time_delta_ = 0.0f;
			jump_time_ = 0.0f;
			cool_time_ = 0.0f;
			player_up_flag_ = false;
			pos_ = SimpleMath::Vector3::Zero;
			rot_ = SimpleMath::Vector3::Zero;
			old_player_pos_ = SimpleMath::Vector3::Zero;
		}
		~PlayerJump() {};

		virtual void Initialize();
		virtual void Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m);

	private:
		void Ready();
		void Jump(Player* const player);
		void CoolTime();
		void JumpingMove();

		int action_state_; /**< 現在行動格納 */

		float time_delta_; /**< 時間 */
		float jump_time_; /**< ジャンプ時間格納 */
		float cool_time_; /**< クールタイム格納 */

		bool  player_up_flag_; /**< プレイヤーが上昇しているか */

		SimpleMath::Vector3 pos_; /**< プレイヤーの座標格納 */
		SimpleMath::Vector3 rot_; /**< プレイヤーの回転格納 */
		SimpleMath::Vector3 old_player_pos_; /**< 過去のプレイヤーの座標 */

		/**< ジャンプ行動の種類 */
		enum ACTION_STATE_ {
			READY, /**< 構え */
			JUMP, /**< ジャンプ */
			COOL_TIME, /**< クールタイム */
			ACTION_END /**< 行動の種類 */
		};

		const float GRAVITY_ = 20.0f; /**< 重力 */
		const float V0_ = 16.0f; /**< ジャンプの初速 */
		const float HALF_ = 0.5f; /** 1/2 */
		const float DOWN_SPEED_ = 2.0f; /**< 落下速度 */
		const float GROUND_Y_ = 0.0f; /**< 着地地点 */
		const float COOL_TIME_MAX_ = 0.6f; /**< クールタイム */
		const float JUMPING_MOVE_SPEED_ = 5.0f; /**< ジャンプ中の移動速度 */
		const float JUMPING_MOVE_SPEED_REVERSE = 2.5f; /**< ジャンプ中の反転移動速度*/
	};
}