#include "Classes/My_Light/My_Light.h"

void My_Light::LoadAssets() {
    D3DLIGHT9 light{};
    light.Type     = D3DLIGHT_DIRECTIONAL;
    light.Ambient  = DX9::Colors::Value(0.5f, 0.5f, 0.5f, 1.0f);
    light.Diffuse  = DX9::Colors::Value(0.5f, 0.5f, 0.5f, 1.0f);
    light.Specular = DX9::Colors::Value(0.5f, 0.5f, 0.5f, 1.0f);

    //1つ目のライト
    light.Direction = DX9::VectorSet(-10, -10, 10);
    DXTK->Direct3D9->SetLight(0, light);

    //2つ目のライト
    light.Direction = DX9::VectorSet(10, -10, 10);
    DXTK->Direct3D9->SetLight(1, light);

    //3つ目のライト
    light.Ambient  = DX9::Colors::Value(2.0f, 2.0f, 2.0f, 50.0f);
    light.Diffuse  = DX9::Colors::Value(2.0f, 2.0f, 2.0f, 50.0f);
    light.Specular = DX9::Colors::Value(2.0f, 2.0f, 2.0f, 50.0f);
    light.Direction = DX9::VectorSet(0, 10, 10);
    DXTK->Direct3D9->SetLight(2, light);
}