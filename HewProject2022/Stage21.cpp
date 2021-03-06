#include "Stage21.h"

using namespace Create;

bool GamePlay::Stage21Scene::Start()
{

	/*	オブジェクト生成	*/


	/*	インスタンス	*/
	m_Map = Instance<Map>(STAGE_5_1);
	m_Player = Instance<Player>("Player");
	m_MainCamera = Instance<MainCamera>("MainCamera");
	m_StorageStart = Instance<Storage>("StorageStart");
	m_World5_deskEnd = Instance<World5_desk>("World5_deskEnd");
	m_Fade = Instance<Fade>("Black");
	m_ScreenEffect = Instance<ScreenFx>("SFX");
	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("World5_BG");
	m_LayerBack = Instance<LayerBack>("LayerBack");
	m_LayerBack->Sprite("World5_obj1_1");
	m_GrayBack = Instance<GrayBack>("GrayBack");
	m_GrayBack->Sprite("Grey");

	/* ゴール時プレイヤーエフェクト生成 */
	m_PGoalEffect = Instance<PlayerGoalEffect>("PGoalEffect");


	/*	天井初期化	*/
	m_Ceiling = Instance<Ceiling>("Ceiling");
	m_Ceiling->Sprite("World5_ceiling");

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
	m_ResultCursor->NowScene = "Stage21";//現在のシーン設定
	m_Button->NowScene = m_ResultCursor->NowScene;

	m_ResultBack = Instance<Result>("ResultBack");
	m_ResultBack->ResultBack_init();

	/* リザルトアニメーションインスタンス生成 */
	m_Fireworks = Instance<Fireworks>("Fireworks");
	m_Star = Instance<Star>("Star");

	/*	初期化	*/
	m_World5_deskEnd->transform->Position.x += ROAD_DISTANCE;

	/*	ギミック初期化	*/


	/*	カメラ設定	*/
	SetCamera(m_MainCamera);
	m_MainCamera->Focus(m_Player);

	// BGM再生
	Sound::Sound_Play(SOUND_LABEL_WORLD5_GAMEBGM);

	Scene_State = 0;

	return true;
}

Scene::STATE GamePlay::Stage21Scene::Update()
{
	switch (Scene_State) {
	case 0:

		/****	当たり判定	****/

		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_StorageStart->GetComponent<BoxCollider2D>());
		m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_World5_deskEnd->GetComponent<BoxCollider2D>());


		/****	オブジェクト更新	****/
		ObjectUpdate();

		/***  ゴール判定用  ***/
		m_Goal->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Player->GetComponent<BoxCollider2D>());
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
	m_Map->SystemUpdate();
	SystemUpdate();
	return PLAY;
}

bool GamePlay::Stage21Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();
	/*	サウンドストップ	*/
	Sound::Sound_Stop(SOUND_LABEL_WORLD5_GAMEBGM);

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage21Scene::Render()
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

	/****	オブジェクト描画	****/
	ObjectRender<Storage>("StorageStart");
	ObjectRender<World5_desk>("World5_deskEnd");

	ObjectRender<Map>(STAGE_5_1);

	/*** ゴール描画 ***/
	ObjectRender<Goal>("Goal");
	ObjectRender<PlayerGoalEffect>("PGoalEffect");

	ObjectRender<Player>("Player");


	/****	デバッグ	****/
	//m_World5_deskEnd->Debug();
	//m_Map->Debug();
	//m_RoseStart->Debug();
	//m_Player->Debug();

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