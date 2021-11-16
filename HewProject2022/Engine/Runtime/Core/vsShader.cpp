//*****************************************************************************
//!	@file	Engime/Runtime/Core/vsShader.cpp
//!	@brief	
//!	@note	頂点シェーダーオブジェクトクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "vsShader.h"
#include "../Graphics/Shader.h"
#include "../Graphics/DirectXGraphics.h"
#include "../Tools/Log.h"
#include "../Tools/FileSystem.h"

//==============================================================================
//!	@fn		Load
//!	@brief　頂点シェーダーデータロード
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool vsShader::Load(std::string in_FileName)
{
	std::string PathName = "Shader/" + in_FileName;
	std::string EntryPoint = FileSystem::GetFileName_NotExt(in_FileName.c_str());
	/****	デバイス取得	****/
	ID3D11Device* device = DirectXGraphics::Instance()->GetDevice();

	/****	デバイスコンテキスト取得	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	bool sts = false;

	/****	頂点データ定義	****/
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	UINT NumElements = ARRAYSIZE(layout);	//エレメント数

	/****	頂点シェーダー生成	****/
	sts = Shader::CreateVertexShader
	(
		device,
		PathName.c_str(),
		EntryPoint.c_str(),
		"vs_5_0",
		layout,
		NumElements,
		VertexShader.GetAddressOf(),
		VertexLayout.GetAddressOf()
	);
	if (sts == false)
	{
		Log::LogError("頂点シェーダーの生成に失敗しました");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		Set
//!	@brief　頂点シェーダーセット
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool vsShader::Set(vsShader& in_vsShader)
{
	VertexShader = in_vsShader.VertexShader;
	VertexLayout = in_vsShader.VertexLayout;

	if (VertexShader == nullptr || VertexLayout == nullptr)
	{
		Log::LogError("頂点シェーダーデータがありません");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		GetVertexShader
//!	@brief　頂点シェーダーオブジェクト取得
//!	@param	
//!	@retval	頂点シェーダーオブジェクト
//==============================================================================
ID3D11VertexShader* vsShader::GetVertexShader()
{
	return VertexShader.Get();
}

//==============================================================================
//!	@fn		GetInputLayout
//!	@brief　レイアウト取得
//!	@param	
//!	@retval	レイアウト
//==============================================================================
ID3D11InputLayout* vsShader::GetInputLayout()
{
	return VertexLayout.Get();
}
