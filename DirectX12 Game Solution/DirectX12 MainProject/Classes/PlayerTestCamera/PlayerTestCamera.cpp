#include "Classes/PlayerTestCamera/PlayerTestCamera.h"
#include "Base/DX12Effekseer.h"

void PlayerTestCamera::Initialize() {
	camera->SetViewLookAt(
        SimpleMath::Vector3(0, CAMERA_POS_Y_, CAMERA_POS_Z_), //カメラの座標
        SimpleMath::Vector3(0, LOOK_AT_POS_Y, 0),   //注視する座標(この座標が画面の中心にくる)
        SimpleMath::Vector3::Up         //カメラの上向きベクトル(ロール回転)
    );
    camera->SetPerspectiveFieldOfView(XMConvertToRadians(45.0f), 16.0f / 9.0f, 1.0f, 10000.0f);
    DXTK->Direct3D9->SetCamera(camera);
    DX12Effect.SetCameraPosition(&camera);
}