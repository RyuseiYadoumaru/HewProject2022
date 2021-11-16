//*****************************************************************************
//!	@file	Engime/Runtime/Core/Sprite.cpp
//!	@brief	
//!	@note	スプライトクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Sprite.h"
#include "../Graphics/Shader.h"
#include "../Tools/Log.h"
#include "../Tools/FileSystem.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
Sprite::Sprite()
{
	ShaderResourceView = nullptr;
	TexResource = nullptr;
}

//==============================================================================
//!	@fn		Load
//!	@brief　スプライトデータロード
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Sprite::Load(std::string in_FilePath)
{
	/****	デバイス取得	****/
	ID3D11Device* device = DirectXGraphics::Instance()->GetDevice();

	/****	デバイスコンテキスト取得	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	bool sts = false;

	/****	SRV生成		****/
	sts = Shader::CreateSRVfromWICFile
	(
		in_FilePath.c_str(),
		device,
		deviceContext,
		TexResource.GetAddressOf(),
		ShaderResourceView.GetAddressOf()
	);
	if (sts == false)
	{
		Log::LogError("SRVの生成に失敗しました");
		return false;
	}

	/****	テクスチャサイズ生成	****/
	Size = FileSystem::GetImageSize(in_FilePath);

	return true;
}

//==============================================================================
//!	@fn		Set
//!	@brief　スプライトデータセット
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Sprite::Set(Sprite& in_Sprite)
{
	ShaderResourceView = in_Sprite.ShaderResourceView;
	TexResource = in_Sprite.TexResource;
	Size = in_Sprite.Size;
	if (ShaderResourceView == nullptr)
	{
		Log::LogError("スプライトデータがありません");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		GetShaderResourceView
//!	@brief　シェーダーリソースビュー取得
//!	@param	
//!	@retval	シェーダーリソースビュー
//==============================================================================
ID3D11ShaderResourceView** Sprite::GetShaderResourceView()
{
	return ShaderResourceView.GetAddressOf();
}

//==============================================================================
//!	@fn		GetSize
//!	@brief　サイズ取得
//!	@param	
//!	@retval	サイズ
//==============================================================================
Math::Vector2 Sprite::GetSize() const
{
	return Size;
}
