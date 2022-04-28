#include "Classes/PlayerTestCamera/PlayerTestCamera.h"

void PlayerTestCamera::Initialize() {
	camera->SetViewLookAt(
        SimpleMath::Vector3(0, 9.0f, -25), //�J�����̍��W
        SimpleMath::Vector3(0, 9.0f, 0),   //����������W(���̍��W����ʂ̒��S�ɂ���)
        SimpleMath::Vector3::Up         //�J�����̏�����x�N�g��(���[����])
    );
    camera->SetPerspectiveFieldOfView(XMConvertToRadians(45.0f), 16.0f / 9.0f, 1.0f, 10000.0f);
    DXTK->Direct3D9->SetCamera(camera);
}

void PlayerTestCamera::Update() {

}

void PlayerTestCamera::Render() {

}