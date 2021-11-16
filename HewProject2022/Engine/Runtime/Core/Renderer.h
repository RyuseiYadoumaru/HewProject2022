//*****************************************************************************
//!	@file	Engine/Runtime/Core/Render.h
//!	@brief	
//!	@note	レンダークラス
//!	@note	レンダーのための一般的な機能
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include "../Graphics/DirectXGraphics.h"
#include "../Tools/macro.h"
#include "../Core/vsShader.h"
#include "../Core/psShader.h"

#include <DirectXMath.h>
#include <memory>

#include <d3d11.h>
#include	<wrl/client.h>

using Microsoft::WRL::ComPtr;

using DirectX::XMFLOAT2;
using DirectX::XMFLOAT3;
using DirectX::XMFLOAT4;
using DirectX::XMFLOAT4X4;
using DirectX::XMMATRIX;

namespace GameEngine
{
	class Renderer
	{

	public:
		struct VERTEX
		{
			DirectX::XMFLOAT3 Pos;
			DirectX::XMFLOAT4 Col;
			DirectX::XMFLOAT2 Tex;
		};

	protected:
		vsShader vertexShader;
		psShader pixcelShader;

	protected:

		ID3D11Buffer* VertexBuffer = nullptr;

	public:
		Renderer() {}
		virtual bool Init() = 0;
		virtual bool Render() = 0;
		virtual void Release() = 0;
	};
}