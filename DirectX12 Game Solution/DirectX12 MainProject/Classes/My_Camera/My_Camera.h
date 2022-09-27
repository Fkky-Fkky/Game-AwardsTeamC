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
		is_vertical_shaking_ = false;
		side_shake_flag_	 = false;
		camera_pos_	= SimpleMath::Vector3::Zero;
	}
	~My_Camera() {};

	void Initialize();
	void Update(const float deltaTime, const ObjectManager* const obj_m_);

private:
	void VerticalShake();
	void SideShake();

	DX9::CAMERA camera_; /**< ƒJƒƒ‰Ši”[ */

	int vertical_shake_state_; /**< ƒJƒƒ‰c—h‚ê‚Ìó‘Ô */
	int side_shake_state_; /**< ƒJƒƒ‰‰¡—h‚ê‚Ìó‘Ô */
	float time_delta_; /**< ŠÔ */
	float vertical_shake_time_; /**< c—h‚ê‚·‚éŠÔ */
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

	const float CAMERA_POS_Y_  = 2.0f; /**< ƒJƒƒ‰‚ÌYÀ•W */
	const float CAMERA_POS_Z_  = -26.0f; /**< ƒJƒƒ‰‚ÌZÀ•W */
	const float LOOK_AT_POS_Y_ = 9.0f; /**< ’–Ú‚·‚éYÀ•W */
	const float FOV_Y_  = 45.0f; /**< Y•ûŒü‚Ì‹–ì */
	const float ASPECT_ = 16.0f / 9.0f; /**< ƒAƒXƒyƒNƒg”ä */
	const float NEAR_Z_ = 1.0f; /**< ƒJƒƒ‰‚ª‰f‚·Å¬Z’l */
	const float FAR_Z_  = 10000.0f; /**< ƒJƒƒ‰‚ª‰f‚·Å‘åZ’l */
	const float VERTICAL_SHAKE_POS_MAX_  = 2.0f; /**< c—h‚ê‚ÌÅ‘åYÀ•W */
	const float VERTICAL_SHAKE_POS_MIN_  = 0.5f; /**< c—h‚ê‚ÌÅ¬YÀ•W@*/
	const float VERTICAL_SHAKE_POWER_	 = 50.0f; /**< c—h‚ê‚Ì‹­‚³ */
	const float VERTICAL_SHAKE_TIME_MAX_ = 0.1f; /**< c—h‚ê‚·‚éŠÔ */
	const float SIDE_SHAKE_POWER_	= 7.0f; /**< ‰¡—h‚ê‚·‚é‹­‚³ */
	const float SIDE_SHAKE_POS_MIN_ = -0.3f; /**< ‰¡—h‚ê‚ÌÅ¬XÀ•W */
	const float SIDE_SHAKE_POS_MAX_ = 0.3f; /**< ‰¡—h‚ê‚ÌÅ‘åXÀ•W */
};