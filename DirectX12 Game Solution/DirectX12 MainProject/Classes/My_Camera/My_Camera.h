/**
* @file My_Camera.h
* @brief ƒJƒƒ‰‚Ìˆ—ƒNƒ‰ƒX
* @author ãƒ•½
*/

#pragma once

/**
* ƒCƒ“ƒNƒ‹[ƒhƒtƒ@ƒCƒ‹
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;
class ObjectManager;

/**
* @brief My_CameraƒNƒ‰ƒX’è‹`
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

	DX9::CAMERA camera_; /**< ƒJƒƒ‰Ši”[ */

	int vertical_shake_state_; /**< ƒJƒƒ‰c—h‚ê‚Ìó‘Ô */
	int side_shake_state_; /**< ƒJƒƒ‰‰¡—h‚ê‚Ìó‘Ô */
	float time_delta_; /**< ŠÔ */
	float vertical_shake_time_; /**< c—h‚ê‚·‚éŠÔŠi”[ */
	float camera_init_pos_x_; /**< ƒJƒƒ‰‚Ì‰ŠúXÀ•W*/
	float camera_init_pos_y_; /**< ƒJƒƒ‰‚Ì‰ŠúYÀ•W */
	float vertical_shake_pos_max_; /**< c—h‚ê‚ÌÅ‘åYÀ•W */
	float vertical_shake_pos_min_; /**< c—h‚ê‚ÌÅ¬YÀ•W@*/
	float vertical_shake_power_; /**< c—h‚ê‚Ì‹­‚³ */
	float vertical_shake_time_max_; /**< c—h‚ê‚·‚éÅ‘åŠÔ */
	float side_shake_power_; /**< ‰¡—h‚ê‚·‚é‹­‚³ */
	float side_shake_pos_min_; /**< ‰¡—h‚ê‚ÌÅ¬XÀ•W */
	float side_shake_pos_max_; /**< ‰¡—h‚ê‚ÌÅ‘åXÀ•W */

	bool is_vertical_shaking_; /**< c—h‚ê‚µ‚Ä‚¢‚é‚© */
	bool side_shake_flag_; /**< ‰¡—h‚ê‚·‚é‚©ƒtƒ‰ƒO */
	SimpleMath::Vector3 camera_pos_; /**< ƒJƒƒ‰‚ÌÀ•WŠi”[ */

	/**< ƒJƒƒ‰—h‚ê‚Ìí—Ş */
	enum SHAKE_STATE_ {
		Up, /**< ã */
		Down, /**< ‰º */
		Right, /**< ‰E */
		Left /**< ¶ */
	};

	const float FOV_Y_  = 45.0f; /**< Y•ûŒü‚Ì‹–ì */
	const float ASPECT_ = 16.0f / 9.0f; /**< ƒAƒXƒyƒNƒg”ä */
	const float NEAR_Z_ = 1.0f; /**< ƒJƒƒ‰‚ª‰f‚·Å¬Z’l */
	const float FAR_Z_  = 10000.0f; /**< ƒJƒƒ‰‚ª‰f‚·Å‘åZ’l */
};