//*****************************************************************************
//!	@file	Engine/Component/SpriteRenderer.h
//!	@brief	
//!	@note	2Dグラフィックスのスプライトをレンダリング
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include <DirectXMath.h>
#include "../Runtime/Core/Renderer.h"
#include "../Runtime/Core/Sprite.h"
#include "../Math/Color.h"
#include "../Math/CRect.h"

using DirectX::XMFLOAT4X4;

namespace GameEngine
{
	class SpriteRenderer : public Renderer
	{
	public:
		std::string SpriteName;
		Math::Color Color;
		std::string VertexShaderName;
		std::string PixcelShaderName;

	public:
		SpriteRenderer(XMFLOAT4X4* in_WorldMatrix);

		bool Init() override;
		bool Render() override;
		void Release() override;

	public:
		void SetSize(float& in_X, float& in_Y);
		void SetSize(float in_X, float in_Y);
		void SetSize(float& in_Size);

		Math::Vector2 GetSize();
	private:
		Math::Vector2 Size;
		Math::CRect Rect;
		Sprite sprite;
		XMFLOAT4X4* WorldMatrix;

	private:
		static const UINT VERTEX_NUM;
	};
}

