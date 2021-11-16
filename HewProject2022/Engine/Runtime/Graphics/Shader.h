//*****************************************************************************
//!	@file	Runtime/Shader.h
//!	@brief	
//!	@note	シェーダーの設定
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include	<d3dcompiler.h>
#include	<directxmath.h>
#include	<locale.h>
#include	<d3d11.h>
#include	<DirectXMath.h>
#include	<wrl/client.h>

#include	<memory>
#include	<string>
#include	<vector>

#include	"../../../directxtex/include/WICTextureLoader.h"
#include "../../../directxtex/include/DDSTextureLoader.h"
#include	"../../../directxtex/include/DirectXTex.h"

using Microsoft::WRL::ComPtr;

class Shader
{
private:

	ComPtr<ID3D11Buffer> ConstantBuffer;

public:

	static Shader* Instance();

	static bool CreateVertexShader
	(
		ID3D11Device* device,
		const char* FileName,
		LPCSTR EntryPoint,
		LPCSTR SharderModel,
		D3D11_INPUT_ELEMENT_DESC* layout,
		unsigned int NumElements,
		ID3D11VertexShader** VertexShader,
		ID3D11InputLayout** VertexLayout
	);

	static bool CreatePixelShader
	(
		ID3D11Device* device,
		const char* FileName,
		LPCSTR EntryPoint,
		LPCSTR SharderModel,
		ID3D11PixelShader** PixelShader
	);

	static bool CreateVertexBuffer
	(
		ID3D11Device* device,
		unsigned int stride,
		unsigned int VertexNum,
		void* VertexShader,
		ID3D11Buffer** VertexBuffer
	);

	static bool CreateConstanceBuffer
	(
		ID3D11Device* device,
		unsigned int ByteSize,
		ID3D11Buffer** ConstantBuffer
	);

	static bool CreateConstanceBufferWrite
	(
		ID3D11Device* device,
		unsigned int ByteSize,
		ID3D11Buffer** ConstantBuffer
	);

	static bool CreateSRVfromWICFile
	(
		const char* FileName,
		ID3D11Device* device,
		ID3D11DeviceContext* deviceContext,
		ID3D11Resource** resource,
		ID3D11ShaderResourceView** ShaderResourceView
	);

	static HRESULT CompileShaderFromFile
	(
		const char* FileName,
		LPCSTR EntryPoint,
		LPCSTR ShaderModel,
		ID3DBlob** BlobOut
	);

private:

	static bool ReadShader(const char* csoName, std::vector<unsigned char>& ByteArray);
};

