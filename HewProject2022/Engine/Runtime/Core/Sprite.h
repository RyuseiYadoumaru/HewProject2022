//*****************************************************************************
//!	@file	Engime/Runtime/Core/Sprite.h
//!	@brief	
//!	@note	スプライトクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "Data.h"

#include "../Graphics/DirectXGraphics.h"
#include "../../Math/Vector2.h"

#include <DirectXMath.h>
#include <memory>

#include <d3d11.h>
#include	<wrl/client.h>

using Microsoft::WRL::ComPtr;

class Sprite : public Data
{
private:

	ComPtr<ID3D11ShaderResourceView> ShaderResourceView;
	ComPtr<ID3D11Resource> TexResource;

	Math::Vector2 Size;

public:
	Sprite();
	bool Load(std::string in_FilePath) override;
	bool Set(Sprite& in_Sprite);

public:
	ID3D11ShaderResourceView** GetShaderResourceView();
	Math::Vector2 GetSize() const;
};

