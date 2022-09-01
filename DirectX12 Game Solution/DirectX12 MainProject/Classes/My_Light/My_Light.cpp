#include "Classes/My_Light/My_Light.h"

void My_Light::LoadAssets() {
    //1つ目のライト
    light.Type = D3DLIGHT_DIRECTIONAL;
    light.Diffuse   = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
    light.Specular  = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
    light.Ambient   = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
    light.Direction = DX9::VectorSet(-20, -170, 80);
    DXTK->Direct3D9->SetLight(0, light);


    //2つ目のライト
    light.Type      = D3DLIGHT_POINT;
    light.Diffuse   = DX9::Colors::Value(50.0f, 5.0f, 10.0f, 1.0f);
    light.Specular  = DX9::Colors::Value(50.0f, 5.0f, 10.0f, 1.0f);
    light.Ambient   = DX9::Colors::Value(50.0f, 5.0f, 10.0f, 1.0f);
    light.Position  = DX9::VectorSet(LIGHT_POS_X_, LIGHT_POS_Y_, LIGHT_POS_Z_);
    light.Range     = 100.0f;
    light.Attenuation0 = 0.5f;
    light.Attenuation1 = 0.0f;
    light.Attenuation2 = 0.0f;
    DXTK->Direct3D9->SetLight(1, light);

    ////3つ目のライト
    //light.Ambient  = DX9::Colors::Value(4.0f, 1.0f, 1.0f, 50.0f);
    //light.Diffuse  = DX9::Colors::Value(4.0f, 1.0f, 1.0f, 50.0f);
    //light.Specular = DX9::Colors::Value(4.0f, 1.0f, 1.0f, 50.0f);
    //light.Direction = DX9::VectorSet(0, -1, 10);
    //DXTK->Direct3D9->SetLight(0, light);

    //light.Ambient  = DX9::Colors::Value(40.0f, 40.0f, 40.0f, 1.0f);
    //light.Diffuse  = DX9::Colors::Value(40.0f, 40.0f, 40.0f, 1.0f);
    //light.Specular = DX9::Colors::Value(40.0f, 40.0f, 40.0f, 1.0f);
    //light.Direction = DX9::VectorSet(0, -40, 50);
    //DXTK->Direct3D9->SetLight(0, light);
}

void My_Light::Update(const float deltaTime) {

}