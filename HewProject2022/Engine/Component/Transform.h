//*****************************************************************************
//!	@file	Engine/Component/Transform.h
//!	@brief	
//!	@note	トランスフォームクラス
//!	@note	全てのオブジェクトの座標系をする
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

