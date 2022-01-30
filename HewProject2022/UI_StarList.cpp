#include "UI_StarList.h"
#include "Player.h"


UI_StarList::UI_StarList(NAME inName) :GameObject(inName)
{
	//���z���������

	m_StarsList[0] = new UI_Star("UI_Star1");
	m_StarsList[1] = new UI_Star("UI_Star2");
	m_StarsList[2] = new UI_Star("UI_Star3");

}

bool UI_StarList::Start()
{
	for (int i = 0; i < 3; i++) {
		m_StarsList[i]->Start();
	}
	//�f�o�b�O�p
	/*m_StarsList[0]->Active = true;
	m_StarsList[1]->Active = true;
	m_StarsList[2]->Active = true;*/

	//���W�Z�b�g
	m_StarsList[0]->transform->Position.Set(LEFT_STAR_POSITION_X, STAR_POSITION_Y, 0.0f);
	m_StarsList[1]->transform->Position.Set(LEFT_STAR_POSITION_X + 88.0f, STAR_POSITION_Y, 0.0f);
	m_StarsList[2]->transform->Position.Set(LEFT_STAR_POSITION_X + 176.0f, STAR_POSITION_Y, 0.0f);

	//�T�C�Y�Z�b�g
	m_StarsList[0]->transform->Scale.Set(0.0f, 0.0f, 0.0f);
	m_StarsList[1]->transform->Scale.Set(0.0f, 0.0f, 0.0f);
	m_StarsList[2]->transform->Scale.Set(0.0f, 0.0f, 0.0f);

	return true;
}

bool UI_StarList::Update()
{
	//Player�̎擾�������̐����g���Ĕz��̒��̐���Active�ɂ���
	Player* m_Player = Create::Scene::GetGameObject<Player>("Player");

	if (m_Player->m_GetStar == 1 && m_StarsList[0]->Active == false) {
		m_StarsList[0]->Active = true;
	}
	if (m_Player->m_GetStar == 2 && m_StarsList[1]->Active == false) {
		m_StarsList[1]->Active = true;
	}
	if (m_Player->m_GetStar == 3 && m_StarsList[2]->Active == false) {
		m_StarsList[2]->Active = true;
	}

	/*	�������X�V	*/
	for (int i = 0; i < 3; i++) {
		if (m_StarsList[i]->Active == true) {//���������Ă�����
			m_StarsList[i]->Update();
		}
	}
	return true;
}

bool UI_StarList::Render()
{
	for (int i = 0; i < 3; i++) {
		if (m_StarsList[i]->Active == true) {//���������Ă�����
			m_StarsList[i]->Render();
		}
	}
	return true;
}

bool UI_StarList::End()
{
	for (int i = 0; i < 3; i++) {
		m_StarsList[i]->End();
		delete m_StarsList[i];
	}


	return true;
}

