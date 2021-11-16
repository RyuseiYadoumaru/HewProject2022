//*****************************************************************************
//!	@file	Engime/Runtime/Core/psShader.cpp
//!	@brief	
//!	@note	�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "psShader.h"
#include "../Graphics/Shader.h"
#include "../Graphics/DirectXGraphics.h"
#include "../Tools/Log.h"
#include "../Tools/FileSystem.h"

//==============================================================================
//!	@fn		Load
//!	@brief�@�s�N�Z���V�F�[�_�[�f�[�^���[�h
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================

bool psShader::Load(std::string in_FileName)
{
	std::string PathName = "Shader/" + in_FileName;
	std::string EntryPoint = FileSystem::GetFileName_NotExt(in_FileName.c_str());
	/****	�f�o�C�X�擾	****/
	ID3D11Device* device = DirectXGraphics::Instance()->GetDevice();

	/****	�f�o�C�X�R���e�L�X�g�擾	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	bool sts = false;

	/****	�s�N�Z���V�F�[�_�[����	****/
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
		Log::LogError("�s�N�Z���V�F�[�_�[�̐����Ɏ��s���܂���");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		Set
//!	@brief	�s�N�Z���V�F�[�_�[�Z�b�g
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool psShader::Set(psShader& in_psShader)
{
	PixelShader = in_psShader.PixelShader;

	if (PixelShader == nullptr)
	{
		Log::LogError("�s�N�Z���V�F�[�_�[�f�[�^������܂���");
		return false;
	}
	return true;
}

//==============================================================================
//!	@fn		GetPixelShader
//!	@brief�@�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�擾
//!	@param	
//!	@retval	�s�N�Z���V�F�[�_�[�I�u�W�F�N�g
//==============================================================================
ID3D11PixelShader* psShader::GetPixelShader()
{
	return PixelShader.Get();
}
