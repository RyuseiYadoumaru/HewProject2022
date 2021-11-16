//*****************************************************************************
//!	@file	Engine/Runtime/Graphics/Shader.cpp
//!	@brief	
//!	@note	シェーダーの設定
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

#include "Shader.h"
#include "../Tools/FileSystem.h"
#include "../Tools/Log.h"

//==============================================================================
//!	@fn		Instance
//!	@brief	インスタンス取得
//!	@param	
//!	@retval	インスタンス
//==============================================================================
Shader* Shader::Instance()
{
	static Shader Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		CreateVertexShader
//!	@brief　頂点シェーダー生成
//!	@param	デバイス
//!	@param	ファイル名
//!	@param	エントリーポイント名
//!	@param	シェーダーモデル
//!	@param	レイアウト
//!	@param	エレメント数
//!	@param	頂点シェーダー
//!	@param	頂点レイアウト
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Shader::CreateVertexShader(
	ID3D11Device* device,
	const char* FileName,
	LPCSTR EntryPoint,
	LPCSTR SharderModel,
	D3D11_INPUT_ELEMENT_DESC* layout,
	unsigned int NumElements,
	ID3D11VertexShader** VertexShader,
	ID3D11InputLayout** VertexLayout)
{

	HRESULT hr;
	ID3D10Blob* Blob = nullptr;

	void* ShaderObject = nullptr;
	size_t ShaderObjectSize = NULL;

	std::vector<unsigned char> ByteArray;

	/****	シェーダーファイル読み込み	****/
	/*	csoファイル	*/
	if (FileSystem::GetFileExt(FileName) == "cso")
	{
		bool sts = ReadShader(FileName, ByteArray);
		if (sts == false)
		{
			if (Blob) Blob->Release();
			Log::LogError("cso読み込みに失敗しました。");
			return false;
		}

		ShaderObject = ByteArray.data();
		ShaderObjectSize = ByteArray.size();
	}

	/*	hlslファイル	*/
	else if (FileSystem::GetFileExt(FileName) == "hlsl")
	{
		hr = CompileShaderFromFile
		(
			FileName,
			EntryPoint,
			SharderModel,
			&Blob
		);

		if (FAILED(hr))
		{
			if (Blob) Blob->Release();
			Log::LogError("ShaderCompileに失敗しました。");
			return false;
		}
		ShaderObject = Blob->GetBufferPointer();
		ShaderObjectSize = Blob->GetBufferSize();
	}

	/*	Error	*/
	else
	{
		Log::LogError("頂点シェーダーのファイル拡張子が違います");
		return false;
	}

	/****	頂点シェーダー生成	****/
	hr = device->CreateVertexShader(ShaderObject, ShaderObjectSize, nullptr, VertexShader);
	if (FAILED(hr))
	{
		if (Blob) Blob->Release();
		return false;
	}

	/****	頂点データ定義作成	****/
	hr = device->CreateInputLayout(
		layout,
		NumElements,
		ShaderObject,
		ShaderObjectSize,
		VertexLayout);
	if (FAILED(hr))
	{
		Log::LogError("レイアウトの作成に失敗しました");
		Blob->Release();
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		CreatePixcelShader
//!	@brief　ピクセルシェーダー生成
//!	@param	デバイス
//!	@param	ファイル名
//!	@param	エントリーポイント名
//!	@param	シェーダーモデル
//!	@param	ピクセルシェーダー
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Shader::CreatePixelShader(
	ID3D11Device* device,
	const char * FileName,
	LPCSTR EntryPoint,
	LPCSTR SharderModel,
	ID3D11PixelShader** PixelShader)
{
	HRESULT hr;
	ID3D10Blob* Blob = nullptr;

	void* ShaderObject = nullptr;
	size_t ShaderObjectSize = NULL;

	std::vector<unsigned char> ByteArray;

	/****	シェーダーファイル読み込み	****/
	/*	csoファイル	*/
	if (FileSystem::GetFileExt(FileName) == "cso")
	{
		bool sts = ReadShader(FileName, ByteArray);
		if (sts == false)
		{
			if (Blob) Blob->Release();
			Log::LogError("cso読み込みに失敗しました。");
			return false;
		}

		ShaderObject = ByteArray.data();
		ShaderObjectSize = ByteArray.size();
	}

	/*	hlslファイル	*/
	else if (FileSystem::GetFileExt(FileName) == "hlsl")
	{
		hr = CompileShaderFromFile
		(
			FileName,
			EntryPoint,
			SharderModel,
			&Blob
		);

		if (FAILED(hr))
		{
			if (Blob) Blob->Release();
			Log::LogError("ShaderCompileに失敗しました。");
			return false;
		}

		ShaderObject = Blob->GetBufferPointer();
		ShaderObjectSize = Blob->GetBufferSize();
	}

	/*	Error	*/
	else
	{
		Log::LogError("ピクセルシェーダーのファイル拡張子が違います");
		return false;
	}

	/****	ピクセルシェーダー生成	****/
	hr = device->CreatePixelShader(ShaderObject, ShaderObjectSize, nullptr, PixelShader);
	if (FAILED(hr))
	{
		if (Blob) Blob->Release();
		Log::LogError("ピクセルシェーダーの生成に失敗しました");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		CreateVertexBuffer
//!	@brief　頂点バッファ作成
//!	@param	デバイス
//!	@param	1頂点バイト数
//!	@param	頂点数
//!	@param	頂点データ格納メモリ
//!	@param	頂点バッファ
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Shader::CreateVertexBuffer(
	ID3D11Device * device,
	unsigned int stride,
	unsigned int VertexNum,
	void * VertexShader,
	ID3D11Buffer** VertexBuffer)
{
	HRESULT hr;

	/****	頂点バッファ作成	****/
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.ByteWidth = stride * VertexNum;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitDate;
	ZeroMemory(&InitDate, sizeof(InitDate));
	InitDate.pSysMem = VertexShader;

	hr = device->CreateBuffer(&BufferDesc, &InitDate, VertexBuffer);
	if (FAILED(hr))
	{
		Log::LogError("頂点バッファの生成に失敗しました");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		CreateConstanceBuffer
//!	@brief　コンスタントバッファ生成
//!	@brief　UpdateSubresourceで更新
//!	@param	デバイス
//!	@param	データサイズ
//!	@param	バッファ
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Shader::CreateConstanceBuffer(
	ID3D11Device* device,
	unsigned int ByteSize,
	ID3D11Buffer** ConstantBuffer)
{
	/****	コンスタントバッファ生成	****/
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));

	BufferDesc.ByteWidth = ByteSize;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;

	HRESULT hr = device->CreateBuffer(&BufferDesc, nullptr, ConstantBuffer);
	if (FAILED(hr))
	{
		Log::LogError("コンスタントバッファ生成に失敗");
		return false;
	}
	return true;
}

//==============================================================================
//!	@fn		CreateConstanceBufferWrite
//!	@brief　コンスタントバッファ生成
//!	@brief　MAPで更新
//!	@param	デバイス
//!	@param	データサイズ
//!	@param	バッファ
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Shader::CreateConstanceBufferWrite(
	ID3D11Device * device,
	unsigned int ByteSize,
	ID3D11Buffer ** ConstantBuffer)
{
	/****	コンスタントバッファ生成	****/
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));

	BufferDesc.ByteWidth = ByteSize;
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;

	HRESULT hr = device->CreateBuffer(&BufferDesc, nullptr, ConstantBuffer);
	if (FAILED(hr))
	{
		Log::LogError("コンスタントバッファ生成に失敗");
		return false;
	}
	return true;
}

//==============================================================================
//!	@fn		CreateSRVfromWICFile
//!	@brief　SRV生成
//!	@param	テクスチャファイル名
//!	@param	デバイス
//!	@param	デバイスコンテキスト
//!	@param	リソース
//!	@param	シェーダーリソースビュー
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Shader::CreateSRVfromWICFile(
	const char* FileName,
	ID3D11Device* device,
	ID3D11DeviceContext* deviceContext,
	ID3D11Resource** resource,
	ID3D11ShaderResourceView** ShaderResourceView)
{
	HRESULT hr;
	wchar_t wcPath[256];

	/****	ファイルチェック	****/
	if (FileSystem::GetFileExt(FileName) != "png" &&
		FileSystem::GetFileExt(FileName) != "jpg")
	{
		Log::LogError("拡張子が違います。png,jpgにしてください");
		return false;
	}

	setlocale(LC_ALL, "Japanese_Japan.932");
	mbstowcs_s(NULL, wcPath, 256, FileName, 255);

	/****	テクスチャ読み込み	****/
	hr = DirectX::CreateWICTextureFromFile(
		device,
		deviceContext,
		wcPath,
		resource,
		ShaderResourceView
	);
	if (FAILED(hr))
	{
		Log::LogError("テクスチャの読み込みに失敗しました");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		CompileShaderFromFile
//!	@brief　hlslファイルコンパイル
//!	@param	hlslファイル名
//!	@param	エントリーポイント
//!	@param	シェーダーモデル
//!	@param	データバッファ
//!	@retval	HRESULTフラグ
//==============================================================================
HRESULT Shader::CompileShaderFromFile(
	const char * FileName,
	LPCSTR EntryPoint,
	LPCSTR ShaderModel,
	ID3DBlob ** BlobOut)
{

	if (FileSystem::GetFileExt(FileName) != "hlsl")
	{
		Log::LogError("hlslファイルを読み取ってください");
		return S_FALSE;
	}

	HRESULT hr = S_OK;
	DWORD ShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	wchar_t wFileName[256];
	setlocale(LC_ALL, "Japanese_Japan.932");
	mbstowcs_s(NULL, wFileName, 256, FileName, 255);

#if defined(DEBUG) || defined(_DEBUG)

	ShaderFlags |= D3DCOMPILE_DEBUG;

#endif

	ID3DBlob* ErrorBlob = nullptr;

	hr = D3DCompileFromFile(
		wFileName,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		EntryPoint,
		ShaderModel,
		ShaderFlags,
		0,
		BlobOut,
		&ErrorBlob
	);

	if (FAILED(hr))
	{
		if (ErrorBlob != nullptr)
		{
			Log::LogError((char*)ErrorBlob->GetBufferPointer());

		}
		if (ErrorBlob)
		{
			ErrorBlob->Release();
		}

		return hr;
	}

	if (ErrorBlob)
	{
		ErrorBlob->Release();
	}
	return S_OK;
}

//==============================================================================
//!	@fn		ReadShader
//!	@brief　シェーダー読み込み
//!	@param	csoファイル名
//!	@param	シェーダーデータ格納コンテナ
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Shader::ReadShader(const char * csoName, std::vector<unsigned char>& ByteArray)
{
	FILE* fp;
	ByteArray.clear();

	int ret = fopen_s(&fp, csoName, "rb");
	/****	ファイル確認	****/
	if (ret != 0)
	{
		Log::LogError("シェーダー読み込み失敗");
		return false;
	}

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	ByteArray.resize(size);
	fseek(fp, 0, SEEK_SET);

	fread(ByteArray.data(), ByteArray.size(), 1, fp);
	fclose(fp);

	return true;
}
