/**
* @file My_Camera.h
* @brief カメラの処理クラス
* @author 吹上純平
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
* @brief My_Cameraクラス定義
*/
class My_Camera {
public:
	My_Camera() {
		vertical_shake_state_ = Down;
		side_shake_state_	  = Right;
		time_delta_			 = 0.0f;
		vertical_shake_time_ = 0.0f;
		camera_init_pos_x_ = 0.0f;
		camera_init_pos_y_ = 0.0f;
		vertical_shake_pos_max_ = 0.0f;
		vertical_shake_pos_min_ = 0.0f;
		vertical_shake_power_ = 0.0f;
		vertical_shake_time_max_ = 0.0f;
		side_shake_power_ = 0.0f;
		side_shake_pos_min_ = 0.0f;
		side_shake_pos_max_ = 0.0f;
		is_vertical_shaking_ = false;
		side_shake_flag_	 = false;
		camera_pos_	= SimpleMath::Vector3::Zero;
	}
	~My_Camera() {};

	void Initialize();
	void Update(const float deltaTime, const ObjectManager* const obj_m_);

private:
	void ReadFile();
	void VerticalShake();
	void SideShake();

	DX9::CAMERA camera_; /**< カメラ格納 */

	int vertical_shake_state_; /**< カメラ縦揺れの状態 */
	int side_shake_state_; /**< カメラ横揺れの状態 */
	float time_delta_; /**< 時間 */
	float vertical_shake_time_; /**< 縦揺れする時間格納 */
	float camera_init_pos_x_; /**< カメラの初期X座標*/
	float camera_init_pos_y_; /**< カメラの初期Y座標 */
	float vertical_shake_pos_max_; /**< 縦揺れ時の最大Y座標 */
	float vertical_shake_pos_min_; /**< 縦揺れ時の最小Y座標　*/
	float vertical_shake_power_; /**< 縦揺れの強さ */
	float vertical_shake_time_max_; /**< 縦揺れする最大時間 */
	float side_shake_power_; /**< 横揺れする強さ */
	float side_shake_pos_min_; /**< 横揺れ時の最小X座標 */
	float side_shake_pos_max_; /**< 横揺れ時の最大X座標 */

	bool is_vertical_shaking_; /**< 縦揺れしているか */
	bool side_shake_flag_; /**< 横揺れするかフラグ */
	SimpleMath::Vector3 camera_pos_; /**< カメラの座標格納 */

	/**< カメラ揺れの種類 */
	enum SHAKE_STATE_ {
		Up, /**< 上 */
		Down, /**< 下 */
		Right, /**< 右 */
		Left /**< 左 */
	};

	const float FOV_Y_  = 45.0f; /**< Y方向の視野 */
	const float ASPECT_ = 16.0f / 9.0f; /**< アスペクト比 */
	const float NEAR_Z_ = 1.0f; /**< カメラが映す最小Z値 */
	const float FAR_Z_  = 10000.0f; /**< カメラが映す最大Z値 */
};