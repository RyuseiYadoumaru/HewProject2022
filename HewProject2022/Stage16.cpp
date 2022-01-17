#include "Stage16.h"

using namespace Create;

bool GamePlay::Stage16Scene::Start()
{
	//オブジェクト生成 初期化
	m_stage16 = make_shared<Actor>("Stage-01");
	m_world4 = make_shared<Actor>("World-04");
	m_stage16->Sprite("stage-01");
	m_world4->Sprite("world-04");

	OldInstance(m_stage16.get());
	OldInstance(m_world4.get());

	///***  ゴール判定用  ***/
	//m_Goal->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Player->GetComponent<BoxCollider2D>());
	////当たったらゴール
	//for (auto name : m_Goal->GetComponent<BoxCollider2D>()->GetHitObject()) {
	//	if (name == m_Player->ToString()) {
	//		Scene_State = 2;//リザルト用分岐に移動
	//		m_ResultBack->Result_On();
	//		m_ResultCursor->Result_On();
	//	}
	//}

	/* Pause初期化 */
	m_Pause = Instance<Pause>("Pause");
	m_Pause->Sprite("ポーズ");

	m_Button = Instance<Pause>("Button");
	m_Button->Sprite("button");

	/*  ゴールインスタンス生成  */
	m_Goal = Instance<Goal>("Goal");

	/* リザルト初期化 */
	m_ResultBack = Instance<Result>("ResultBack");
	m_ResultBack->ResultBack_init();
	m_ResultCursor = Instance<Result>("ResultCursor");
	m_ResultCursor->ResultCursor_Init();
	m_ResultCursor->NowScene = "Stage16";
	

	m_stage16->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world4->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	カメラ設定	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	Scene_State = 0;

	return true;
}

Scene::STATE GamePlay::Stage16Scene::Update()
{
	switch (Scene_State) {
	case 0:
		/****	オブジェクト更新	****/
		ObjectUpdate();


		/****	ロードシーン	****/
		if (Input::GetKeyTrigger(PK_ENTER) == true || Input::GetControllerTrigger(XINPUT_GAMEPAD_B))//エンター押すと次のシーンへ移動
		{
			GameEngine::SceneManager::LoadScene("ResultScene");
		}

		/* Pause処理　ON */
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_START) == true) {
			m_Pause->Pause_On();
			m_Button->Pause_On();
			Scene_State = 1;
		}

		/****	システム更新	****/
		SystemUpdate();
		return PLAY;
		break;
	case 1://ポーズ画面
	/****   ポーズ中処理   ****/
		m_Button->PauseCursor_Move();
		/* Pause処理　OFF */
		if (m_Button->Get_Checker() == 1) {
			m_Pause->Pause_Off();
			m_Button->Pause_Off();
			Scene_State = 0;
		}
		break;
	case 2://リザルト画面
		m_ResultBack->Result_On();//リザルト画面のフラグ
		m_ResultCursor->ResultCursor_Move();//カーソルフラグ＆分岐
		break;
	}
}

bool GamePlay::Stage16Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage16Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_stage16->Render();
	m_world4->Render();

	/*** ゴール描画 ***/
	ObjectRender<Goal>("Goal");

	/**** Pause描画 ****/
	ObjectRender<Pause>("Pause");
	ObjectRender<Pause>("Button");

	/*** リザルト ***/
	ObjectRender<Result>("ResultBack");
	ObjectRender<Result>("ResultCursor");


	/****	画面描画	****/
	SwapChain();

	return true;
}
