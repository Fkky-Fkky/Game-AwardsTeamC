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

    ReadFile();

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
    bool is_vertical_shake_ = obj_m->IsCameraVerticalShake(); /**< 縦揺れをするか */
    side_shake_flag_ = obj_m->IsCameraSideShake();

    if (is_vertical_shake_ && !is_vertical_shaking_) {
        is_vertical_shaking_ = true;
    }

    VerticalShake();
    SideShake();
    camera_->SetPosition(camera_pos_);
    DXTK->Direct3D9->SetCamera(camera_);
}

/**
* @brief CSVファイル読み込みパラメーターを設定
*/
void My_Camera::ReadFile() {
    FILE* fp;
    if (fopen_s(&fp, "CSV/Camera_data.csv", "r") != 0) {
        assert(!"Camera_data.csvを開けません");
        throw std::exception();
    }

    char file_data_[256];
    fgets(file_data_, 255, fp);

    float camera_init_pos_z_; /**< カメラの初期Z座標 */
    float look_at_pos_x_; /**< 注目するX座標 */
    float look_at_pos_y_; /**< 注目するY座標 */
    float look_at_pos_z_; /**< 注目するZ座標 */
    fscanf_s(
        fp,
        "%f,%f,%f,%f,%f,%f,",
        &camera_init_pos_x_, &camera_init_pos_y_, &camera_init_pos_z_,
        &look_at_pos_x_, &look_at_pos_y_, &look_at_pos_z_
    );
    camera_->SetViewLookAt(
        SimpleMath::Vector3(camera_init_pos_x_, camera_init_pos_y_, camera_init_pos_z_), //カメラの座標
        SimpleMath::Vector3(look_at_pos_x_, look_at_pos_y_, look_at_pos_z_),   //注視する座標(この座標が画面の中心にくる)
        SimpleMath::Vector3::Up         //カメラの上向きベクトル(ロール回転)
    );

    fgets(file_data_, 255, fp);
    fgets(file_data_, 255, fp);
    fscanf_s(
        fp,
        "%f,%f,%f,%f,",
        &vertical_shake_time_max_, &vertical_shake_pos_max_, &vertical_shake_pos_min_, &vertical_shake_power_
    );
    fgets(file_data_, 255, fp);
    fgets(file_data_, 255, fp);
    fscanf_s(
        fp,
        "%f,%f,%f,",
        &side_shake_pos_max_, &side_shake_pos_min_, &side_shake_power_
    );
    fclose(fp);
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
        camera_pos_.y = std::min(camera_pos_.y + vertical_shake_power_ * time_delta_, vertical_shake_pos_max_);
        if (camera_pos_.y >= vertical_shake_pos_max_) {
            vertical_shake_state_ = Down;
        }
    }
    else if (vertical_shake_state_ == Down) {
        camera_pos_.y = std::max(camera_pos_.y - vertical_shake_power_ * time_delta_, vertical_shake_pos_min_);
        if (camera_pos_.y <= vertical_shake_pos_min_) {
            vertical_shake_state_ = Up;
        }
    }
    if (vertical_shake_time_ >= vertical_shake_time_max_) {
        vertical_shake_time_ = 0.0f;
        is_vertical_shaking_ = false;
        camera_pos_.y = camera_init_pos_y_;
    }
}

/**
* @brief カメラ横揺れ
*/
void My_Camera::SideShake() {
    if (!side_shake_flag_) {
        camera_pos_.x = camera_init_pos_x_;
        return;
    }

    if (side_shake_state_ == Right) {
        camera_pos_.x = std::min(camera_pos_.x + side_shake_power_ * time_delta_, side_shake_pos_max_);
        if (camera_pos_.x >= side_shake_pos_max_) {
            side_shake_state_ = Left;
        }
    }
    else if (side_shake_state_ == Left) {
        camera_pos_.x = std::max(camera_pos_.x - side_shake_power_ * time_delta_, side_shake_pos_min_);
        if (camera_pos_.x <= side_shake_pos_min_) {
            side_shake_state_ = Right;
        }
    }
}