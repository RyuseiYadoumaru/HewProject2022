//*****************************************************************************
//!	@file	Engine/Data/DataArray.cpp
//!	@brief	
//!	@note	�Q�[���Ŏg�p����f�[�^���܂Ƃ߂��N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "DataArray.h"
#include "../Runtime/Tools/FileSystem.h"
using namespace GameEngine;
//-----------------------------------------------------------------------------
// �X�^�e�B�b�N�@�����o�[
//-----------------------------------------------------------------------------
std::map<std::string, Sprite> DataArray::SpriteData;
std::map<std::string, vsShader> DataArray::vsShaderData;
std::map<std::string, psShader> DataArray::psShaderData;

//==============================================================================
//!	@fn		Instance
//!	@brief	�C���X�^���X�擾
//!	@param	
//!	@retval	�C���X�^���X
//==============================================================================
DataArray* DataArray::Instance()
{
	static DataArray Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		Init
//!	@brief	������
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool DataArray::Init()
{
	/****	SpriteData	****/
	std::vector<std::string> ImagePathList;
	ImagePathList = FileSystem::SearchImageFilePath("assets/Sprite/");
	for (auto Now : ImagePathList)
	{
		std::string SpriteName = FileSystem::GetFileName_NotExt(Now.c_str());
		Sprite sprite;
		sprite.Load(Now);
		SpriteData.insert(std::make_pair(SpriteName, sprite));
	}

	/****	vsShaderData	****/
	std::vector<std::string> vsShaderNameList;

	vsShaderNameList = { "vs_2DSprite.hlsl", "vs_Debug.hlsl", "vs_Ui.hlsl" };
	for (auto Now : vsShaderNameList)
	{
		std::string vsShaderName = FileSystem::GetFileName_NotExt(Now.c_str());
		vsShader vs;
		vs.Load(Now);
		vsShaderData.insert(std::make_pair(vsShaderName, vs));
	}

	/****	psShaderData	****/
	std::vector<std::string> psShaderNameList;

	psShaderNameList = { "ps_2DSprite.hlsl", "ps_Debug.hlsl" };
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
//!	@brief	�X�v���C�g�f�[�^�擾
//!	@param	
//!	@retval	�X�v���C�g�f�[�^
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
//!	@brief	���_�V�F�[�_�[�擾
//!	@param	
//!	@retval	���_�V�F�[�_�[�f�[�^
//==============================================================================
vsShader& DataArray::GetvsShader(std::string in_vsShaderName)
{
	return vsShaderData[in_vsShaderName];
}

psShader& DataArray::GetpsShader(std::string in_psShaderName)
{
	return psShaderData[in_psShaderName];
}
