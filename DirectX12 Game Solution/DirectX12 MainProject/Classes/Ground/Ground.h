/**
* @file Ground.h
* @brief ステージ、BGMの処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

class ObjectManager;

using namespace DirectX;

/**
* @brief Groundクラス定義
*/
class Ground {
public:
	Ground() { 
		mist_pos_ = SimpleMath::Vector3(MIST_INIT_POS_X_, 0.0f, MIST_INIT_POS_Z_);
		is_frist_battle_ = false;
		first_bg_alpha_ = COLOR_MAX_;
		miset_speed_ = MIST_MOVE_SPEED_SLOW_;
		first_bgm_volume_ = 0.0f;
	}
	~Ground() {};

	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;
	void Render2D()const;

private:
	void BGMChange(const float deltaTime);

	DX9::MODEL stage_; /**< ステージモデル格納 */
	DX9::SPRITE first_bg_; /**< 前半戦背景格納 */
	DX9::SPRITE second_bg_; /**< 後半戦背景格納 */
	DX9::SPRITE mist_; /**< 霧背景格納 */
	DX9::MEDIARENDERER first_battle_bgm_; /**< 前半戦BGM格納 */
	DX9::MEDIARENDERER second_battle_bgm_; /**< 後半戦BGM格納 */

	float first_bg_alpha_; /**< 前半戦背景のアルファ値格納 */
	float miset_speed_; /**< 霧の動く速度格納 */
	float first_bgm_volume_; /**< 前半戦BGMの音量格納 */
	bool is_frist_battle_; /**< 前半戦か */
	SimpleMath::Vector3 mist_pos_; /**< 霧の座標格納 */

	const float STAGE_POS_X_ = 35.0f; /**< ステージのX座標 */
	const float STAGE_POS_Z_ = -40.0f; /**< ステージのZ座標 */
	const float STAGE_SCALE_ = 7.0f; /**< ステージモデルの大きさ */
	const float FIRST_BG_POS_Z_ = 10000.0f; /**< 前半戦背景のZ座標 */
	const float SECOND_BG_POS_Z_ = 9999.0f; /**< 後半戦背景のZ座標 */
	const float MIST_INIT_POS_Z_ = 9998.0f; /**< 霧のZ座標 */
	const float MIST_INIT_POS_X_ = -1280.0f; /**< 霧の初期X座標 */
	const float MIST_MOVE_SPEED_SLOW_ = 100.0f; /**< 霧の移動速度(遅い) */
	const float MIST_MOVE_SPEED_QUICK_ = 200.0f; /**< 霧の移動速度(速い) */
	const float ADD_MIST_SPEED_  = 80.0f; /**< 霧の加速度 */
	const float ADD_ALPHA_SPEED_ = 300.0f; /**< アルファ値の増減速度 */
	const float COLOR_MAX_ = 255.0f; /**< 色の最大値 */
	const float SPRITE_WIDTH_ = 1280.0f; /**< 画像の最大横幅 */
	const float SPRITE_HIGHT_ = 720.0f; /**< 画像の最大縦幅 */
	const float BOSS_HP_HALF_ = 15.0f; /**< ボスのHPの半分 */
	const float VOLUME_SPEED_ = 900.0f; /**< 音量減少速度 */
	const float VOLUME_MIN_ = -2000.0f; /**< 音量の最小値 */
};