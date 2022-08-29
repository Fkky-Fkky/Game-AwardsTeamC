#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;
class ObjectManager;

class PlayerTestCamera {
public:
	PlayerTestCamera() {
		shake_state_ = Down;
		time_delta_ = 0.0f;
		shake_time_ = 0.0f;
		shake_flag_ = false;
		camera_pos_ = SimpleMath::Vector3::Zero;
	}
	~PlayerTestCamera() {};

	void Initialize();
	void Update(const float deltaTime, ObjectManager* obj_m_);
private:
	void CameraShake();

	DX9::CAMERA camera;
	
	int shake_state_;
	float time_delta_;
	float shake_time_;
	bool shake_flag_;
	SimpleMath::Vector3 camera_pos_;

	enum SHAKE_STATE_ {
		Up,
		Down
	};

	const float CAMERA_POS_Y_ = 2.0f;
	const float CAMERA_POS_Z_ = -26.0f;
	const float LOOK_AT_POS_Y_ = 9.0f;
	const float FOV_Y_ = 45.0f;
	const float ASPECT_ = 16.0f / 9.0f;
	const float NEAR_Z_ = 1.0f;
	const float FAR_Z_ = 10000.0f;
	const float SHAKE_POS_MAX_ = 2.0f;
	const float SHAKE_POS_MIN_ = 0.5f;
	const float SHAKE_POWER_ = 50.0f;
	const float SHAKE_TIME_MAX_ = 0.1f;
};