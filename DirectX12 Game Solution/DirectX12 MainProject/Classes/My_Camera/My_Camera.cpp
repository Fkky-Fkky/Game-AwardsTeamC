#include "Classes/My_Camera/My_Camera.h"
#include "Classes/Object/ObjectManager.h"
#include "Base/DX12Effekseer.h"

/**
* @brief 値とカメラの初期化
*/
void My_Camera::Initialize() {
    vertical_shake_state_ = Down;
    side_shake_state_     = Right;
    time_delta_          = 0.0f;
    vertical_shake_time_ = 0.0f;
    is_vertical_shaking_ = false;
    side_shake_flag_     = false;

    camera_->SetViewLookAt(
        SimpleMath::Vector3(0, CAMERA_POS_Y_, CAMERA_POS_Z_), //カメラの座標
        SimpleMath::Vector3(0, LOOK_AT_POS_Y_, 0),   //注視する座標(この座標が画面の中心にくる)
        SimpleMath::Vector3::Up         //カメラの上向きベクトル(ロール回転)
    );
    camera_->SetPerspectiveFieldOfView(XMConvertToRadians(FOV_Y_), ASPECT_, NEAR_Z_, FAR_Z_);
    DXTK->Direct3D9->SetCamera(camera_);
    DX12Effect.SetCameraPosition(&camera_);
    camera_pos_ = camera_.GetPosition();
}

/**
* @brief カメラの更新
* 
* @param[in] deltaTime 時間
* @param[in] obj_m オブジェクトマネージャー
*/
void My_Camera::Update(const float deltaTime, const ObjectManager* const obj_m) {
    time_delta_ = deltaTime;
    bool is_vertical_shake_ = obj_m->IsGroundVerticalShake(); /**< 縦揺れをするか */
    side_shake_flag_ = obj_m->IsGroundSideShake();

    if (is_vertical_shake_ && !is_vertical_shaking_) {
        is_vertical_shaking_ = true;
    }

    VerticalShake();
    SideShake();
    camera_->SetPosition(camera_pos_);
    DXTK->Direct3D9->SetCamera(camera_);
}

/**
* @brief カメラ縦揺れ
*/
void My_Camera::VerticalShake() {
    if (!is_vertical_shaking_) {
        return;
    }
    vertical_shake_time_ += time_delta_;
    if (vertical_shake_state_ == Up) {
        camera_pos_.y = std::min(camera_pos_.y + VERTICAL_SHAKE_POWER_ * time_delta_, VERTICAL_SHAKE_POS_MAX_);
        if (camera_pos_.y >= VERTICAL_SHAKE_POS_MAX_) {
            vertical_shake_state_ = Down;
        }
    }
    else if (vertical_shake_state_ == Down) {
        camera_pos_.y = std::max(camera_pos_.y - VERTICAL_SHAKE_POWER_ * time_delta_, VERTICAL_SHAKE_POS_MIN_);
        if (camera_pos_.y <= VERTICAL_SHAKE_POS_MIN_) {
            vertical_shake_state_ = Up;
        }
    }
    if (vertical_shake_time_ >= VERTICAL_SHAKE_TIME_MAX_) {
        vertical_shake_time_ = 0.0f;
        is_vertical_shaking_ = false;
        camera_pos_.y = CAMERA_POS_Y_;
    }
}

/**
* @brief カメラ横揺れ
*/
void My_Camera::SideShake() {
    if (!side_shake_flag_) {
        camera_pos_.x = 0.0f;
        return;
    }

    if (side_shake_state_ == Right) {
        camera_pos_.x = std::min(camera_pos_.x + SIDE_SHAKE_POWER_ * time_delta_, SIDE_SHAKE_POS_MAX_);
        if (camera_pos_.x >= SIDE_SHAKE_POS_MAX_) {
            side_shake_state_ = Left;
        }
    }
    else if (side_shake_state_ == Left) {
        camera_pos_.x = std::max(camera_pos_.x - SIDE_SHAKE_POWER_ * time_delta_, SIDE_SHAKE_POS_MIN_);
        if (camera_pos_.x <= SIDE_SHAKE_POS_MIN_) {
            side_shake_state_ = Right;
        }
    }
}