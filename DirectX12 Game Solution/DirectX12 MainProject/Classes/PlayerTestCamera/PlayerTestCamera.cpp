#include "Classes/PlayerTestCamera/PlayerTestCamera.h"

void PlayerTestCamera::Initialize() {
	camera->SetViewLookAt(
        SimpleMath::Vector3(0, 9.0f, -25), //カメラの座標
        SimpleMath::Vector3(0, 9.0f, 0),   //注視する座標(この座標が画面の中心にくる)
        SimpleMath::Vector3::Up         //カメラの上向きベクトル(ロール回転)
    );
    camera->SetPerspectiveFieldOfView(XMConvertToRadians(45.0f), 16.0f / 9.0f, 1.0f, 10000.0f);
    DXTK->Direct3D9->SetCamera(camera);
}

void PlayerTestCamera::Update() {

}

void PlayerTestCamera::Render() {

}