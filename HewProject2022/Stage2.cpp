#include "Stage2.h"

using namespace Create;

bool GamePlay::Stage2Scene::Start()
{
	/*	インスタンス	*/
	m_Map = Instance<Map>("stage1-2");
	m_Player = Instance<Player>("Player");
	m_MainCamera = Instance<MainCamera>("MainCamera");
	m_SofaStart = Instance<Sofa>("SofaStart");
	m_CuhsionEnd = Instance<Cuhsion>("ChusionEnd");
	m_Fade = Instance<Fade>("Black");
	m_ScreenEffect = Instance<ScreenFx>("SFX");
	m_CameraFrame = Instance<CameraFrame>("CFX");
	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("Wall");
	m_LayerBack = Instance<LayerBack>("LayerBack");
	m_LayerBack->Sprite("World1_obj1-2");
	m_LayerFront = Instance<LayerFront>("LayerFront");
	m_LayerFront->Sprite("World_obj2_1");

	/* Pause初期化 */
	m_Pause = Instance<Pause>("Pause");
	m_Pause->Sprite("ポーズ");

	m_Button = Instance<Pause>("Button");
	m_Button->Sprite("button");
	m_Button->NowScene = "Stage2";

	/*  ゴールインスタンス生成  */
	m_Goal = Instance<Goal>("Goal");

	/* リザルト初期化 */
	m_ResultBack = Instance<Result>("ResultBack");
	m_ResultBack->ResultBack_init();

	m_ResultCursor = Instance<Result>("ResultCursor");
	m_ResultCursor->ResultCursor_Init();
	m_ResultCursor->NowScene = "Stage2";

	/*	初期化	*/
	m_CuhsionEnd->transform->Position.x += ROAD_DISTANCE;

	// BGM再生
	Sound::Sound_Play(SOUND_LABEL_WORLD1_GAMEBGM);

	/*	カメラ設定	*/
	SetCamera(m_MainCamera);
	//m_MainCamera->Focus(m_Player);
	Scene_State = 0;
	return true;
}

Scene::STATE GamePlay::Stage2Scene::Update()
{
	/*	フレームカウント	*/
	static int cnt = 0;
	cnt++;
	cout << "\nフレーム" << cnt << endl;

	switch (Scene_State) {
	case 0:

		/****	当たり判定	****/
		m_Map->HitCheckMap(*m_Player);
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_SofaStart->GetComponent<BoxCollider2D>());
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_CuhsionEnd->GetComponent<BoxCollider2D>());
		/***  ゴール判定用  ***/
		m_Goal->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Player->GetComponent<BoxCollider2D>());

		/****	オブジェクト更新	****/
		ObjectUpdate();

		//当たったらゴール
		for (auto name : m_Goal->GetComponent<BoxCollider2D>()->GetHitObject()) {
			if (name == m_Player->ToString()) {
				Scene_State = 2;//リザルト用分岐に移動
				m_ResultBack->Result_On();
				m_ResultCursor->Result_On();
			}
		}

		/* Pause処理　ON */
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_START) == true) {
			m_Pause->Pause_On();
			m_Button->Pause_On();
			Scene_State = 1;
		}
		break;

	case 1://ポーズ画面
		/****   ポーズ中処理   ****/
		m_Button->PauseCursor_Move();
		/* Pause処理　OFF */
		if (m_Button->Get_Checker() == 1 || Input::GetControllerTrigger(XINPUT_GAMEPAD_START) == true) {
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
	/****	システム更新	****/
	m_Map->SystemUpdate();
	SystemUpdate();
	return PLAY;

}

bool GamePlay::Stage2Scene::End()
{
	/*	サウンドストップ	*/
	Sound::Sound_Stop(SOUND_LABEL_WORLD1_GAMEBGM);


	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}


bool GamePlay::Stage2Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	背景	****/
	ObjectRender<BackGround>("Wall");

	/****	後装飾品	****/
	ObjectRender<LayerBack>("LayerBack");

	/****	天井	****/
	ObjectRender<Ceiling>("Ceiling");

	/****	オブジェクト描画	****/
	ObjectRender<Sofa>("SofaStart");
	ObjectRender<Cuhsion>("ChusionEnd");

	ObjectRender<Map>("stage1-2");
	ObjectRender<Player>("Player");

	/*** ゴール描画 ***/
	ObjectRender<Goal>("Goal");

	/****	前装飾品	****/
	ObjectRender<LayerFront>("LayerFront");

	/****	デバッグ	****/
	//m_Player->Debug();
	//m_Map->Debug();
	//m_TableStart->Debug();

	/****	画面エフェクト	****/
	//m_Fade->Render();
	ObjectRender<ScreenFx>("SFX");
	ObjectRender<CameraFrame>("CFX");

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