//*****************************************************************************
//!	@file	Engime/Runtime/Core/Sprite.cpp
//!	@brief	
//!	@note	�X�v���C�g�N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Sprite.h"
#include "../Graphics/Shader.h"
#include "../Tools/Log.h"
#include "../Tools/FileSystem.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
Sprite::Sprite()
{
	ShaderResourceView = nullptr;
	TexResource = nullptr;
}

//==============================================================================
//!	@fn		Load
//!	@brief�@�X�v���C�g�f�[�^���[�h
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Sprite::Load(std::string in_FilePath)
{
	/****	�f�o�C�X�擾	****/
	ID3D11Device* device = DirectXGraphics::Instance()->GetDevice();

	/****	�f�o�C�X�R���e�L�X�g�擾	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	bool sts = false;

	/****	SRV����		****/
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
		Log::LogError("SRV�̐����Ɏ��s���܂���");
		return false;
	}

	/****	�e�N�X�`���T�C�Y����	****/
	Size = FileSystem::GetImageSize(in_FilePath);

	return true;
}

//==============================================================================
//!	@fn		Set
//!	@brief�@�X�v���C�g�f�[�^�Z�b�g
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Sprite::Set(Sprite& in_Sprite)
{
	ShaderResourceView = in_Sprite.ShaderResourceView;
	TexResource = in_Sprite.TexResource;
	Size = in_Sprite.Size;
	if (ShaderResourceView == nullptr)
	{
		Log::LogError("�X�v���C�g�f�[�^������܂���");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		GetShaderResourceView
//!	@brief�@�V�F�[�_�[���\�[�X�r���[�擾
//!	@param	
//!	@retval	�V�F�[�_�[���\�[�X�r���[
//==============================================================================
ID3D11ShaderResourceView** Sprite::GetShaderResourceView()
{
	return ShaderResourceView.GetAddressOf();
}

//==============================================================================
//!	@fn		GetSize
//!	@brief�@�T�C�Y�擾
//!	@param	
//!	@retval	�T�C�Y
//==============================================================================
Math::Vector2 Sprite::GetSize() const
{
	return Size;
}
