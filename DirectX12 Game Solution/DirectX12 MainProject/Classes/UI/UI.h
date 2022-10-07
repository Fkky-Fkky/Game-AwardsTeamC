/**
* @file UI.h
* @brief UI処理クラス
* @outhor 吹上純平
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
* @UIクラス定義
*/
class UI {
public:
	UI() {
		time_delta_ = 0.0f;
		for (int i = 0; i < CHARACTER_MAX_; i++) {
			side_shake_state_[i]	 = 0;
			vertical_shake_state_[i] = 0;
			hp_init_pos_x_[i] = 0.0f;
			hp_init_pos_y_[i] = 0.0f;
			hp_width_[i] = 0.0f;
			old_hp_[i]	 = 0.0f;
			ui_shake_time_[i]	  = 0.0f;
			ui_shake_time_max_[i] = 0.0f;
			ui_side_shake_pos_min_[i] = 0.0f;
			ui_side_shake_pos_max_[i] = 0.0f;
			ui_vertical_shake_pos_min_[i] = 0.0f;
			ui_vertical_shake_pos_max_[i] = 0.0f;
			ui_side_shake_power_[i]		= 0.0f;
			ui_vertical_shake_power_[i] = 0.0f;
			is_damage_[i] = false;
			hp_pos_[i] = SimpleMath::Vector3::Zero;
		}
	}
	~UI() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render() const;

private:
	void ReadFile();
	void UIShake();

	enum { CHARACTER_MAX_ = 2 }; /**< キャラクターの最大数 */
	DX9::SPRITE hp_top_[CHARACTER_MAX_]; /**< HP満タン画像格納 */
	DX9::SPRITE hp_bottom_[CHARACTER_MAX_]; /**< HP空画像格納 */
	
	int side_shake_state_[CHARACTER_MAX_]; /**< HP横揺れ状態 */
	int vertical_shake_state_[CHARACTER_MAX_]; /**< HP縦揺れ状態 */
	float time_delta_; /**< 時間 */
	float hp_init_pos_x_[CHARACTER_MAX_]; /**< HPの初期X座標 */
	float hp_init_pos_y_[CHARACTER_MAX_]; /**< HPの初期Y座標 */
	float hp_width_[CHARACTER_MAX_]; /**< HPの横幅 */
	float old_hp_[CHARACTER_MAX_]; /**< 過去のHP格納 */
	float ui_shake_time_[CHARACTER_MAX_]; /**< HP揺らす時間 */
	float ui_shake_time_max_[CHARACTER_MAX_]; /**< UI揺らす最大時間 */
	float ui_side_shake_pos_min_[CHARACTER_MAX_]; /**< UI揺らす最小X座標 */
	float ui_side_shake_pos_max_[CHARACTER_MAX_]; /**<UI揺らす最大X座標 */
	float ui_vertical_shake_pos_min_[CHARACTER_MAX_]; /**< UI揺らす最小Y座標 */
	float ui_vertical_shake_pos_max_[CHARACTER_MAX_]; /**< UI揺らす最大Y座標 */
	float ui_side_shake_power_[CHARACTER_MAX_]; /**< UI横方向に揺らす強さ */
	float ui_vertical_shake_power_[CHARACTER_MAX_]; /**< UI縦方向に揺らす強さ */	
	bool is_damage_[CHARACTER_MAX_]; /**< ダメージを受けたか */
	SimpleMath::Vector3 hp_pos_[CHARACTER_MAX_]; /**< HP座標格納 */

	/**< キャラクターの種類 */
	enum  CHARACTER {
		PLAYER, /**< プレイヤー */
		BOSS /**< ボス */
	};

	/**< UI揺れる種類 */
	enum SHAKE_STATE_ {
		UP, /**< 上 */
		DOWN, /**< 下 */
		RIGHT, /**< 右 */
		LEFT /**< 左 */
	};

	const int HP_HIGHT_ = 30; /**< HP画像の高さ */
	const float PLAYER_HP_WIDTH_DIVIDE_ = 11.3f; /**< プレイヤーHP1/30の横幅 */
	const float BOSS_HP_WIDTH_DIVIDE_ = 30.0f; /**< ボスHP1/30の横幅 */
	const float HP_SPEED_ = 300.0f; /**< HPの増減速度 */
};