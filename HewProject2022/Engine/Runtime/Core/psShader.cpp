//*****************************************************************************
//!	@file	Engime/Runtime/Core/psShader.cpp
//!	@brief	
//!	@note	ピクセルシェーダーオブジェクトクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "psShader.h"
#include "../Graphics/Shader.h"
#include "../Graphics/DirectXGraphics.h"
#include "../Tools/Log.h"
#include "../Tools/FileSystem.h"

//==============================================================================
//!	@fn		Load
//!	@brief　ピクセルシェーダーデータロード
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================

bool psShader::Load(std::string in_FileName)
{
	std::string PathName = "Shader/" + in_FileName;
	std::string EntryPoint = FileSystem::GetFileName_NotExt(in_FileName.c_str());
	/****	デバイス取得	****/
	ID3D11Device* device = DirectXGraphics::Instance()->GetDevice();

	/****	デバイスコンテキスト取得	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	bool sts = false;

	/****	ピクセルシェーダー生成	****/
	sts = Shader::CreatePixelShader
	(
		device,
		PathName.c_str(),
		EntryPoint.c_str(),
		"ps_5_0",
		&PixelShader
	);
	if (sts == false)
	{
		Log::LogError("ピクセルシェーダーの生成に失敗しました");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		Set
//!	@brief	ピクセルシェーダーセット
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool psShader::Set(psShader& in_psShader)
{
	PixelShader = in_psShader.PixelShader;

	if (PixelShader == nullptr)
	{
		Log::LogError("ピクセルシェーダーデータがありません");
		return false;
	}
	return true;
}

//==============================================================================
//!	@fn		GetPixelShader
//!	@brief　ピクセルシェーダーオブジェクト取得
//!	@param	
//!	@retval	ピクセルシェーダーオブジェクト
//==============================================================================
ID3D11PixelShader* psShader::GetPixelShader()
{
	return PixelShader.Get();
}
