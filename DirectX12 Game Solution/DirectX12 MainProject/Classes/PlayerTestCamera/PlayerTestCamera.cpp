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
    bool is_ground_shake_ = obj_m_->IsGroundVerticalShake();
    bool is_ground_side_shake_ = obj_m_->IsGroundSideShake();
    if (is_ground_shake_ && !shake_flag_) {
        shake_flag_ = true;
    }

    side_shake_flag_ = is_ground_side_shake_;

    VerticalShake();
    SideShake();
    camera->SetPosition(camera_pos_);
    DXTK->Direct3D9->SetCamera(camera);
}

void PlayerTestCamera::VerticalShake() {  //カメラを揺らす
    if (!shake_flag_) {
        return;
    }
    shake_time_ += time_delta_;
    if (vertical_shake_state_ == Up) {
        camera_pos_.y = std::min(camera_pos_.y + SHAKE_POWER_ * time_delta_, SHAKE_POS_MAX_);
        if (camera_pos_.y >= SHAKE_POS_MAX_) {
            vertical_shake_state_ = Down;
        }
    }
    else if (vertical_shake_state_ == Down) {
        camera_pos_.y = std::max(camera_pos_.y - SHAKE_POWER_ * time_delta_, SHAKE_POS_MIN_);
        if (camera_pos_.y <= SHAKE_POS_MIN_) {
            vertical_shake_state_ = Up;
        }
    }
    if (shake_time_ >= SHAKE_TIME_MAX_) {
        shake_time_ = 0.0f;
        shake_flag_ = false;
        camera_pos_.y = CAMERA_POS_Y_;
    }
}

void PlayerTestCamera::SideShake() {    //カメラ横揺れ
    if (!side_shake_flag_) {
        camera_pos_.x = 0.0f;
        side_shake_power_ = 0.0f;
        return;
    }
    const float SIDE_SHAKE_POWER_ = 7.0f;

    /*side_shake_power_ = std::min(side_shake_power_ + 15.0f * time_delta_, SIDE_SHAKE_POWER_);*/
    side_shake_power_ = SIDE_SHAKE_POWER_;
    if (side_shake_state_ == Right) {
        camera_pos_.x = std::min(camera_pos_.x + side_shake_power_ * time_delta_, SHAKE_POS_X_MAX_);
        if (camera_pos_.x >= SHAKE_POS_X_MAX_) {
            side_shake_state_ = Left;
        }
    }
    else if (side_shake_state_ == Left) {
        camera_pos_.x = std::max(camera_pos_.x - side_shake_power_ * time_delta_, SHAKE_POS_X_MIN_);
        if (camera_pos_.x <= SHAKE_POS_X_MIN_) {
            side_shake_state_ = Right;
        }
    }
}