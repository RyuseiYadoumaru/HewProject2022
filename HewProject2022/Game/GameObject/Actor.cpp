//*****************************************************************************
//!	@file	Game/GameObject/Actor.cpp
//!	@brief	
//!	@note	アクタークラス
//!	@note	静的オブジェクトの基底クラス
//!	@note	キャラクター以外のゲームオブジェクトに継承する
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Actor.h"
#include "../../Engine/Create/Scene.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param
//==============================================================================
Create::Actor::Actor() : GameObject()
{
	m_SpriteRenderer = AddRenderer<GameEngine::SpriteRenderer>();
}

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	オブジェクト名前
//==============================================================================
Create::Actor::Actor(std::string in_Name) : GameObject(in_Name)
{
	m_SpriteRenderer = AddRenderer<GameEngine::SpriteRenderer>();
}

//==============================================================================
//!	@fn		Start
//!	@brief	初期化
//!	@note	新しく処理を書きたいといはオーバーライドしてください
//!	@note	ここにスプライトレンダー初期化処理を必ず記述してください
//!	@note	今後記述しなくていいようにする予定です
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Create::Actor::Start()
{
	m_SpriteRenderer->Init();
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	return true;
}

//==============================================================================
//!	@fn		Update
//!	@brief	更新
//!	@note	新しく処理を書きたいといはオーバーライドしてください
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Create::Actor::Update()
{
	return true;
}

//==============================================================================
//!	@fn		End
//!	@brief	終了
//!	@note	新しく処理を書きたいといはオーバーライドしてください
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Create::Actor::End()
{
	return true;
}

//==============================================================================
//!	@fn		Render
//!	@brief	描画
//!	@note	基本的には新しく処理を書く必要がありません。
//!	@note	シーンクラスのRenderに描画したい順番に書いてください
//!	@note	時間があれば自動で描画する処理も作ります。期待しないでよね。
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Create::Actor::Render()
{
	if (Active == true)
	{
		m_SpriteRenderer->Render();
	}

	return true;
}

//==============================================================================
//!	@fn		SetSize
//!	@brief	セットサイズ
//!	@note	画像のサイズを調整する
//!	@retval	
//==============================================================================
void Create::Actor::SetSize(float in_SizeX, float in_SizeY)
{
	m_SpriteRenderer->SetSize(in_SizeX, in_SizeY);
}

//==============================================================================
//!	@fn		Sprite
//!	@brief	スプライト
//!	@note	描画したい画像の名前を入れる
//!	@retval	
//==============================================================================
void Create::Actor::Sprite(std::string in_SpriteName)
{
	m_SpriteRenderer->SpriteName = in_SpriteName;
	m_SpriteRenderer->SetSprite(in_SpriteName);
}

//==============================================================================
//!	@fn		Vertex
//!	@brief	頂点シェーダー
//!	@note	使いたい頂点シェーダーの名前を入れる
//!	@retval	
//==============================================================================
void Create::Actor::Vertex(std::string in_VertexName)
{
	m_SpriteRenderer->VertexShaderName = in_VertexName;
	m_SpriteRenderer->SetVertexShader(in_VertexName);
}

//==============================================================================
//!	@fn		Pixcel
//!	@brief	ピクセルシェーダー
//!	@note	使いたいピクセルシェーダーの名前を入れる
//!	@retval	
//==============================================================================
void Create::Actor::Pixcel(std::string in_PixcelName)
{
	m_SpriteRenderer->PixcelShaderName = in_PixcelName;
	m_SpriteRenderer->SetPixcelShader(in_PixcelName);
}
