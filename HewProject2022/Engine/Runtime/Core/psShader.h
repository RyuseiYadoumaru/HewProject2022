//*****************************************************************************
//!	@file	Engime/Runtime/Core/psShader.h
//!	@brief	
//!	@note	ピクセルシェーダーオブジェクトクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include "Data.h"
#include "../Graphics/DirectXGraphics.h"

#include <memory>

#include <d3d11.h>
#include <wrl/client.h>
class psShader : public Data
{
private:
	ComPtr<ID3D11PixelShader> PixelShader;

public:
	bool Load(std::string in_FileName) override;
	bool Set(psShader& in_psShader);

public:
	ID3D11PixelShader* GetPixelShader();
};

