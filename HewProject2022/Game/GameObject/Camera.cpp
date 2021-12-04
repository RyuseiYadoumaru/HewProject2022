//*****************************************************************************
//!	@file	Game/GameObject/Camera.cpp
//!	@brief	
//!	@note	カメラクラス
//!	@note	全てのカメラの元となる
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Camera.h"

#include "../../Engine/Runtime/Core/TransformMatrix.h"
#include "../../Engine/Runtime/Application.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	オブジェクト名前
//==============================================================================
Create::Camera::Camera(std::string in_name) : Create::GameObject(in_name)
{
}

//==============================================================================
//!	@fn		Start
//!	@brief	初期化(仮想関数)
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Create::Camera::Start()
{
	return true;
}

//==============================================================================
//!	@fn		Update
//!	@brief	更新(仮想関数)
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Create::Camera::Update()
{
	SetCameraPos();
	return true;
}

//==============================================================================
//!	@fn		GetColor
//!	@brief	カラー情報取得
//!	@param	BackgroundColor
//==============================================================================
Math::Color* Create::Camera::GetBackgroundColor()
{
	return &BackgroundColor;
}

//==============================================================================
//!	@fn		GetLeft
//!	@brief	左端座標
//!	@param	左
//==============================================================================
float Create::Camera::GetLeft()
{
	float Pos = transform->Position.x - ((float)Application::SCREEN_WIDTH / 2.0f);
	return Pos;
}

//==============================================================================
//!	@fn		GetRight
//!	@brief	右端座標
//!	@param	右
//==============================================================================
float Create::Camera::GetRight()
{
	return transform->Position.x + ((float)Application::SCREEN_WIDTH / 2.0f);
}

//==============================================================================
//!	@fn		GetTop
//!	@brief	上座標
//!	@param	上
//==============================================================================
float Create::Camera::GetTop()
{
	return transform->Position.y - ((float)Application::SCREEN_HEIGHT / 2.0f);
}

//==============================================================================
//!	@fn		GetButtom
//!	@brief	下座標
//!	@param	下
//==============================================================================
float Create::Camera::GetButtom()
{
	return transform->Position.y + ((float)Application::SCREEN_HEIGHT / 2.0f);
}

//==============================================================================
//!	@fn		SetCameraPos
//!	@brief	カメラの座標更新
//!	@param	
//==============================================================================
void Create::Camera::SetCameraPos()
{

	/*	行列変換	*/
	TransformMatrix* transformMatrix = TransformMatrix::Instance();

	DirectX::XMFLOAT3 Pos =
	{
		transform->Position.x,
		transform->Position.y,
		0.0f
	};
	transformMatrix->SetCameraPosition(Pos);
}
