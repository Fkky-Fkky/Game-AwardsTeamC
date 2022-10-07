#include "Classes/My_Light/My_Light.h"

/**
* @brief ���C�g�̐ݒ�A�ݒu
*/
void My_Light::LoadAssets() {
    FILE* fp;
    if (fopen_s(&fp, "CSV/Light_data.csv", "r") != 0) {
        assert(!"Light_data.csv���J���܂���");
        throw std::exception();
    }

    char file_data_[256];
    fgets(file_data_, 255, fp);

    float color_r_; /**< ���C�g�̐FR */
    float color_g_; /**< ���C�g�̐FG */
    float color_b_; /**< ���C�g�̐FB */
    float color_a_; /**< ���C�g�̐FA */
    float light_pos_x_; /**< �Ƃ炷X�����E���W */
    float light_pos_y_; /**< �Ƃ炷Y�����E���W */
    float light_pos_z_; /**< �Ƃ炷Z�����E���W */
    fscanf_s(
        fp,
        "%f,%f,%f,%f,%f,%f,%f,",
        &light_pos_x_, &light_pos_y_, &light_pos_z_,
        &color_r_, &color_g_, &color_b_, &color_a_
    );
    D3DLIGHT9 light{};
    //1�ڂ̃��C�g(�͈̓��C�g)
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
    //2�ڂ̃��C�g(�|�C���g���C�g)
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