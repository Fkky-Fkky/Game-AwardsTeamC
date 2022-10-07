#include "Classes/My_Light/My_Light.h"

/**
* @brief ライトの設定、設置
*/
void My_Light::LoadAssets() {
    FILE* fp;
    if (fopen_s(&fp, "CSV/Light_data.csv", "r") != 0) {
        assert(!"Light_data.csvを開けません");
        throw std::exception();
    }

    char file_data_[256];
    fgets(file_data_, 255, fp);

    float color_r_; /**< ライトの色R */
    float color_g_; /**< ライトの色G */
    float color_b_; /**< ライトの色B */
    float color_a_; /**< ライトの色A */
    float light_pos_x_; /**< 照らすX向き・座標 */
    float light_pos_y_; /**< 照らすY向き・座標 */
    float light_pos_z_; /**< 照らすZ向き・座標 */
    fscanf_s(
        fp,
        "%f,%f,%f,%f,%f,%f,%f,",
        &light_pos_x_, &light_pos_y_, &light_pos_z_,
        &color_r_, &color_g_, &color_b_, &color_a_
    );
    D3DLIGHT9 light{};
    //1つ目のライト(範囲ライト)
    light.Type = D3DLIGHT_DIRECTIONAL;
    light.Diffuse   = DX9::Colors::Value(color_r_, color_g_, color_b_, color_a_);
    light.Specular  = DX9::Colors::Value(color_r_, color_g_, color_b_, color_a_);
    light.Ambient   = DX9::Colors::Value(color_r_, color_g_, color_b_, color_a_);
    light.Direction = DX9::VectorSet(light_pos_x_, light_pos_y_, light_pos_z_);
    DXTK->Direct3D9->SetLight(0, light);

    fscanf_s(
        fp,
        "%f,%f,%f,%f,%f,%f,%f,",
        &light_pos_x_, &light_pos_y_, &light_pos_z_,
        &color_r_, &color_g_, &color_b_, &color_a_
    );
    //2つ目のライト(ポイントライト)
    light.Type     = D3DLIGHT_POINT;
    light.Diffuse  = DX9::Colors::Value(color_r_, color_g_, color_b_, color_a_);
    light.Specular = DX9::Colors::Value(color_r_, color_g_, color_b_, color_a_);
    light.Ambient  = DX9::Colors::Value(color_r_, color_g_, color_b_, color_a_);
    light.Position = DX9::VectorSet(light_pos_x_, light_pos_y_, light_pos_z_);
    light.Range    = RANGE_;
    light.Attenuation0 = 0.5f;
    light.Attenuation1 = 0.0f;
    light.Attenuation2 = 0.0f;
    DXTK->Direct3D9->SetLight(1, light);

    fclose(fp);
}