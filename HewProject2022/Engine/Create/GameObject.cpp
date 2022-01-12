//*****************************************************************************
//!	@file	Engine/Create/GameObject.cpp
//!	@brief	
//!	@note	ゲームオブジェクトクラス
//!	@note	ゲームオブジェクトの元となる
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "GameObject.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
Create::GameObject::GameObject()
{
	Active = true;
	name = "NoName";
	id += ObjectNum + GAMEOBJECT_ID;
	transform = AddComponent<GameEngine::Transform>();
}

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	オブジェクト名前
//==============================================================================
Create::GameObject::GameObject(std::string in_Name)
{
	Active = true;
	name = in_Name;
	id += ObjectNum + GAMEOBJECT_ID;
	transform = AddComponent<GameEngine::Transform>();

}

//==============================================================================
//!	@fn		GetTransform
//!	@brief	トランスフォーム取得
//!	@param	
//!	@retval	transform
//==============================================================================
Transform Create::GameObject::GetTransform()
{
	return *transform;
}

//==============================================================================
//!	@fn		Render
//!	@brief	描画
//!	@note	基本的には新しく処理を書く必要がありません。
//!	@note	シーンクラスのRenderに描画したい順番に書いてください
//!	@note	時間があれば自動で描画する処理も作ります。期待しないでよね。
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Create::GameObject::Render()
{
	return true;
}
