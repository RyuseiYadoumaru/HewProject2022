#include "ChangeTile.h"
#include "Map.h"

bool ChangeTile::Start()
{
	/*	初期座標保存	*/
	m_StartPosition = transform->Position;

	/*	スプライト初期化	*/
	m_SpriteRenderer->SetSize(TILE_WIDTH, TILE_HEIGHT);
	m_SpriteRenderer->Init();

	/*	ボックスコライダコンポーネント	*/
	AddComponent<BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	アニメーションコンポーネント	*/
	AddComponent<Animator>(&m_ChangeTileController);

	/*	何種類の色の入れ替えか	*/
	if (m_Kind == CR3 || m_Kind == CB3 || m_Kind == CG3) {
		m_Change_Pattern = CHANGE_3;
	}
	else {
		m_Change_Pattern = CHANGE_4;
	}

	/*	生成と同時にm_kindをC1(赤色)にする	*/
	//m_Kind = C1;

	/*	生成と同時に入れ替えタイルのm_kindを対象のカラーブロックの色(C1なら赤色等)に変える	*/
	switch (m_Kind)
	{
	case CR3:
		m_Kind = C1;
		break;
	case CB3:
		m_Kind = C2;
		break;
	case CG3:
		m_Kind = C3;
		break;
	case CR4:
		m_Kind = C1;
		break;
	case CB4:
		m_Kind = C2;
		break;
	case CG4:
		m_Kind = C3;
		break;
	case CP4:
		m_Kind = C4;
		break;
	default:
		break;
	}

	//trueだったら入れ替え中
	m_IsChanging = false;

	//タイマーを0にする//
	m_ChangeTimer = 0;

	/*	タグ設定	*/
	if (m_Kind != NB && m_Kind != NO && m_Kind != GR)
	{
		tag = ColorBlock;
	}
	else if (m_Kind == NB)
	{
		tag = NormalBlock;
	}
	else if (m_Kind == GR)
	{
		tag = Ground;
	}
	return true;
}

bool ChangeTile::Update()
{
	if (m_ChangeTimer >= CHANGE_TIME) {//3秒で入れ替える

		m_ChangeTileController.AnimState = ChangeTileAnimController::CHANGE;

		switch (m_Change_Pattern)
		{
		case ChangeTile::CHANGE_3:
			//ここに3色用の関数
			Change3_AnimUpdate();
			break;

		case ChangeTile::CHANGE_4:
			//ここに4色用の関数
			Change4_AnimUpdate();
			break;

		default:
			break;
		}
	}

	//ここで画像を変える
	//テクスチャ変える
	if (m_IsChanging == true)
	{
		if (m_ChangeTileController.AnimState == ChangeTileAnimController::EMPTY)
		{
			m_IsChanging = false;
			this->Sprite(m_NextTexture);
		}
		m_ChangeTimer = 0;
	}

	if (Map::m_MoveManager.empty() == true) {
		m_ChangeTimer += GameTimer::deltaTime();
	}

	return true;
}

/*  3色入れ替えアニメーション処理  */
void ChangeTile::Change3_AnimUpdate()
{
	switch (m_Kind)
	{
	case C1:
		//kind変える
		this->m_Kind = C2;//青にする
		m_NowTexture = "red_blue";//現在のテクスチャを保存する
		m_NextTexture = "blue_green";//入れ替え先のテクスチャを保存する
		m_IsChanging = true;

		break;

	case C2:
		this->m_Kind = C3;//緑にする
		m_NowTexture = "blue_green";//現在のテクスチャを保存する
		m_NextTexture = "green_red";//入れ替え先のテクスチャを保存する
		m_IsChanging = true;

		break;

	case C3:
		this->m_Kind = C1;//赤にする
		m_NowTexture = "green_red";//現在のテクスチャを保存する
		m_NextTexture = "red_blue";//入れ替え先のテクスチャを保存する
		m_IsChanging = true;
		break;

	default:
		break;
	}
}

/*  4色入れ替えアニメーション処理  */
void ChangeTile::Change4_AnimUpdate()
{
	switch (m_Kind)
	{
	case C1:
		//kind変える
		this->m_Kind = C2;//青にする
		m_NowTexture = "red_blue";//現在のテクスチャを保存する
		m_NextTexture = "blue_green";//入れ替え先のテクスチャを保存する
		m_IsChanging = true;
		break;

	case C2:
		this->m_Kind = C3;//緑にする
		m_NowTexture = "blue_green";//現在のテクスチャを保存する
		m_NextTexture = "green_purple";//入れ替え先のテクスチャを保存する
		m_IsChanging = true;
		break;

	case C3:
		this->m_Kind = C4;//紫にする
		m_NowTexture = "green_purple";//現在のテクスチャを保存する
		m_NextTexture = "purple_red";//入れ替え先のテクスチャを保存する
		m_IsChanging = true;
		break;

	case C4:
		this->m_Kind = C1;//赤にする
		m_NowTexture = "purple_red";//現在のテクスチャを保存する
		m_NextTexture = "red_blue";//入れ替え先のテクスチャを保存する
		m_IsChanging = true;
		break;

	default:
		break;
	}
}

//bool ChangeTile::Render()
//{
//	return true;
//}
