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
		player_side_shake_	   = 0;
		player_vertical_shake_ = 0;
		boss_side_shake_	 = 0;
		boss_vertical_shake_ = 0;
		player_hp_width_ = 0.0f;
		boss_hp_width_	 = 0.0f;
		time_delta_		 = 0.0f;
		old_player_hp_	 = 0.0f;
		old_boss_hp_	 = 0.0f;
		player_shake_time_ = 0.0f;
		boss_shake_time_   = 0.0f;
		is_player_damage_ = false;
		is_boss_damage_	  = false;
		player_hp_pos_ = SimpleMath::Vector3::Zero;
		boss_hp_pos_   = SimpleMath::Vector3::Zero;
	}
	~UI() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render() const;

private:
	void PlayerUIShake();
	void BossUIShake();

	DX9::SPRITE player_hp_top_; /**< プレイヤーHP満タン画像格納 */
	DX9::SPRITE player_hp_bottom_; /**< プレイヤーHP空画像格納 */
	DX9::SPRITE boss_hp_top_; /**< ボスHP満タン画像格納 */
	DX9::SPRITE boss_hp_bottom_; /**< ボスHP空画像格納 */
	
	int player_side_shake_; /**< プレイヤーHP横揺れ状態 */
	int player_vertical_shake_; /**< プレイヤーHP縦揺れ状態 */
	int boss_side_shake_; /**< ボスHP横揺れ状態 */
	int boss_vertical_shake_; /**< ボスHP縦揺れ状態 */
	float player_hp_width_; /**< プレイヤーHPの横幅 */
	float boss_hp_width_; /**< ボスHPの横幅 */
	float time_delta_; /**< 時間 */
	float old_player_hp_; /**< 過去のプレイヤーHP格納 */
	float old_boss_hp_; /**< 過去のボスHP格納 */
	float player_shake_time_; /**< プレイヤーHP揺らす時間 */
	float boss_shake_time_; /**< ボスHP揺らす時間 */
	bool is_player_damage_; /**< プレイヤーがダメージを受けたか */
	bool is_boss_damage_; /**< ボスがダメージを受けたか */
	SimpleMath::Vector3 player_hp_pos_; /**< プレイヤーHP座標格納 */
	SimpleMath::Vector3 boss_hp_pos_; /**< ボスHP座標格納 */

	/**< UI揺れる種類 */
	enum SHAKE_STATE_ {
		UP, /**< 上 */
		DOWN, /**< 下 */
		RIGHT, /**< 右 */
		LEFT /**< 左 */
	};

	const int PLAYER_HP_HIGHT_ = 30; /**< プレイヤーHP高さ */
	const int BOSS_HP_HIGHT_   = 30; /**< ボスHP高さ */
	const float PLAYER_HP_POS_X_ = 50.0f; /**< プレイヤーHPのX座標 */
	const float PLAYER_HP_POS_Y_ = 680.0f; /**< プレイヤーHPのY座標 */
	const float BOSS_HP_POS_X_ = 190.0f; /**< ボスHPのX座標 */
	const float BOSS_HP_POS_Y_ = 30.0f; /**< ボスHPのY座標 */
	const float PLAYER_HP_WIDTH_DIVIDE_ = 11.3f; /**< プレイヤーHP1/30の横幅 */
	const float BOSS_HP_WIDTH_DIVIDE_ = 30.0f; /**< ボスHP1/30の横幅 */
	const float HP_SPEED_ = 300.0f; /**< HPの増減速度 */
};