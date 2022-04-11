#include "Classes/My_Camera/My_Camera.h"

void My_Camera::Initialize() {
	camera->SetView(SimpleMath::Vector3(0.0f, 30.0f, -10.0f), SimpleMath::Vector3(-25.1f,0.0f,0.0f));

	camera->SetPerspectiveFieldOfView(XM_PIDIV2, 16.0f / 9.0f, 1.0f, 10000.0f);
	DXTK->Direct3D9->SetCamera(camera);
}

void My_Camera::Update(){

}

void My_Camera::Render() {

}
