#include "StageTestScene.h"

bool StageTestScene::Start()
{
	cout << "ステージテストシーン" << endl;
	/*	オブジェクト生成	*/
	m_Map = make_shared<Map>();
	m_ProtPlayer = make_shared<Player>("ProtPlayer");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_BackGruond = make_shared<BackGround>("BackGorund");

	/*	オブジェクト初期化	*/
	m_Map->Start();
	m_ProtPlayer->Start();
	m_BackGruond->Start();

	/*	カメラセット	*/
	SetCamera(m_MainCamera.get());
	m_MainCamera->BackgroundColor = Math::Color::Blue;
	//m_MainCamera->Focus(m_ProtPlayer.get());

	/*　BGＭ再生　*/
	Sound::Sound_Play(SOUND_LABEL_BGM000);

	return true;
}

Scene::STATE StageTestScene::Update()
{

	if (Input::GetKeyTrigger(PK_ENTER) == true)//エンター押すとタイトルに戻る
	{
		GameEngine::SceneManager::LoadScene("ResultScene");
	}

	m_ProtPlayer->Update();
	m_Map->Update();
	m_BackGruond->Update();
	m_MainCamera->Update();



	return PLAY;
}

bool StageTestScene::End()
{
	return true;
}

bool StageTestScene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	背景	****/
	m_BackGruond->Render();

	/****	テスト	****/
	m_ProtPlayer->Render();

	/****	マップ描画	****/
	m_Map->Render();

	/****	画面描画	****/
	SwapChain();

	return true;

}