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
	//操作していないときは動かない
	if (Input::GetControllerLeftStick().x == 0) {
		m_SelectAnimController.AnimState = SelectAnimController::IDLE;
	}

	if (m_SelectAnimController.AnimState != SelectAnimController::RIGHT_END || m_SelectAnimController.AnimState != SelectAnimController::LEFT_END) {

		//右に傾けたら右にアニメーション
		if (Input::GetKeyPress(VK_RIGHT) == true || Input::GetControllerLeftStick().x < 0) {
			m_SelectAnimController.AnimState = SelectAnimController::RIGHT;
		}

		//左に傾けたら左にアニメーション
		if (Input::GetKeyPress(VK_LEFT) == true || Input::GetControllerLeftStick().x > 0) {
			m_SelectAnimController.AnimState = SelectAnimController::LEFT;
		}
	}

	return true;
}
