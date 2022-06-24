#include "Title.h"

Title::Title(string in_Name) : Actor(in_Name)
{
}

bool Title::Start()
{
	//Now_Scene = "TitleScene";
	m_SpriteRenderer->Init();
	this->Vertex("vs_Ui");										//��ʍ��W�̎擾
	this->transform->Position.Set(1920 / 2, (1080 / 2) - 70, 0);	//���W�����l�ݒ�
	this->GetComponent<SpriteRenderer>()->Color.a = 0;			//�����Ŕ�\����
	Logo_sw = true;												//�t���O�̏�����
	Frame_cnt = 0.0f;
	nowTime = 0.0f;
	return true;
}

bool Title::Fade_In()
{

	//���l���グ�Ă���
	if (this->GetComponent<SpriteRenderer>()->Color.a < 1.0f) {
		this->GetComponent<SpriteRenderer>()->Color.a += 0.008f;
	}
	return true;
}

bool Title::Fade_Out()
{
	//���l�������Ă���
	if (this->GetComponent<SpriteRenderer>()->Color.a > 0.0f) {
		this->GetComponent<SpriteRenderer>()->Color.a -= 0.008f;
	}
	return true;
}

bool Title::Fade_Switch()
{
	//�t���[���J�E���g�Ńt�F�[�h�C���E�t�F�[�h�A�E�g��ؑ�
	Frame_cnt++;

	//�f���^�^�C�����Z
	nowTime += GameTimer::deltaTime();

	/****	�^�C�g���t�F�[�h�A�j���[�V����	****/
	if (nowTime > fadeTime)
	{
		if (GameTimer::ErrorFPS() == false)
		{
			//FPS�����肵����t�F�[�h�A�E�g���s��
			this->Fade_Out();
		}
	}

	else
	{
		//�t�F�[�h�C��
		this->Fade_In();
	}


	//if (GameTimer::ErrorFPS() == true)
	//{
	//	if (Frame_cnt < 500) 
	//	{
	//		this->Fade_In();
	//	}
	//	else if (Frame_cnt >= 500 && GameTimer::ErrorFPS() == false) {
	//		this->Fade_Out();
	//	}

	//}

	//else
	//{
	//	if (Frame_cnt < 60) {
	//		this->Fade_In();
	//	}
	//	else if (Frame_cnt >= 60) {
	//		this->Fade_Out();
	//	}
	//}
	if (this->GetComponent<SpriteRenderer>()->Color.a <= 0) {
		Logo_sw = false;//�t���O�ؑցi�^�C�g���V�[���̃t���O�ؑցj
	}
	return true;
}

//�t���O�̎擾
bool Title::GetLogo_sw()
{
	return Logo_sw;
}
