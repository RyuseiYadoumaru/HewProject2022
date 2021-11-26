#include "StageTestScene.h"

bool StageTestScene::Start()
{
	cout << "ステージテストシーン" << endl;
	/*	オブジェクト生成	*/
	m_Map = make_shared<Map>();
	m_Test = make_shared<GamePlay::Test>("Hanamaru");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_BackGruond = make_shared<BackGround>("BackGorund");

	/*	オブジェクト初期化	*/
	m_Map->Start();
	m_Test->Start();
	m_BackGruond->Start();

	/*	カメラセット	*/
	SetCamera(m_MainCamera.get());
	m_MainCamera->BackgroundColor = Math::Color::Blue;
	m_MainCamera->Focus(m_Test.get());
	return true;
}

Scene::STATE StageTestScene::Update()
{

	/*	ブロック挙動	*/
	if (Input::GetKeyTrigger(PK_ENTER) == true && m_Map->GetisMove() == false)
	{
		m_Map->MoveSwicthON();
		Tile* Debug = m_Map->m_TileColumnList[24].mp_Column[0];
		m_Map->MoveMap(Debug);

	}
	/*	ブロック挙動	*/
	if (Input::GetKeyTrigger(PK_1) == true && m_Map->GetisMove() == false)
	{
		m_Map->MoveSwicthON();
		Tile* Debug = m_Map->m_TileColumnList[26].mp_Column[1];
		m_Map->MoveMap(Debug);
	}
	/*	ブロック挙動	*/
	if (Input::GetKeyTrigger(PK_2) == true && m_Map->GetisMove() == false)
	{
		m_Map->MoveSwicthON();
		Tile* Debug = m_Map->m_TileColumnList[31].mp_Column[4];
		m_Map->MoveMap(Debug);
	}
	/*	ブロック挙動	*/
	if (Input::GetKeyTrigger(PK_3) == true && m_Map->GetisMove() == false)
	{
		m_Map->MoveSwicthON();
		Tile* Debug = m_Map->m_TileColumnList[23].mp_Column[0];
		m_Map->MoveMap(Debug);
	}


	m_Test->Update();
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
	m_Test->Render();

	/****	マップ描画	****/
	m_Map->Render();

	/****	画面描画	****/
	SwapChain();

	return true;

}