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
