//*****************************************************************************
//!	@file	Engime/Runtime/Core/vsShader.h
//!	@brief	
//!	@note	頂点シェーダーオブジェクトクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "Data.h"
#include "../Graphics/DirectXGraphics.h"

#include <memory>

#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class vsShader :public Data
{
private:

	ComPtr<ID3D11VertexShader> VertexShader;
	ComPtr<ID3D11InputLayout> VertexLayout;

public:
	bool Load(std::string in_FileName) override;
	bool Set(vsShader& in_vsShader);

public:
	ID3D11VertexShader* GetVertexShader();
	ID3D11InputLayout* GetInputLayout();
};

