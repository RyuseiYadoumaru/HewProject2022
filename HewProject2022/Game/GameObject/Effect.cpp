//*****************************************************************************
//!	@file	Game/GameObject/Effect.cpp
//!	@brief	
//!	@note	エフェクトクラス
//!	@note	エフェクトの基底クラス
//!	@note	エフェクトゲームオブジェクトに継承する
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Effect.h"
#include "../../Engine/Create/Scene.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param
//==============================================================================
Create::Effect::Effect() : GameObject()
{
	m_Owner = nullptr;
	m_SpriteRenderer = AddRenderer<GameEngine::SpriteRenderer>();
}

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	オブジェクト名前
//==============================================================================
Create::Effect::Effect(std::string in_Name) : GameObject(in_Name)
{
	m_Owner = nullptr;
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
bool Create::Effect::Start()
{
	m_SpriteRenderer->Init();
	return true;
}

//==============================================================================
//!	@fn		Update
//!	@brief	更新
//!	@note	新しく処理を書きたいといはオーバーライドしてください
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Create::Effect::Update()
{
	return true;
}

//==============================================================================
//!	@fn		End
//!	@brief	終了
//!	@note	新しく処理を書きたいといはオーバーライドしてください
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Create::Effect::End()
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
bool Create::Effect::Render()
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
void Create::Effect::SetSize(float in_SizeX, float in_SizeY)
{
	m_SpriteRenderer->SetSize(in_SizeX, in_SizeY);
}

//==============================================================================
//!	@fn		Sprite
//!	@brief	スプライト
//!	@note	描画したい画像の名前を入れる
//!	@retval	
//==============================================================================
void Create::Effect::Sprite(std::string in_SpriteName)
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
void Create::Effect::Vertex(std::string in_VertexName)
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
void Create::Effect::Pixcel(std::string in_PixcelName)
{
	m_SpriteRenderer->PixcelShaderName = in_PixcelName;
	m_SpriteRenderer->SetPixcelShader(in_PixcelName);
}

//==============================================================================
//!	@fn		SetOwnerTransform
//!	@brief	トランスフォーム設定
//!	@note	オーナーのトランスフォームを設定する
//!	@retval	
//==============================================================================
void Create::Effect::SetOwnerTransform()
{
	if (m_Owner != nullptr)
	{
		transform = m_Owner->transform;
	}
}
