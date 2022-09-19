#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;
class ObjectManager;

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

	DX9::CAMERA camera_;

	int vertical_shake_state_;
	int side_shake_state_;
	float time_delta_;
	float vertical_shake_time_;
	bool is_vertical_shaking_;
	bool side_shake_flag_;
	SimpleMath::Vector3 camera_pos_;

	enum SHAKE_STATE_ {
		Up,
		Down,
		Right,
		Left
	};

	const float CAMERA_POS_Y_  = 2.0f;
	const float CAMERA_POS_Z_  = -26.0f;
	const float LOOK_AT_POS_Y_ = 9.0f;
	const float FOV_Y_  = 45.0f;
	const float ASPECT_ = 16.0f / 9.0f;
	const float NEAR_Z_ = 1.0f;
	const float FAR_Z_  = 10000.0f;
	const float VERTICAL_SHAKE_POS_MAX_  = 2.0f;
	const float VERTICAL_SHAKE_POS_MIN_  = 0.5f;
	const float VERTICAL_SHAKE_POWER_	 = 50.0f;
	const float VERTICAL_SHAKE_TIME_MAX_ = 0.1f;
	const float SIDE_SHAKE_POWER_	= 7.0f;
	const float SIDE_SHAKE_POS_MIN_ = -0.3f;
	const float SIDE_SHAKE_POS_MAX_ = 0.3f;
};