#include "UI_StarList.h"
#include "Player.h"


UI_StarList::UI_StarList(NAME inName) :GameObject(inName)
{
	//星配列を初期化

	m_StarsList[0] = new UI_Star("UI_Star1");
	m_StarsList[1] = new UI_Star("UI_Star2");
	m_StarsList[2] = new UI_Star("UI_Star3");

}

bool UI_StarList::Start()
{
	for (int i = 0; i < 3; i++) {
		m_StarsList[i]->Start();
	}
	//デバッグ用
	/*m_StarsList[0]->Active = true;
	m_StarsList[1]->Active = true;
	m_StarsList[2]->Active = true;*/

	//座標セット
	m_StarsList[0]->transform->Position.Set(LEFT_STAR_POSITION_X, STAR_POSITION_Y, 0.0f);
	m_StarsList[1]->transform->Position.Set(LEFT_STAR_POSITION_X + 88.0f, STAR_POSITION_Y, 0.0f);
	m_StarsList[2]->transform->Position.Set(LEFT_STAR_POSITION_X + 176.0f, STAR_POSITION_Y, 0.0f);

	//サイズセット
	m_StarsList[0]->transform->Scale.Set(0.0f, 0.0f, 0.0f);
	m_StarsList[1]->transform->Scale.Set(0.0f, 0.0f, 0.0f);
	m_StarsList[2]->transform->Scale.Set(0.0f, 0.0f, 0.0f);

	return true;
}

bool UI_StarList::Update()
{
	//Playerの取得した星の数を使って配列の中の星をActiveにする
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

	/*	星たち更新	*/
	for (int i = 0; i < 3; i++) {
		if (m_StarsList[i]->Active == true) {//星が生きていたら
			m_StarsList[i]->Update();
		}
	}
	return true;
}

bool UI_StarList::Render()
{
	for (int i = 0; i < 3; i++) {
		if (m_StarsList[i]->Active == true) {//星が生きていたら
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

