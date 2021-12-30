#include "Stage2.h"

using namespace Create;

bool GamePlay::Stage2Scene::Start()
{

	/*	オブジェクト生成	*/
	m_Map = make_shared<Map>("MapSizeTest_3");
	m_Player = make_shared<Player>("Player");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_Fade = make_shared<Fade>("Black");
	m_CuhsionStart = make_shared<Cuhsion>("CuhsionStart");
	m_CuhsionEnd = make_shared<Cuhsion>("CuhsionEnd");
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
	Instance(m_CuhsionStart.get());
	Instance(m_CuhsionEnd.get());
	Instance(m_Fade.get());
	Instance(m_ScreenEffect.get());
	Instance(m_CameraFrame.get());

	/*	初期化	*/
	m_Player->transform->Position.Set(-2500.0f, -500.0f, 0.0f);
	m_CuhsionEnd->transform->Position.x = CUHSION_DISTANCE;

	/*	ギミック初期化	*/
	m_Player->m_LandTile.Init(m_Player.get(), &m_Map->m_TileColumnList);

	/*	カメラ設定	*/
	SetCamera(m_MainCamera.get());
	m_MainCamera->Focus(m_Player.get());

	return true;
}

Scene::STATE GamePlay::Stage2Scene::Update()
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
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_CuhsionStart->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_CuhsionEnd->GetComponent<BoxCollider2D>());


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

bool GamePlay::Stage2Scene::End()
{
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
	m_BackGround->Render();

	/****	オブジェクト描画	****/
	m_CuhsionStart->Render();
	m_CuhsionEnd->Render();
	m_Map->Render();
	m_Player->Render();

	/****	デバッグ	****/
	//m_Player->Debug();
	//m_Map->Debug();
	//m_CuhsionStart->Debug();

	/****	画面エフェクト	****/
	m_Fade->Render();
	m_ScreenEffect->Render();
	m_CameraFrame->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}