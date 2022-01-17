#include "ResultScene.h"

using namespace Create;

bool GamePlay::ResultScene::Start()
{
	//オブジェクト生成 初期化
	m_ResultText = Instance<Actor>("ResultText");
	m_ResultText->Sprite("congratulations");
	m_ResultText->Vertex("vs_Ui");
	m_ResultText->transform->Position.Set(1920 / 2,(1080 / 2) - 300, 0);

	m_Cursor = Instance<Result>("Cursor");
	m_Cursor->Sprite("button");
	//m_Cursor->transform->Scale.Set(1.2, 1.2, 0);

	m_BackGround = Instance<BackGround>("BackGround");
	m_BackGround->Sprite("Aquarium");
	m_BackGround->Vertex("vs_Ui");
	m_BackGround->transform->Position.Set(0, 0, 0);
	m_BackGround->transform->Scale.Set(8, 8, 1);
	m_BackGround->GetComponent<SpriteRenderer>()->Color.a = 1;

	/*	カメラ	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::ResultScene::Update()
{
	/****	オブジェクト更新	****/
	ObjectUpdate();
	//m_Cursor->ResultCursor_Move();

	

	/****	システム更新	****/
	SystemUpdate();
	return PLAY;
}

bool GamePlay::ResultScene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();
	return true;
}

bool GamePlay::ResultScene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_BackGround->Render();
	m_ResultText->Render();
	//m_Cursor->Render();
	ObjectRender<Result>("Cursor");
	

	/****	画面描画	****/
	SwapChain();

	return true;
}