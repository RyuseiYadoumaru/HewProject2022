//*****************************************************************************
//!	@file	Engime/Runtime/Core/vsShader.cpp
//!	@brief	
//!	@note	���_�V�F�[�_�[�I�u�W�F�N�g�N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "vsShader.h"
#include "../Graphics/Shader.h"
#include "../Graphics/DirectXGraphics.h"
#include "../Tools/Log.h"
#include "../Tools/FileSystem.h"

//==============================================================================
//!	@fn		Load
//!	@brief�@���_�V�F�[�_�[�f�[�^���[�h
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool vsShader::Load(std::string in_FileName)
{
	std::string PathName = "Shader/" + in_FileName;
	std::string EntryPoint = FileSystem::GetFileName_NotExt(in_FileName.c_str());
	/****	�f�o�C�X�擾	****/
	ID3D11Device* device = DirectXGraphics::Instance()->GetDevice();

	/****	�f�o�C�X�R���e�L�X�g�擾	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	bool sts = false;

	/****	���_�f�[�^��`	****/
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	UINT NumElements = ARRAYSIZE(layout);	//�G�������g��

	/****	���_�V�F�[�_�[����	****/
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
		Log::LogError("���_�V�F�[�_�[�̐����Ɏ��s���܂���");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		Set
//!	@brief�@���_�V�F�[�_�[�Z�b�g
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool vsShader::Set(vsShader& in_vsShader)
{
	VertexShader = in_vsShader.VertexShader;
	VertexLayout = in_vsShader.VertexLayout;

	if (VertexShader == nullptr || VertexLayout == nullptr)
	{
		Log::LogError("���_�V�F�[�_�[�f�[�^������܂���");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		GetVertexShader
//!	@brief�@���_�V�F�[�_�[�I�u�W�F�N�g�擾
//!	@param	
//!	@retval	���_�V�F�[�_�[�I�u�W�F�N�g
//==============================================================================
ID3D11VertexShader* vsShader::GetVertexShader()
{
	return VertexShader.Get();
}

//==============================================================================
//!	@fn		GetInputLayout
//!	@brief�@���C�A�E�g�擾
//!	@param	
//!	@retval	���C�A�E�g
//==============================================================================
ID3D11InputLayout* vsShader::GetInputLayout()
{
	return VertexLayout.Get();
}
