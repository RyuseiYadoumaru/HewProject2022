#include "Stage5.h"

using namespace Create;

bool GamePlay::Stage5Scene::Start()
{

	/*	オブジェクト生成	*/
	m_Map = make_shared<Map>("stage1-5");
	m_Player = make_shared<Player>("Player");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_Fade = make_shared<Fade>("Black");
	m_DeskStart = make_shared<Desk>("DeskStart");
	m_DeskEnd = make_shared<Desk>("DeskEnd");
	m_ScreenEffect = make_shared<ScreenFx>("SFX");
	m_CameraFrame = make_shared<CameraFrame>("CFX");


	/*	背景初期化	*/
	m_BackGround = make_shared<BackGround>("Wall");
	m_BackGround->Sprite("Wall");
	OldInstance(m_BackGround.get());

	m_LayerBack = make_shared<LayerBack>("LayerBack");
	m_LayerBack->Sprite("World_obj1_5");
	OldInstance(m_LayerBack.get());

	m_LayerFront = make_shared<LayerFront>("LayerFront");
	m_LayerFront->Sprite("World_obj2_5");
	OldInstance(m_LayerFront.get());

	/*	天井初期化	*/
	m_Ceiling = make_shared<Ceiling>("Ceiling");
	m_Ceiling->Sprite("ceiling");
	OldInstance(m_Ceiling.get());


	/*	インスタンス	*/
	OldInstance(m_Map.get());
	OldInstance(m_Player.get());
	OldInstance(m_DeskStart.get());
	OldInstance(m_DeskEnd.get());
	OldInstance(m_Fade.get());
	OldInstance(m_ScreenEffect.get());
	OldInstance(m_CameraFrame.get());

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
	m_ResultCursor->NowScene = "Stage1";
	


	/*	初期化	*/
	m_DeskEnd->transform->Position.x += ROAD_DISTANCE;

	/*	ギミック初期化	*/
	m_Player->m_LandTile.Init(m_Player.get(), &m_Map->m_TileColumnList);

	/*	カメラ設定	*/
	OldSetCamera(m_MainCamera.get());
	//m_MainCamera->Focus(m_Player.get());

	Scene_State = 0;

	return true;
}

Scene::STATE GamePlay::Stage5Scene::Update()
{
	/*	フレームカウント	*/
	static int cnt = 0;
	cnt++;
	cout << "\nフレーム" << cnt << endl;

	switch (Scene_State) {
	case 0:
		/****	ブロック移動	****/
		m_Map->CheckLandTile(&m_Player->m_LandTile);
		if (((m_Player->m_LandTile.GetisLandTile() == false) ||
			(Input::GetControllerTrigger(XINPUT_GAMEPAD_X)) || Input::GetKeyTrigger(PK_R)) &&
			(m_Map->m_OnReset == false))
		{
			//リセット発動
			m_Map->m_OnReset = true;
		}

		/****	オブジェクト更新	****/
		ObjectUpdate();

		/****	当たり判定	****/
		m_Map->HitCheckMap(*m_Player);
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_DeskStart->GetComponent<BoxCollider2D>());
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_DeskEnd->GetComponent<BoxCollider2D>());

		/***  ゴール判定用  ***/
		m_Goal->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Player->GetComponent<BoxCollider2D>());
		//当たったらゴール
		for (auto name : m_Goal->GetComponent<BoxCollider2D>()->GetHitObject()) {
			if (name == m_Player->ToString()) {
				Scene_State = 2;//リザルト用分岐に移動
				m_ResultBack->Result_On();
				m_ResultCursor->Result_On();
			}
		}

		/****	ロードシーン	****/
		//if (Input::GetKeyTrigger(PK_ENTER) == true ||
		//	Input::GetControllerTrigger(XINPUT_GAMEPAD_A))
		//{
		//	//GameEngine::SceneManager::LoadScene("ResultScene");
		//}

		/* Pause処理　ON */
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_START) == true) {
			m_Pause->Pause_On();
			m_Button->Pause_On();
			Scene_State = 1;
		}

		/****	システム更新	****/
		m_Map->SystemUpdate();
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

bool GamePlay::Stage5Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage5Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	背景	****/
	m_BackGround->Render();

	/****	後装飾品	****/
	m_LayerBack->Render();

	/****	天井	****/
	m_Ceiling->Render();

	/****	オブジェクト描画	****/
	m_DeskStart->Render();
	m_DeskEnd->Render();

	m_Map->Render();
	m_Player->Render();

	/*** ゴール描画 ***/
	ObjectRender<Goal>("Goal");

	/****	前装飾品	****/
	m_LayerFront->Render();

	/****	デバッグ	****/
	//m_Player->Debug();
	//m_Map->Debug();
	//m_TableStart->Debug();

	/****	画面エフェクト	****/
	//m_Fade->Render();
	m_ScreenEffect->Render();
	m_CameraFrame->Render();

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