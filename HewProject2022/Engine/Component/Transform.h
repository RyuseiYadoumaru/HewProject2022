//*****************************************************************************
//!	@file	Engine/Component/Transform.h
//!	@brief	
//!	@note	�g�����X�t�H�[���N���X
//!	@note	�S�ẴI�u�W�F�N�g�̍��W�n������
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "Component.h"
#include "../Math/Vector3.h"
#include "../Runtime/Core/TransformMatrix.h"

namespace GameEngine
{

	class Transform : public Component
	{

	public:

		Math::Vector3 Position;
		Math::Vector3 Rotation;
		Math::Vector3 Scale;

	public:

		Transform();
		bool Update() override;
		XMFLOAT4X4 Get() const;
		XMFLOAT4X4* GetAddress();


	private:
		XMFLOAT4X4 WorldMatrix;

	private:
		void SetWorldMatrix();


	};
}

