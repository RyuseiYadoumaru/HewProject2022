//*****************************************************************************
//!	@file	Game/GameObject/Camera.cpp
//!	@brief	
//!	@note	カメラクラス
//!	@note	全てのカメラの元となる
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Camera.h"

#include "../../Engine/Runtime/Core/TransformMatrix.h"

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
	TransformMatrix* transformMatrix = TransformMatrix::Instance();

	DirectX::XMFLOAT3 Pos =
	{
		transform.Position.x,
		transform.Position.y,
		0.0f
	};
	transformMatrix->SetCameraPosition(Pos);

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
