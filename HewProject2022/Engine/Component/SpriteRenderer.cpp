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
#include "../Create/GameObject.h"


//-----------------------------------------------------------------------------
// �X�^�e�B�b�N�@�����o�[
//-----------------------------------------------------------------------------
const UINT GameEngine::SpriteRenderer::VERTEX_NUM = 4;	//���_��

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
GameEngine::SpriteRenderer::SpriteRenderer() : Renderer()
{
	SpriteName = "Default";
	VertexShaderName = "vs_2DSprite";
	PixcelShaderName = "ps_2DSprite";
	TexCoord.SetSize(1.0f, 1.0f);
	UTiling = 0.0f;
	VTiling = 0.0f;
	TexCoord.SetSize(1.0f, 1.0f);
	TexCoord.SetTiling(UTiling, VTiling);
	Size.Set(0.0f, 0.0f);
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

	/****	�g�����X�t�H�[���擾	****/
	WorldMatrix = Owner->transform->GetAddress();

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
	if (Size.x > 0.0f && Size.y > 0.0f)
	{
		Rect.Set(Size.x, Size.y);
	}
	else
	{
		Rect.Set(sprite.GetSize().x, sprite.GetSize().y);
		Size.Set(sprite.GetSize().x, sprite.GetSize().y);

	}

	/****	���_���W	****/
	VERTEX vertex[VERTEX_NUM] =
	{
		XMFLOAT3(Rect.GetButtomLeft().x, Rect.GetButtomLeft().y, 0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(TexCoord.LeftU, TexCoord.ButtomV),
		XMFLOAT3(Rect.GetTopLeft().x,	 Rect.GetTopLeft().y,	 0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(TexCoord.LeftU, TexCoord.TopV),
		XMFLOAT3(Rect.GetButtomRight().x,Rect.GetButtomRight().y,0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(TexCoord.RightU,TexCoord.ButtomV),
		XMFLOAT3(Rect.GetTopRight().x,	 Rect.GetTopRight().y,	 0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(TexCoord.RightU,TexCoord.TopV)

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
//!	@fn		Update
//!	@brief�@�X�V
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::SpriteRenderer::Update()
{
	/****	���_���W	****/
	VERTEX vertex[VERTEX_NUM] =
	{
		XMFLOAT3(Rect.GetButtomLeft().x, Rect.GetButtomLeft().y, 0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(TexCoord.LeftU, TexCoord.ButtomV),
		XMFLOAT3(Rect.GetTopLeft().x,	 Rect.GetTopLeft().y,	 0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(TexCoord.LeftU, TexCoord.TopV),
		XMFLOAT3(Rect.GetButtomRight().x,Rect.GetButtomRight().y,0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(TexCoord.RightU,TexCoord.ButtomV),
		XMFLOAT3(Rect.GetTopRight().x,	 Rect.GetTopRight().y,	 0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(TexCoord.RightU,TexCoord.TopV)

	};

	/****	���_�f�[�^�X�V	****/

	DirectXGraphics::Instance()->GetDeviceContext()->UpdateSubresource
	(
		VertexBuffer,			// �X�V�Ώۂ̃o�b�t�@
		0,						// �C���f�b�N�X(0)
		NULL,					// �X�V�͈�(nullptr)
		vertex,					// ���f�f�[�^
		0,						// �f�[�^��1�s�̃T�C�Y(0)
		0						// 1�[�x�X���C�X�̃T�C�Y(0)
	);
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
	//DataArray* daa = DataArray::Instance();
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
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::SpriteRenderer::Release()
{
	if (VertexBuffer != nullptr)
	{
		VertexBuffer->Release();
		VertexBuffer = nullptr;
	}
	return true;
}

//==============================================================================
//!	@fn		SetSize
//!	@brief�@�摜�T�C�Y�C�Ӑݒ�
//!	@param	����
//!	@param	�c��
//==============================================================================
void GameEngine::SpriteRenderer::SetSize(float& in_X, float& in_Y)
{
	Size.Set(in_X, in_Y);
}

//==============================================================================
//!	@fn		SetSize
//!	@brief�@�摜�T�C�Y�C�Ӑݒ�
//!	@param	����
//!	@param	�c��
//==============================================================================
void GameEngine::SpriteRenderer::SetSize(float in_X, float in_Y)
{
	Size.Set(in_X, in_Y);
}

//==============================================================================
//!	@fn		SetSize
//!	@brief�@�摜�T�C�Y�C�Ӑݒ�
//!	@param	�����A�c��
//==============================================================================
void GameEngine::SpriteRenderer::SetSize(float& in_Size)
{
	Size.Set(in_Size, in_Size);
}

//==============================================================================
//!	@fn		GetSize
//!	@brief�@�摜�T�C�Y�擾
//!	@param	�����A�c��
//==============================================================================
Math::Vector2 GameEngine::SpriteRenderer::GetSize()
{
	return Size;
}
