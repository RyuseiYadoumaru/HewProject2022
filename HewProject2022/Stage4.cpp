#include "Stage4.h"

using namespace Create;

bool GamePlay::Stage4Scene::Start()
{

	/*	オブジェクト生成	*/
	m_Map = make_shared<Map>("MapSizeTest_3");
	m_Player = make_shared<Player>("Player");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_Fade = make_shared<Fade>("Black");
	m_ChairStart = make_shared<Chair>("ChairStart");
	m_ChairEnd = make_shared<Chair>("ChairEnd");
	m_ScreenEffect = make_shared<ScreenFx>("SFX");
	m_CameraFrame = make_shared<CameraFrame>("CFX");


	/*	背景初期化	*/
	m_BackGround = make_shared<Actor>("Wall");
	m_BackGround->Sprite("Wall");
	Instance(m_BackGround.get());
	m_BackGround->transform->Position.Set(-40.0f, -200.0f, 0.0f);


	/*	インスタンス	*/
	Instance(m_Map.get());
	Instance(m_Player.get());
	Instance(m_ChairStart.get());
	Instance(m_ChairEnd.get());
	Instance(m_Fade.get());
	Instance(m_ScreenEffect.get());
	Instance(m_CameraFrame.get());

	/*	初期化	*/
	m_Player->transform->Position.Set(-2500.0f, -500.0f, 0.0f);
	m_ChairEnd->transform->Position.x = CHAIR_DISTANCE;

	/*	ギミック初期化	*/
	m_Player->m_LandTile.Init(m_Player.get(), &m_Map->m_TileColumnList);

	/*	カメラ設定	*/
	SetCamera(m_MainCamera.get());
	m_MainCamera->Focus(m_Player.get());

	return true;
}

Scene::STATE GamePlay::Stage4Scene::Update()
{
	/*	フレームカウント	*/
	static int cnt = 0;
	cnt++;
	cout << "\nフレーム" << cnt << endl;

	/****	ブロック移動	****/
	m_Map->CheckLandTile(&m_Player->m_LandTile);
	if (m_Player->m_LandTile.GetisLandTile() == false ||
		Input::GetControllerTrigger(XINPUT_GAMEPAD_X))
	{
		m_Map->MoveReset();
	}

	/****	オブジェクト更新	****/
	ObjectUpdate();

	/****	当たり判定	****/
	m_Map->HitCheckMap(*m_Player);
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_ChairStart->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_ChairEnd->GetComponent<BoxCollider2D>());


	/****	ロードシーン	****/
	//if (Input::GetKeyTrigger(PK_ENTER) == true ||
	//	Input::GetControllerTrigger(XINPUT_GAMEPAD_A))
	//{
	//	//GameEngine::SceneManager::LoadScene("ResultScene");
	//}

	/****	システム更新	****/
	m_Map->SystemUpdate();
	SystemUpdate();	return PLAY;
}

bool GamePlay::Stage4Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage4Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	背景	****/
	m_BackGround->Render();

	/****	オブジェクト描画	****/
	m_ChairStart->Render();
	m_ChairEnd->Render();
	m_Map->Render();
	m_Player->Render();

	/****	デバッグ	****/
	//m_Player->Debug();
	//m_Map->Debug();
	//m_ChairStart->Debug();

	/****	画面エフェクト	****/
	m_Fade->Render();
	m_ScreenEffect->Render();
	m_CameraFrame->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}