#include "SelectTutorial.h"

SelectTutorial::SelectTutorial(string in_Name)
{
}

bool SelectTutorial::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "selectAnimation";
	m_SpriteRenderer->SetSize(1920.0f, 1080.0f);
	this->Vertex("vs_Ui");
	m_SpriteRenderer->Init();

	/*	座標設定	*/
	transform->Position.Set(1920 / 2, 1080 / 2, 0);

	/*	アニメーションコンポーネント　*/
	AddComponent<Animator>(&m_SelectAnimController);

	return true;
}

bool SelectTutorial::Update()
{

	//右に傾けたら右にアニメーション
	if (Input::GetKeyPress(VK_RIGHT) == true || Input::GetControllerLeftStick().x > 0 && m_SelectAnimController.AnimState != SelectAnimController::RIGHT_END) {
		m_SelectAnimController.AnimState = SelectAnimController::RIGHT;
	}

	//左に傾けたら左にアニメーション
	else if (Input::GetKeyPress(VK_LEFT) == true || Input::GetControllerLeftStick().x < 0 && m_SelectAnimController.AnimState != SelectAnimController::LEFT_END) {
		m_SelectAnimController.AnimState = SelectAnimController::LEFT;
	}

	//操作していないときは動かない
	else if (Input::GetControllerLeftStick().x == 0) {
		m_SelectAnimController.AnimState = SelectAnimController::IDLE;
	}


	return true;
}
