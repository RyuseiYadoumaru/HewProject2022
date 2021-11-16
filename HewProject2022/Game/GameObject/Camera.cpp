//*****************************************************************************
//!	@file	Game/GameObject/Camera.cpp
//!	@brief	
//!	@note	�J�����N���X
//!	@note	�S�ẴJ�����̌��ƂȂ�
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Camera.h"

#include "../../Engine/Runtime/Core/TransformMatrix.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	�I�u�W�F�N�g���O
//==============================================================================
Create::Camera::Camera(std::string in_name) : Create::GameObject(in_name)
{
}

//==============================================================================
//!	@fn		Start
//!	@brief	������(���z�֐�)
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Create::Camera::Start()
{
	return true;
}

//==============================================================================
//!	@fn		Update
//!	@brief	�X�V(���z�֐�)
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
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
//!	@brief	�J���[���擾
//!	@param	BackgroundColor
//==============================================================================
Math::Color* Create::Camera::GetBackgroundColor()
{
	return &BackgroundColor;
}
