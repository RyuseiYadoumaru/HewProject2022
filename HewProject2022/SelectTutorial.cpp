#include "SelectTutorial.h"

SelectTutorial::SelectTutorial(string in_Name)
{
}

bool SelectTutorial::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "selectAnimation";
	m_SpriteRenderer->SetSize(800.0f, 800.0f);
	this->Vertex("vs_Ui");
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Position.Set(975, 650, 0);

	/*	アニメーションコンポーネント　*/
	AddComponent<Animator>(&m_SelectAnimController);

	return true;
}

bool SelectTutorial::Update()
{
	return false;
}
