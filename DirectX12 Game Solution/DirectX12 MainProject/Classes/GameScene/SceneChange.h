/**
* @file SceneChamge.h
* @brief �V�[���؂�ւ������N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

/**
* @brief SceneChange�N���X��`
*/
class SceneChange {
public:
	SceneChange() {
		black_alpha_ = 0.0f;
		white_alpha_ = 0.0f;
		wait_time_	 = 0.0f;
		scene_change_flag_ = false;
		is_game_start_ = false;
		is_game_clear_ = false;
	};

	~SceneChange() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* obj_m);
	void Render2D()const;

	/**
	* @brief �V�[����؂�ւ��邩
	* 
	* @retval TRUE �؂�ւ���
	* @retval FALSE �؂�ւ��Ȃ�
	*/
	bool IsSceneChange() const { return scene_change_flag_; }

	/**
	* @brief �Q�[�����N���A������
	* 
	* @retval TRUE �N���A
	* @retval FALSE �Q�[���I�[�o�[
	*/
	bool IsGameClear() const { return is_game_clear_; }

	/**
	* @brief �Q�[�����J�n���邩
	* 
	* @retval TRUE ����
	* @retval FALSE ���Ȃ�
	*/
	bool IsGameStart() const { return is_game_start_; }
private:
	DX9::SPRITE black_; /**< ���摜�i�[ */
	DX9::SPRITE white_; /**< ���摜�i�[ */

	float black_alpha_; /**< ���摜�̃A���t�@�l */
	float white_alpha_; /**< ���摜�̃A���t�@�l */
	float wait_time_; /**< �ҋ@���� */
	bool scene_change_flag_; /**< �V�[���؂�ւ��t���O */
	bool is_game_start_; /**< �Q�[�����J�n���邩 */
	bool is_game_clear_; /**< �Q�[�����N���A������ */

	const int WIDTH_MAX_ = 1280; /**< �����ő�l */
	const int HIGHT_MAX_ = 720; /**< �c���ő�l */
	const float ALPHA_SPEED_  = 180.0f; /**< �A���t�@�l�������x */
	const float COLOR_MAX_	  = 255.0f; /**< �F�̍ő�l */
	const float SPRITE_POS_Z_ = -10.0f; /**< �摜��Z���W */
	const float PLAYER_DEAD_WAIT_TIME_MAX_ = 1.5f; /**< �v���C���[���S���̑ҋ@���� */
	const float BOSS_DEAD_WAIT_TIME_MAX_   = 1.0f; /**< �{�X���S���̑ҋ@���� */
};