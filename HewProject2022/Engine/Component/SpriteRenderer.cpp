//*****************************************************************************
//!	@file	Engine/Component/SpriteRenderer.cpp
//!	@brief	
//!	@note	2D�O���t�B�b�N�X�̃X�v���C�g�������_�����O
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "SpriteRenderer.h"
#include "../Runtime/Graphics/Shader.h"
#include "../Runtime/Tools/Log.h"
#include "../Runtime/Core/TransformMatrix.h"
#include "../Data/DataArray.h"


//-----------------------------------------------------------------------------
// �X�^�e�B�b�N�@�����o�[
//-----------------------------------------------------------------------------
const UINT GameEngine::SpriteRenderer::VERTEX_NUM = 4;	//���_��

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
GameEngine::SpriteRenderer::SpriteRenderer(XMFLOAT4X4* in_WorldMatrix) : Renderer()
{
	SpriteName = "Default";
	VertexShaderName = "vs_2DSprite";
	PixcelShaderName = "ps_2DSprite";
	WorldMatrix = in_WorldMatrix;

}

//==============================================================================
//!	@fn		Init
//!	@brief�@������
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::SpriteRenderer::Init()
{
	bool sts = false;

	/****	�f�o�C�X�擾	****/
	ID3D11Device* device = DirectXGraphics::Instance()->GetDevice();

	/****	�f�o�C�X�R���e�L�X�g�擾	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	/****	���_�V�F�[�_�[����	****/
	vertexShader.Set(DataArray::GetvsShader(VertexShaderName));

	/****	�s�N�Z���V�F�[�_�[����	****/
	pixcelShader.Set(DataArray::GetpsShader(PixcelShaderName));

	/****	SRV����		****/
	sprite.Set(DataArray::GetSpriteData(SpriteName));

	Rect.Set(sprite.GetSize().x, sprite.GetSize().y);

	/****	���_���W	****/
	VERTEX vertex[VERTEX_NUM] =
	{
		XMFLOAT3(Rect.GetButtomLeft().x, Rect.GetButtomLeft().y, 0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(0.0f,1.0f),
		XMFLOAT3(Rect.GetTopLeft().x,	 Rect.GetTopLeft().y,	 0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(0.0f,0.0f),
		XMFLOAT3(Rect.GetButtomRight().x,Rect.GetButtomRight().y,0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(1.0f,1.0f),
		XMFLOAT3(Rect.GetTopRight().x,	 Rect.GetTopRight().y,	 0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(1.0f,0.0f)

	};

	/****	���_�o�b�t�@����	****/
	sts = Shader::CreateVertexBuffer
	(
		device,
		sizeof(VERTEX),
		VERTEX_NUM,
		vertex,
		&VertexBuffer
	);
	if (sts == false)
	{
		Log::LogError("���_�o�b�t�@�̐����Ɏ��s���܂���");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		Render
//!	@brief�@�`��
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::SpriteRenderer::Render()
{
	/****	�f�o�C�X�R���e�L�X�g�擾	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	/****	�s��ϊ�����	****/
	TransformMatrix* TransformMtx = TransformMatrix::Instance();

	/****	���_�o�b�t�@�ݒ�	****/
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;

	bool sts = false;

	/****	���[���h���W�s��Z�b�g	****/
	sts = TransformMtx->SetTransformMatrix(TransformMatrix::TYPE::WORLD, *WorldMatrix);
	if (sts == false)
	{
		Log::LogError("���[���h���W�s��̃Z�b�g�Ɏ��s���܂����B");
		return false;
	}


	/****	���_�o�b�t�@�Z�b�g	****/
	deviceContext->IASetVertexBuffers(
		0,						// �X�^�[�g�X���b�g
		1,						// ���_�o�b�t�@��
		&VertexBuffer,			// ���_�o�b�t�@�̐擪�A�h���X
		&stride,				// �X�g���C�h
		&offset);				// �I�t�Z�b�g


	/****	�g�|���W�[�Z�b�g	****/
	deviceContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP));


	/****	���_���C�A�E�g�Z�b�g	****/
	DataArray* daa = DataArray::Instance();
	deviceContext->IASetInputLayout(vertexShader.GetInputLayout());

	deviceContext->VSSetShader(vertexShader.GetVertexShader(), nullptr, 0);		// ���_�V�F�[�_�[���Z�b�g
	deviceContext->PSSetShader(pixcelShader.GetPixelShader(), nullptr, 0);		// �s�N�Z���V�F�[�_�[���Z�b�g

	/****	SRV�Z�b�g	****/
	deviceContext->PSSetShaderResources(0, 1, sprite.GetShaderResourceView());

	/****	�`��	****/
	deviceContext->Draw(VERTEX_NUM, 0);

	return true;
}

//==============================================================================
//!	@fn		Release
//!	@brief�@�������
//!	@param	
//!	@retval	
//==============================================================================
void GameEngine::SpriteRenderer::Release()
{
	if (VertexBuffer != nullptr)
	{
		VertexBuffer->Release();
		VertexBuffer = nullptr;
	}
}