//*****************************************************************************
//!	@file	Engine/Component/Transform.cpp
//!	@brief	
//!	@note	�g�����X�t�H�[���N���X
//!	@note	�S�ẴI�u�W�F�N�g�̍��W�n������
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Transform.h"
#include<DirectXMath.h>

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
GameEngine::Transform::Transform()
{
	Position.Set(0.0f, 0.0f, 0.0f);
	Rotation.Set(0.0f, 0.0f, 0.0f);
	Scale.Set(1.0f, 1.0f, 1.0f);
	SetWorldMatrix();
}

//==============================================================================
//!	@fn		Update
//!	@brief	�X�V
//!	@param	
//==============================================================================
bool GameEngine::Transform::Update()
{
	SetWorldMatrix();
	return true;
}

//==============================================================================
//!	@fn		Get
//!	@brief	�ϊ��s��擾
//!	@param	
//==============================================================================
XMFLOAT4X4 GameEngine::Transform::Get() const
{
	return WorldMatrix;
}

//==============================================================================
//!	@fn		GetAddress
//!	@brief	�ϊ��s��A�h���X�擾
//!	@param	
//==============================================================================
XMFLOAT4X4* GameEngine::Transform::GetAddress()
{
	return &WorldMatrix;
}

//==============================================================================
//!	@fn		SetWorldMatrix
//!	@brief	���[���h���W�ϊ��s��
//!	@param	
//==============================================================================
void GameEngine::Transform::SetWorldMatrix()
{
	XMMATRIX mtxTransform = DirectX::XMMatrixTranslation
	(
		Position.x,
		Position.y,
		Position.z
	);

	XMMATRIX mtxRotX = DirectX::XMMatrixRotationX((DirectX::XMConvertToRadians(Rotation.x)));
	XMMATRIX mtxRotY = DirectX::XMMatrixRotationY((DirectX::XMConvertToRadians(Rotation.y)));
	XMMATRIX mtxRotZ = DirectX::XMMatrixRotationZ((DirectX::XMConvertToRadians(Rotation.z)));

	XMMATRIX mtxScale = DirectX::XMMatrixScaling
	(
		Scale.x,
		Scale.y,
		Scale.z
	);

	XMMATRIX mtx = mtxScale * mtxRotX * mtxRotY * mtxRotZ * mtxTransform;

	DirectX::XMStoreFloat4x4(&WorldMatrix, mtx);
}
