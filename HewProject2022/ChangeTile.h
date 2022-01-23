#pragma once
#include"Tile.h"
#include"ydmEngine.h"
#include"ChangeTileAnimController.h"

#define CHANGE_TIME 3000

class ChangeTile :public Tile
{
public:
	bool Start() override;
	bool Update() override;
	//bool Render()override;

private:
	//����ւ��F�̃p�[�^�[��
	enum Change_Pattern {
		CHANGE_3,
		CHANGE_4,
	};

	void Change3_AnimUpdate();//3�F����ւ��A�j���[�V��������

	void Change4_AnimUpdate();//4�F����ւ��A�j���[�V��������

	bool m_IsChanging;//����ւ������t���O

	string m_NowTexture;//���݂̃e�N�X�`��

	string m_NextTexture;//����ւ���̃e�N�X�`��

	Change_Pattern m_Change_Pattern;

	ChangeTileAnimController m_ChangeTileController;

	float m_ChangeTimer;   //�F���ς��܂ł̎���
};

