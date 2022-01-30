#include "Stage19.h"

using namespace Create;

bool GamePlay::Stage19Scene::Start()
{
	/* インスタンス */
	m_Map = Instance<Map>(STAGE_4_4);
	m_Player = Instance<Player>("Player");
	m_MainCamera = Instance<MainCamera>("MainCamera");
	m_Fade = Instance<Fade>("Black");
	m_ScreenEffect = Instance<ScreenFx>("SFX");
	m_PicTureFrameStart = Instance<PictureFrame>("PicTureFrameStart");
	m_Shelf2End = Instance<Shelf2>("Shelf2End");

	/*	背景初期化	*/
	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("WORLD4_BG");

	m_LayerBack = Instance<LayerBack>("LayerBack");
	m_LayerBack->Sprite("world4_obj1_4");
	m_GrayBack = Instance<GrayBack>("GrayBack");
	m_GrayBack->Sprite("Grey4_4");
	m_LayerBack->transform->Position.y += 5.0f;
	m_GrayBack->transform->Position.y += 5.0f;

	/*	天井初期化	*/
	m_Ceiling = Instance<Ceiling>("Ceiling");
	m_Ceiling->Sprite("World4_ceiling");
	/*	初期化	*/
	m_Shelf2End->transform->Position.x += ROAD_DISTANCE;

	/* ゴール時プレイヤーエフェクト生成 */
	m_PGoalEffect = Instance<PlayerGoalEffect>("PGoalEffect");

	// BGM再生
	Sound::Sound_Play(SOUND_LABEL_WORLD4_GAMEBGM);

	/* Pause初期化 */
	m_Pause = Instance<Pause>("Pause");
	m_Pause->Sprite("ポーズ");

	m_Button = Instance<Pause>("Button");
	m_Button->Sprite("button_2");

	/*  ゴールインスタンス生成  */
	m_Goal = Instance<Goal>("Goal");

	// ゲーム画面UI初期化
	m_PlayModeUI = Instance<PlayModeUI>("PlayModeUI");
	m_waku = Instance<waku>("waku");

	/* リザルト初期化 */
	m_ResultFront = Instance<Result>("ResultFront");
	m_ResultFront->ResultFront_init();
	m_ResultCursor = Instance<Result>("ResultCursor");	//リザルト中カーソルのインスタンス生成
	m_ResultCursor->ResultCursor_Init();				//初期値セット
	m_ResultCursor->NowScene = "Stage19";//現在のシーン設定
	m_Button->NowScene = m_ResultCursor->NowScene;

	m_ResultBack = Instance<Result>("ResultBack");
	m_ResultBack->ResultBack_init();

	/* リザルトアニメーションインスタンス生成 */
	m_Fireworks = Instance<Fireworks>("Fireworks");
	m_Star = Instance<Star>("Star");

	/*	カメラ設定	*/
	SetCamera(m_MainCamera);
	m_MainCamera->Focus(m_Player);

	Scene_State = 0;

	return true;
}

Scene::STATE GamePlay::Stage19Scene::Update()
{
	/*	フレームカウント	*/
	static int cnt = 0;
	cnt++;
	cout << "\nフレーム" << cnt << endl;



	/****	オブジェクト更新	****/
	switch (Scene_State) {
	case 0:
		/****	当たり判定	****/
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_PicTureFrameStart->GetComponent<BoxCollider2D>());
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Shelf2End->GetComponent<BoxCollider2D>());

		/***  ゴール判定用  ***/
		m_Goal->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Player->GetComponent<BoxCollider2D>());

		/****	オブジェクト更新	****/
		ObjectUpdate();

		//当たったらゴール
		for (auto name : m_Goal->GetComponent<BoxCollider2D>()->GetHitObject())
		{
			if (name == m_Player->ToString())
			{
				if (m_Player->m_OnGround == true) {
					Scene_State = 2;//リザルト用分岐に移動
				}
			}
		}

		/* Pause処理　ON */
		if (Input::GetControllerTrigger(XINPUT_GAMEPAD_START) == true || Input::GetKeyTrigger(VK_ESCAPE)) {
			m_Pause->Pause_On();
			m_Button->Pause_On();
			Scene_State = 1;
		}


		break;
	case 1://ポーズ画面
	/****   ポーズ中処理   ****/
		m_Button->PauseCursor_Move();
		/* Pause処理　OFF */
		if (m_Button->Get_Checker() == 1 || Input::GetControllerTrigger(XINPUT_GAMEPAD_START) == true || Input::GetKeyTrigger(VK_ESCAPE)) {
			m_Pause->Pause_Off();
			m_Button->Pause_Off();
			Scene_State = 0;
		}
		break;
	case 2://リザルト画面

		m_Player->Goal(m_Goal->transform->Position.x);//ゴールアニメーション再生
		m_PGoalEffect->EF_Start();
		m_PGoalEffect->transform->Position.Set(m_Player->transform->Position.x, m_Player->transform->Position.y, 0);
		if (m_Player->GetGoal() == true) {//アニメーション終了でリザルト表示
			m_Star->StarChecker(m_Player->m_GetStar);
			m_Fireworks->Anim_Start();
			m_ResultFront->Result_On();//リザルト画面のフラグ
			m_ResultBack->Result_On();//リザルト画面のフラグ
			m_ResultCursor->Result_On();
			m_ResultCursor->ResultCursor_Move();//カーソルフラグ＆分岐
			m_Fade->Update();
		}
		break;
	}
	/****	システム更新	****/
	SystemUpdate();
	return PLAY;
}

bool GamePlay::Stage19Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();
	/*	サウンドストップ	*/
	Sound::Sound_Stop(SOUND_LABEL_WORLD4_GAMEBGM);

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage19Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();
	/****	背景	****/
	ObjectRender<BackGround>("Wall");

	/****	後装飾品	****/
	ObjectRender<LayerBack>("LayerBack");

	// グレー背景
	ObjectRender<GrayBack>("GrayBack");

	/****	天井	****/
	ObjectRender<Ceiling>("Ceiling");

	/*** ゴール描画 ***/
	ObjectRender<Goal>("Goal");
	ObjectRender<PlayerGoalEffect>("PGoalEffect");

	/****	オブジェクト描画	****/
	ObjectRender<Player>("Player");
	ObjectRender<Map>(STAGE_4_4);
	ObjectRender<PictureFrame>("PicTureFrameStart");
	ObjectRender<Shelf2>("Shelf2End");

	/****	画面エフェクト	****/
	//m_Fade->Render();
	ObjectRender<ScreenFx>("SFX");

	// ゲーム画面UI
	ObjectRender<PlayModeUI>("PlayModeUI");
	ObjectRender<waku>("waku");

	/*** リザルト ***/
	ObjectRender<Result>("ResultBack");
	ObjectRender<Fireworks>("Fireworks");
	ObjectRender<Star>("Star");
	ObjectRender<Result>("ResultFront");
	ObjectRender<Result>("ResultCursor");

	/*** フェード ***/
	m_Fade->Render();

	/**** Pause描画 ****/
	ObjectRender<Pause>("Pause");
	ObjectRender<Pause>("Button");

	/****	画面描画	****/
	SwapChain();

	return true;
}