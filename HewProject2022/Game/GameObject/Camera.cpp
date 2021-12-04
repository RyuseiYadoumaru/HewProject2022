//*****************************************************************************
//!	@file	Game/GameObject/Camera.cpp
//!	@brief	
//!	@note	�J�����N���X
//!	@note	�S�ẴJ�����̌��ƂȂ�
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Camera.h"

#include "../../Engine/Runtime/Core/TransformMatrix.h"
#include "../../Engine/Runtime/Application.h"

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
	SetCameraPos();
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

//==============================================================================
//!	@fn		GetLeft
//!	@brief	���[���W
//!	@param	��
//==============================================================================
float Create::Camera::GetLeft()
{
	float Pos = transform->Position.x - ((float)Application::SCREEN_WIDTH / 2.0f);
	return Pos;
}

//==============================================================================
//!	@fn		GetRight
//!	@brief	�E�[���W
//!	@param	�E
//==============================================================================
float Create::Camera::GetRight()
{
	return transform->Position.x + ((float)Application::SCREEN_WIDTH / 2.0f);
}

//==============================================================================
//!	@fn		GetTop
//!	@brief	����W
//!	@param	��
//==============================================================================
float Create::Camera::GetTop()
{
	return transform->Position.y - ((float)Application::SCREEN_HEIGHT / 2.0f);
}

//==============================================================================
//!	@fn		GetButtom
//!	@brief	�����W
//!	@param	��
//==============================================================================
float Create::Camera::GetButtom()
{
	return transform->Position.y + ((float)Application::SCREEN_HEIGHT / 2.0f);
}

//==============================================================================
//!	@fn		SetCameraPos
//!	@brief	�J�����̍��W�X�V
//!	@param	
//==============================================================================
void Create::Camera::SetCameraPos()
{

	/*	�s��ϊ�	*/
	TransformMatrix* transformMatrix = TransformMatrix::Instance();

	DirectX::XMFLOAT3 Pos =
	{
		transform->Position.x,
		transform->Position.y,
		0.0f
	};
	transformMatrix->SetCameraPosition(Pos);
}
