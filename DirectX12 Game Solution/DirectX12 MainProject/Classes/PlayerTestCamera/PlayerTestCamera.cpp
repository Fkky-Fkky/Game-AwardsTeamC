#include "Classes/PlayerTestCamera/PlayerTestCamera.h"
#include "Base/DX12Effekseer.h"

void PlayerTestCamera::Initialize() {
	camera->SetViewLookAt(
        SimpleMath::Vector3(0, CAMERA_POS_Y_, CAMERA_POS_Z_), //�J�����̍��W
        SimpleMath::Vector3(0, LOOK_AT_POS_Y, 0),   //����������W(���̍��W����ʂ̒��S�ɂ���)
        SimpleMath::Vector3::Up         //�J�����̏�����x�N�g��(���[����])
    );
    camera->SetPerspectiveFieldOfView(XMConvertToRadians(45.0f), 16.0f / 9.0f, 1.0f, 10000.0f);
    DXTK->Direct3D9->SetCamera(camera);
    DX12Effect.SetCameraPosition(&camera);
}