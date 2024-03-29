/**
* @file Ground.h
* @brief Xe[WABGMฬNX
* @author ใฝ
*/

#pragma once

/**
* CN[ht@C
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

class ObjectManager;

using namespace DirectX;

/**
* @brief GroundNX่`
*/
class Ground {
public:
	Ground() { 
		mist_pos_ = SimpleMath::Vector3(MIST_INIT_POS_X_, 0.0f, MIST_INIT_POS_Z_);
		is_frist_battle_ = false;
		first_bg_alpha_ = COLOR_MAX_;
		miset_speed_ = MIST_MOVE_SPEED_SLOW_;
		first_bgm_volume_ = 0.0f;
	}
	~Ground() {};

	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;
	void Render2D()const;

private:
	void BGMChange(const float deltaTime);

	DX9::MODEL stage_; /**< Xe[Wfi[ */
	DX9::SPRITE first_bg_; /**< Oผํwii[ */
	DX9::SPRITE second_bg_; /**< ใผํwii[ */
	DX9::SPRITE mist_; /**< ถwii[ */
	DX9::MEDIARENDERER first_battle_bgm_; /**< OผํBGMi[ */
	DX9::MEDIARENDERER second_battle_bgm_; /**< ใผํBGMi[ */

	float first_bg_alpha_; /**< OผํwiฬAt@li[ */
	float miset_speed_; /**< ถฬฎญฌxi[ */
	float first_bgm_volume_; /**< OผํBGMฬนสi[ */
	bool is_frist_battle_; /**< Oผํฉ */
	SimpleMath::Vector3 mist_pos_; /**< ถฬภWi[ */

	const float STAGE_POS_X_ = 35.0f; /**< Xe[WฬXภW */
	const float STAGE_POS_Z_ = -40.0f; /**< Xe[WฬZภW */
	const float STAGE_SCALE_ = 7.0f; /**< Xe[Wfฬๅซณ */
	const float FIRST_BG_POS_Z_ = 10000.0f; /**< OผํwiฬZภW */
	const float SECOND_BG_POS_Z_ = 9999.0f; /**< ใผํwiฬZภW */
	const float MIST_INIT_POS_Z_ = 9998.0f; /**< ถฬZภW */
	const float MIST_INIT_POS_X_ = -1280.0f; /**< ถฬ๚XภW */
	const float MIST_MOVE_SPEED_SLOW_ = 100.0f; /**< ถฬฺฎฌx(xข) */
	const float MIST_MOVE_SPEED_QUICK_ = 200.0f; /**< ถฬฺฎฌx(ฌข) */
	const float ADD_MIST_SPEED_  = 80.0f; /**< ถฬมฌx */
	const float ADD_ALPHA_SPEED_ = 300.0f; /**< At@lฬธฌx */
	const float COLOR_MAX_ = 255.0f; /**< Fฬลๅl */
	const float SPRITE_WIDTH_ = 1280.0f; /**< ๆฬลๅก */
	const float SPRITE_HIGHT_ = 720.0f; /**< ๆฬลๅc */
	const float BOSS_HP_HALF_ = 15.0f; /**< {XฬHPฬผช */
	const float VOLUME_SPEED_ = 900.0f; /**< นสธญฌx */
	const float VOLUME_MIN_ = -2000.0f; /**< นสฬลฌl */
};