//*****************************************************************************
//!	@file	Engine/Data/DataArray.cpp
//!	@brief	
//!	@note	ゲームで使用するデータをまとめたクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "DataArray.h"
#include "../Runtime/Tools/FileSystem.h"
using namespace GameEngine;
//-----------------------------------------------------------------------------
// スタティック　メンバー
//-----------------------------------------------------------------------------
std::map<std::string, Sprite> DataArray::SpriteData;
std::map<std::string, vsShader> DataArray::vsShaderData;
std::map<std::string, psShader> DataArray::psShaderData;

//==============================================================================
//!	@fn		Instance
//!	@brief	インスタンス取得
//!	@param	
//!	@retval	インスタンス
//==============================================================================
DataArray* DataArray::Instance()
{
	static DataArray Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		Init
//!	@brief	初期化
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool DataArray::Init()
{
	/****	SpriteData	****/
	std::vector<PATH_LIST> ImageList;
	ImageList.push_back(LoadAllImagePath("assets/Sprite/"));
	ImageList.push_back(LoadAllImagePath("assets/Sprite/World1/"));
	ImageList.push_back(LoadAllImagePath("assets/Sprite/World2/"));
	ImageList.push_back(LoadAllImagePath("assets/Sprite/World3/"));
	ImageList.push_back(LoadAllImagePath("assets/Sprite/World4/"));
	ImageList.push_back(LoadAllImagePath("assets/Sprite/World5/"));
	ImageList.push_back(LoadAllImagePath("assets/Sprite/World6/"));
	ImageList.push_back(LoadAllImagePath("assets/Sprite/Block/"));
	ImageList.push_back(LoadAllImagePath("assets/Sprite/Effect/"));
	ImageList.push_back(LoadAllImagePath("assets/Sprite/Select/"));
	ImageList.push_back(LoadAllImagePath("assets/Sprite/Tutorial/"));
	ImageList.push_back(LoadAllImagePath("assets/Sprite/UI/"));
	for (auto ImagePathList : ImageList)
	{
		for (auto Now : ImagePathList)
		{
			std::string SpriteName = FileSystem::GetFileName_NotExt(Now.c_str());
			Sprite sprite;
			sprite.Load(Now);
			SpriteData.insert(std::make_pair(SpriteName, sprite));
		}
	}

	/****	vsShaderData	****/
	std::vector<std::string> vsShaderNameList;

	//vsShaderNameList = { "vs_2DSprite.hlsl", "vs_Debug.hlsl", "vs_Ui.hlsl" };
	vsShaderNameList = { "vs_2DSprite.cso", "vs_Debug.cso", "vs_Ui.cso" };
	for (auto Now : vsShaderNameList)
	{
		std::string vsShaderName = FileSystem::GetFileName_NotExt(Now.c_str());
		vsShader vs;
		vs.Load(Now);
		vsShaderData.insert(std::make_pair(vsShaderName, vs));
	}

	/****	psShaderData	****/
	std::vector<std::string> psShaderNameList;

	//psShaderNameList = { "ps_2DSprite.hlsl", "ps_Debug.hlsl" };
	psShaderNameList = { "ps_2DSprite.cso", "ps_Debug.cso" };
	for (auto Now : psShaderNameList)
	{
		std::string psShaderName = FileSystem::GetFileName_NotExt(Now.c_str());
		psShader ps;
		ps.Load(Now);
		psShaderData.insert(std::make_pair(psShaderName, ps));
	}


	return true;
}

//==============================================================================
//!	@fn		GetSpriteData
//!	@brief	スプライトデータ取得
//!	@param	
//!	@retval	スプライトデータ
//==============================================================================
Sprite& DataArray::GetSpriteData(std::string in_SpriteName)
{
	if (SpriteData[in_SpriteName].GetShaderResourceView() == nullptr)
	{
		return SpriteData["Default"];
	}
	return SpriteData[in_SpriteName];
}

//==============================================================================
//!	@fn		GetvsShader
//!	@brief	頂点シェーダー取得
//!	@param	
//!	@retval	頂点シェーダーデータ
//==============================================================================
vsShader& DataArray::GetvsShader(std::string in_vsShaderName)
{
	return vsShaderData[in_vsShaderName];
}

//==============================================================================
//!	@fn		GetpsShader
//!	@brief	ピクセルシェーダー取得
//!	@param	
//!	@retval	ピクセルシェーダーデータ
//==============================================================================
psShader& DataArray::GetpsShader(std::string in_psShaderName)
{
	return psShaderData[in_psShaderName];
}

//==============================================================================
//!	@fn		LoadAllImagePath
//!	@brief	フォルダパス内の全てのデータを読み込む
//!	@param	フォルダパス
//!	@retval	パスリスト
//==============================================================================
PATH_LIST GameEngine::DataArray::LoadAllImagePath(PATH_NAME in_FilePath)
{
	PATH_LIST ImagePathList;
	ImagePathList = FileSystem::SearchImageFilePath(in_FilePath);
	return ImagePathList;
}
