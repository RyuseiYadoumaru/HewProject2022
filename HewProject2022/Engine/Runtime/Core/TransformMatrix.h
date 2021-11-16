//*****************************************************************************
//!	@file	Engine/Runtime/Core/TransformMatrix.h
//!	@brief	
//!	@note	ç¿ïWïœä∑çsóÒ
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include <DirectXMath.h>
#include "../Tools/macro.h"

#include <d3d11.h>
#include	<wrl/client.h>

using Microsoft::WRL::ComPtr;
using DirectX::XMMATRIX;
using DirectX::XMFLOAT4X4;
using DirectX::XMFLOAT3;

class TransformMatrix
{
public:

	ALIGN16 struct ConstanceBufferMatrixWorld
	{
		XMMATRIX Matrix;
	};

	ALIGN16 struct ConstanceBufferMatrixView
	{
		XMMATRIX Matrix;
	};

	ALIGN16 struct ConstanceBufferMatrixProjection
	{
		XMMATRIX Matrix;
	};

	ALIGN16 struct ConstanceBufferCameraPos
	{
		float CameraPos[4];
	};

	enum class TYPE
	{
		WORLD,
		VIEW,
		PROJECTION
	};

private:

	ConstanceBufferMatrixWorld m_World;
	ConstanceBufferMatrixView m_View;
	ConstanceBufferMatrixProjection m_Projection;

	ConstanceBufferCameraPos m_Camera;

	ComPtr<ID3D11Buffer> m_ConstanceBufferWorld;
	ComPtr<ID3D11Buffer> m_ConstanceBufferView;
	ComPtr<ID3D11Buffer> m_ConstanceBufferProjection;

	ComPtr<ID3D11Buffer> m_ConstanceBufferCameraPos;

public:

	TransformMatrix();

	static TransformMatrix* Instance();

	bool Init();

	bool SetTransformMatrix(TYPE in_Type, XMFLOAT4X4& in_Matrix);
	bool SetCameraPosition(XMFLOAT3& in_Position);

};


