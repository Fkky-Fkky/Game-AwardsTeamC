#include "Classes/PlayerTestCamera/PlayerTestCamera.h"
#include "Classes/Collision/ObjectManager.h"
#include "Base/DX12Effekseer.h"

void PlayerTestCamera::Initialize() {
	camera->SetViewLookAt(
        SimpleMath::Vector3(0, CAMERA_POS_Y_, CAMERA_POS_Z_), //カメラの座標
        SimpleMath::Vector3(0, LOOK_AT_POS_Y_, 0),   //注視する座標(この座標が画面の中心にくる)
        SimpleMath::Vector3::Up         //カメラの上向きベクトル(ロール回転)
    );
    camera->SetPerspectiveFieldOfView(XMConvertToRadians(FOV_Y_), ASPECT_, NEAR_Z_, FAR_Z_);
    DXTK->Direct3D9->SetCamera(camera);
    DX12Effect.SetCameraPosition(&camera);
    camera_pos_ = camera.GetPosition();
}

void PlayerTestCamera::Update(const float deltaTime, ObjectManager* obj_m_) {
    time_delta_ = deltaTime;
    bool is_ground_shake_ = obj_m_->IsGroundShake();

    if (is_ground_shake_ && !shake_flag_) {
        shake_flag_ = true;
    }
    CameraShake();
    DXTK->Direct3D9->SetCamera(camera);
}

void PlayerTestCamera::CameraShake() {  //カメラを揺らす
    if (!shake_flag_) {
        return;
    }
    shake_time_ += time_delta_;
    if (shake_state_ == Up) {
        camera_pos_.y = std::min(camera_pos_.y + SHAKE_POWER_ * time_delta_, SHAKE_POS_MAX_);
        if (camera_pos_.y >= SHAKE_POS_MAX_) {
            shake_state_ = Down;
        }
    }
    else if (shake_state_ == Down) {
        camera_pos_.y = std::max(camera_pos_.y - SHAKE_POWER_ * time_delta_, SHAKE_POS_MIN_);
        if (camera_pos_.y <= SHAKE_POS_MIN_) {
            shake_state_ = Up;
        }
    }
    if (shake_time_ >= SHAKE_TIME_MAX_) {
        shake_time_ = 0.0f;
        shake_flag_ = false;
        camera_pos_.y = CAMERA_POS_Y_;
    }
    camera->SetPosition(camera_pos_);
}