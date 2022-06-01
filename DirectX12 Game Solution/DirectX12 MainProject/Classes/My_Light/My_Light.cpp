#include "Classes/My_Light/My_Light.h"

void My_Light::LoadAssets() {
    D3DLIGHT9 light{};
    light.Type     = D3DLIGHT_DIRECTIONAL;
    light.Ambient  = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
    light.Diffuse  = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
    light.Specular = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);

    //1つ目のライト
    light.Direction = DX9::VectorSet(-LIGHT_POS_X_, LIGHT_POS_Y_, LIGHT_POS_Z_);
    DXTK->Direct3D9->SetLight(0, light);

    //2つ目のライト
    light.Direction = DX9::VectorSet(LIGHT_POS_X_, LIGHT_POS_Y_, LIGHT_POS_Z_);
    DXTK->Direct3D9->SetLight(1, light);

    //3つ目のライト
    light.Ambient   = DX9::Colors::Value(0.3f, 0.3f, 0.3f, 1.0f);
    light.Diffuse   = DX9::Colors::Value(0.3f, 0.3f, 0.3f, 1.0f);
    light.Specular  = DX9::Colors::Value(0.3f, 0.3f, 0.3f, 1.0f);

    light.Direction = DX9::VectorSet(0.0f, -10.0f, 0.0f);
    DXTK->Direct3D9->SetLight(2, light);
}