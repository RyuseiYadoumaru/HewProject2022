//*****************************************************************************
//!	@file	Engine/Runtime/Graphics/Shader.cpp
//!	@brief	
//!	@note	�V�F�[�_�[�̐ݒ�
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

#include "Shader.h"
#include "../Tools/FileSystem.h"
#include "../Tools/Log.h"

//==============================================================================
//!	@fn		Instance
//!	@brief	�C���X�^���X�擾
//!	@param	
//!	@retval	�C���X�^���X
//==============================================================================
Shader* Shader::Instance()
{
	static Shader Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		CreateVertexShader
//!	@brief�@���_�V�F�[�_�[����
//!	@param	�f�o�C�X
//!	@param	�t�@�C����
//!	@param	�G���g���[�|�C���g��
//!	@param	�V�F�[�_�[���f��
//!	@param	���C�A�E�g
//!	@param	�G�������g��
//!	@param	���_�V�F�[�_�[
//!	@param	���_���C�A�E�g
//!	@retval	true:����I���@false:�ُ�I��
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

	/****	�V�F�[�_�[�t�@�C���ǂݍ���	****/
	/*	cso�t�@�C��	*/
	if (FileSystem::GetFileExt(FileName) == "cso")
	{
		bool sts = ReadShader(FileName, ByteArray);
		if (sts == false)
		{
			if (Blob) Blob->Release();
			Log::LogError("cso�ǂݍ��݂Ɏ��s���܂����B");
			return false;
		}

		ShaderObject = ByteArray.data();
		ShaderObjectSize = ByteArray.size();
	}

	/*	hlsl�t�@�C��	*/
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
			Log::LogError("ShaderCompile�Ɏ��s���܂����B");
			return false;
		}
		ShaderObject = Blob->GetBufferPointer();
		ShaderObjectSize = Blob->GetBufferSize();
	}

	/*	Error	*/
	else
	{
		Log::LogError("���_�V�F�[�_�[�̃t�@�C���g���q���Ⴂ�܂�");
		return false;
	}

	/****	���_�V�F�[�_�[����	****/
	hr = device->CreateVertexShader(ShaderObject, ShaderObjectSize, nullptr, VertexShader);
	if (FAILED(hr))
	{
		if (Blob) Blob->Release();
		return false;
	}

	/****	���_�f�[�^��`�쐬	****/
	hr = device->CreateInputLayout(
		layout,
		NumElements,
		ShaderObject,
		ShaderObjectSize,
		VertexLayout);
	if (FAILED(hr))
	{
		Log::LogError("���C�A�E�g�̍쐬�Ɏ��s���܂���");
		Blob->Release();
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		CreatePixcelShader
//!	@brief�@�s�N�Z���V�F�[�_�[����
//!	@param	�f�o�C�X
//!	@param	�t�@�C����
//!	@param	�G���g���[�|�C���g��
//!	@param	�V�F�[�_�[���f��
//!	@param	�s�N�Z���V�F�[�_�[
//!	@retval	true:����I���@false:�ُ�I��
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

	/****	�V�F�[�_�[�t�@�C���ǂݍ���	****/
	/*	cso�t�@�C��	*/
	if (FileSystem::GetFileExt(FileName) == "cso")
	{
		bool sts = ReadShader(FileName, ByteArray);
		if (sts == false)
		{
			if (Blob) Blob->Release();
			Log::LogError("cso�ǂݍ��݂Ɏ��s���܂����B");
			return false;
		}

		ShaderObject = ByteArray.data();
		ShaderObjectSize = ByteArray.size();
	}

	/*	hlsl�t�@�C��	*/
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
			Log::LogError("ShaderCompile�Ɏ��s���܂����B");
			return false;
		}

		ShaderObject = Blob->GetBufferPointer();
		ShaderObjectSize = Blob->GetBufferSize();
	}

	/*	Error	*/
	else
	{
		Log::LogError("�s�N�Z���V�F�[�_�[�̃t�@�C���g���q���Ⴂ�܂�");
		return false;
	}

	/****	�s�N�Z���V�F�[�_�[����	****/
	hr = device->CreatePixelShader(ShaderObject, ShaderObjectSize, nullptr, PixelShader);
	if (FAILED(hr))
	{
		if (Blob) Blob->Release();
		Log::LogError("�s�N�Z���V�F�[�_�[�̐����Ɏ��s���܂���");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		CreateVertexBuffer
//!	@brief�@���_�o�b�t�@�쐬
//!	@param	�f�o�C�X
//!	@param	1���_�o�C�g��
//!	@param	���_��
//!	@param	���_�f�[�^�i�[������
//!	@param	���_�o�b�t�@
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Shader::CreateVertexBuffer(
	ID3D11Device * device,
	unsigned int stride,
	unsigned int VertexNum,
	void * VertexShader,
	ID3D11Buffer** VertexBuffer)
{
	HRESULT hr;

	/****	���_�o�b�t�@�쐬	****/
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
		Log::LogError("���_�o�b�t�@�̐����Ɏ��s���܂���");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		CreateConstanceBuffer
//!	@brief�@�R���X�^���g�o�b�t�@����
//!	@brief�@UpdateSubresource�ōX�V
//!	@param	�f�o�C�X
//!	@param	�f�[�^�T�C�Y
//!	@param	�o�b�t�@
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Shader::CreateConstanceBuffer(
	ID3D11Device* device,
	unsigned int ByteSize,
	ID3D11Buffer** ConstantBuffer)
{
	/****	�R���X�^���g�o�b�t�@����	****/
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
		Log::LogError("�R���X�^���g�o�b�t�@�����Ɏ��s");
		return false;
	}
	return true;
}

//==============================================================================
//!	@fn		CreateConstanceBufferWrite
//!	@brief�@�R���X�^���g�o�b�t�@����
//!	@brief�@MAP�ōX�V
//!	@param	�f�o�C�X
//!	@param	�f�[�^�T�C�Y
//!	@param	�o�b�t�@
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Shader::CreateConstanceBufferWrite(
	ID3D11Device * device,
	unsigned int ByteSize,
	ID3D11Buffer ** ConstantBuffer)
{
	/****	�R���X�^���g�o�b�t�@����	****/
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
		Log::LogError("�R���X�^���g�o�b�t�@�����Ɏ��s");
		return false;
	}
	return true;
}

//==============================================================================
//!	@fn		CreateSRVfromWICFile
//!	@brief�@SRV����
//!	@param	�e�N�X�`���t�@�C����
//!	@param	�f�o�C�X
//!	@param	�f�o�C�X�R���e�L�X�g
//!	@param	���\�[�X
//!	@param	�V�F�[�_�[���\�[�X�r���[
//!	@retval	true:����I���@false:�ُ�I��
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

	/****	�t�@�C���`�F�b�N	****/
	if (FileSystem::GetFileExt(FileName) != "png" &&
		FileSystem::GetFileExt(FileName) != "jpg")
	{
		Log::LogError("�g���q���Ⴂ�܂��Bpng,jpg�ɂ��Ă�������");
		return false;
	}

	setlocale(LC_ALL, "Japanese_Japan.932");
	mbstowcs_s(NULL, wcPath, 256, FileName, 255);

	/****	�e�N�X�`���ǂݍ���	****/
	hr = DirectX::CreateWICTextureFromFile(
		device,
		deviceContext,
		wcPath,
		resource,
		ShaderResourceView
	);
	if (FAILED(hr))
	{
		Log::LogError("�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		CompileShaderFromFile
//!	@brief�@hlsl�t�@�C���R���p�C��
//!	@param	hlsl�t�@�C����
//!	@param	�G���g���[�|�C���g
//!	@param	�V�F�[�_�[���f��
//!	@param	�f�[�^�o�b�t�@
//!	@retval	HRESULT�t���O
//==============================================================================
HRESULT Shader::CompileShaderFromFile(
	const char * FileName,
	LPCSTR EntryPoint,
	LPCSTR ShaderModel,
	ID3DBlob ** BlobOut)
{

	if (FileSystem::GetFileExt(FileName) != "hlsl")
	{
		Log::LogError("hlsl�t�@�C����ǂݎ���Ă�������");
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
//!	@brief�@�V�F�[�_�[�ǂݍ���
//!	@param	cso�t�@�C����
//!	@param	�V�F�[�_�[�f�[�^�i�[�R���e�i
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Shader::ReadShader(const char * csoName, std::vector<unsigned char>& ByteArray)
{
	FILE* fp;
	ByteArray.clear();

	int ret = fopen_s(&fp, csoName, "rb");
	/****	�t�@�C���m�F	****/
	if (ret != 0)
	{
		Log::LogError("�V�F�[�_�[�ǂݍ��ݎ��s");
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
