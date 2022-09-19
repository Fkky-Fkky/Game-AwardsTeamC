#include "Classes/My_Light/My_Light.h"

void My_Light::LoadAssets() {
    D3DLIGHT9 light{};
    //1�ڂ̃��C�g
    light.Type = D3DLIGHT_DIRECTIONAL;
    light.Diffuse   = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
    light.Specular  = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
    light.Ambient   = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
    light.Direction = DX9::VectorSet(DIRECTION_X_, DIRECTION_Y_, DIRECTION_Z_);
    DXTK->Direct3D9->SetLight(0, light);

    //2�ڂ̃��C�g
    light.Type      = D3DLIGHT_POINT;
    light.Diffuse   = DX9::Colors::Value(50.0f, 5.0f, 10.0f, 1.0f);
    light.Specular  = DX9::Colors::Value(50.0f, 5.0f, 10.0f, 1.0f);
    light.Ambient   = DX9::Colors::Value(50.0f, 5.0f, 10.0f, 1.0f);
    light.Position  = DX9::VectorSet(LIGHT_POS_X_, LIGHT_POS_Y_, LIGHT_POS_Z_);
    light.Range     = RANGE_;
    light.Attenuation0 = 0.5f;
    light.Attenuation1 = 0.0f;
    light.Attenuation2 = 0.0f;
    DXTK->Direct3D9->SetLight(1, light);
}