//*****************************************************************************
//!	@file	Engine/Component/Physics/BaxColliuder2D.cpp
//!	@brief	
//!	@note	2D�{�b�N�X�R���C�_
//!	@note	�R���C�_
//!	@author	YoshidaKouki
//*****************************************************************************

#include "BoxCollider2D.h"
#include "../../Runtime/Graphics/DirectXGraphics.h"
#include "../../Data/DataArray.h"
#include "../../Runtime/Graphics/Shader.h"
#include "../../Runtime/Tools/Log.h"

using namespace Math;
using namespace Create;
using namespace GameEngine;

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
GameEngine::BoxCollider2D::BoxCollider2D()
{
	isActive = true;
	isHit = false;
	Offset.Set(0.0f, 0.0f);
	Size.Set(1.0f, 1.0f);//�R���C�_�[�̃T�C�Y�ݒ�
	//�O�،��ǉ�
	isHit_overBlock = false;
	isHit_underBlock = false;
	isHit_rightBlock = false;
	isHit_leftBlock = false;
}

//==============================================================================
//!	@fn		Init
//!	@brief�@������
//!	@param	�I�u�W�F�N�g�T�C�Y
//==============================================================================
void BoxCollider2D::Init(Math::Vector2 in_Size)
{

	/*	�I�u�W�F�N�g�T�C�Y�ۑ�	*/
	m_ObjectSize.Set(in_Size.x, in_Size.y);


	/****	�R���C�_�Đ���	****/
	CreateCollider();

#pragma region Debug
	/****	�f�o�C�X�擾	****/
	ID3D11Device* device = DirectXGraphics::Instance()->GetDevice();

	/****	�f�o�C�X�R���e�L�X�g�擾	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	/****	���_�V�F�[�_�[����	****/
	vertexShader.Set(DataArray::GetvsShader("vs_Debug"));

	/****	�s�N�Z���V�F�[�_�[����	****/
	pixcelShader.Set(DataArray::GetpsShader("ps_Debug"));

	/****	���_���W	****/
	VERTEX_RECT vertex[4] =
	{
		XMFLOAT3(Rect.GetButtomLeft().x, Rect.GetButtomLeft().y, 0.0f),	XMFLOAT4(0.0f,1.0f,0.0f,1.0f),
		XMFLOAT3(Rect.GetTopLeft().x,	 Rect.GetTopLeft().y,	 0.0f),	XMFLOAT4(0.0f,1.0f,0.0f,1.0f),
		XMFLOAT3(Rect.GetButtomRight().x,Rect.GetButtomRight().y,0.0f),	XMFLOAT4(0.0f,1.0f,0.0f,1.0f),
		XMFLOAT3(Rect.GetTopRight().x,	 Rect.GetTopRight().y,	 0.0f),	XMFLOAT4(0.0f,1.0f,0.0f,1.0f)

	};

	/****	���_�o�b�t�@����	****/
	bool sts = false;
	sts = Shader::CreateVertexBuffer
	(
		device,
		sizeof(VERTEX_RECT),
		4,
		vertex,
		&VertexBuffer
	);

	if (sts == false)
	{
		Log::LogError("���_�o�b�t�@�̐����Ɏ��s���܂���");
	}
#pragma endregion �f�o�b�O�p

}

//==============================================================================
//!	@fn		Update
//!	@brief�@�X�V
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool BoxCollider2D::Update()
{
	//�������Ă���I�u�W�F�N�g������������
	m_HitObjectList.clear();
	m_HitObjectIdList.clear();

	/****	�R���C�_�Đ���	****/
	CreateCollider();

	/****	�����蔻��	****/
	HitCheck();

	return true;

}

//==============================================================================
//!	@fn		Debug
//!	@brief	�R���C�_�`�揈��
//!	@param
//==============================================================================
void GameEngine::BoxCollider2D::Debug(float red, float green, float blue)
{
	/****	�f�o�C�X�R���e�L�X�g�擾	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	/****	���_���W	****/
	VERTEX_RECT vertex[4] =
	{
		XMFLOAT3(Rect.GetButtomLeft().x, Rect.GetButtomLeft().y, 0.0f),	XMFLOAT4(red,green,blue,1.0f),
		XMFLOAT3(Rect.GetTopLeft().x,	 Rect.GetTopLeft().y,	 0.0f),	XMFLOAT4(red,green,blue,1.0f),
		XMFLOAT3(Rect.GetButtomRight().x,Rect.GetButtomRight().y,0.0f),	XMFLOAT4(red,green,blue,1.0f),
		XMFLOAT3(Rect.GetTopRight().x,	 Rect.GetTopRight().y,	 0.0f),	XMFLOAT4(red,green,blue,1.0f)
	};

	/****	���_�f�[�^�X�V	****/
	deviceContext->UpdateSubresource
	(
		VertexBuffer,		// �X�V�Ώۂ̃o�b�t�@
		0,						// �C���f�b�N�X(0)
		NULL,					// �X�V�͈�(nullptr)
		vertex,					// ���f�f�[�^
		0,						// �f�[�^��1�s�̃T�C�Y(0)
		0						// 1�[�x�X���C�X�̃T�C�Y(0)
	);

	/****	���_�o�b�t�@�ݒ�	****/
	UINT stride = sizeof(VERTEX_RECT);
	UINT offset = 0;

	bool sts = false;

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
	deviceContext->IASetInputLayout(vertexShader.GetInputLayout());

	deviceContext->VSSetShader(vertexShader.GetVertexShader(), nullptr, 0);		// ���_�V�F�[�_�[���Z�b�g
	deviceContext->PSSetShader(pixcelShader.GetPixelShader(), nullptr, 0);		// �s�N�Z���V�F�[�_�[���Z�b�g

	/****	�`��	****/
	deviceContext->Draw(4, 0);
}

//==============================================================================
//!	@fn		HitCheckBox
//!	@brief�@�����蔻�菈��
//!	@param	����I�u�W�F�N�g
//==============================================================================
void BoxCollider2D::HitCheckBox(BoxCollider2D& in_ObjCollider)
{
	/*	�`�F�b�N�I�u�W�F�N�g�ǉ�	*/
	m_CheckList.push_back(in_ObjCollider);

}

//==============================================================================
//!	@fn		PushBackObject
//!	@brief�@�����߂�����
//!	@param
//==============================================================================
void BoxCollider2D::PushBackObject()
{

	//�����蔻�肪���������Z����Ă���
	//1�P��HitCheck��PushBack�����������Ă�����Ƃ��܂������Ǝv���I�I�I�I�I
	//��肭�������I�I�I�I

	Owner->transform->Position = FixPosition;


}

//==============================================================================
//!	@fn		SetOffset
//!	@brief�@�I�t�Z�b�g�ݒ�
//!	@param	OffsetX, OffsetY
//==============================================================================
void BoxCollider2D::SetOffset(float in_OffsetX, float in_OffsetY)
{
	Offset.x = in_OffsetX;
	Offset.y = in_OffsetY;
}

//==============================================================================
//!	@fn		SetOffset
//!	@brief�@�I�t�Z�b�g�ݒ�
//!	@param	OffsetX, OffsetY
//==============================================================================
void GameEngine::BoxCollider2D::SetSize(float in_SizeX, float in_SizeY)
{
	Size.x = in_SizeX;
	Size.y = in_SizeY;
}

//==============================================================================
//!	@fn		SetisActive
//!	@brief�@�A�N�e�B�u�ݒ�
//!	@param	�t���O
//==============================================================================
void BoxCollider2D::SetisActive(bool in_isActive)
{
	isActive = in_isActive;

}

//==============================================================================
//!	@fn		GetisActive
//!	@brief�@�A�N�e�B�u�擾
//!	@retval	�A�N�e�B�u�t���O
//==============================================================================
bool BoxCollider2D::GetisActive()
{
	return isActive;
}


//==============================================================================
//!	@fn		HitCheck
//!	@brief�@�����蔻��𒲂ׂ�
//!	@param	
//==============================================================================
void GameEngine::BoxCollider2D::HitCheck()
{
	Vector2 PushBack;
	Vector2 Distance;
	Vector2 HalfTotalLength;
	isHit = false;

	isHit_overBlock = false;
	isHit_underBlock = false;
	isHit_rightBlock = false;
	isHit_leftBlock = false;

	//�A�N�e�B�u�o�Ȃ��Ȃ�isHit��false��
	if (isActive == false)
	{
		isHit = false;

		isHit_overBlock = false;
		isHit_underBlock = false;
		isHit_rightBlock = false;
		isHit_leftBlock = false;
		return;
	}

	/*	���W��ۑ����Ă���	*/
	FixPosition = Owner->transform->Position;
	/*	�����蔻��	*/
	for (auto Check : m_CheckList)
	{
		//����̒��S���W�[�����̒��S���W
		Distance.x = fabsf(Check.CenterPos.x - CenterPos.x);
		Distance.y = fabsf(Check.CenterPos.y - CenterPos.y);

		/*	Box�̏c/������	*/
		HalfTotalLength.x = CenterLength.x + Check.CenterLength.x;
		HalfTotalLength.y = CenterLength.y + Check.CenterLength.y;

		/*	�Փ˔���	*/
		if (Distance.x < HalfTotalLength.x &&
			Distance.y < HalfTotalLength.y)
		{
			/*	�Փ�	*/
			isHit = true;

			/*	�����߂��l�v�Z	*/
			//�I�u�W�F�N�g���� - �v���C���[�E��
			float dx1 = (Check.CenterPos.x - Check.CenterLength.x) - (CenterPos.x + CenterLength.x);
			//�I�u�W�F�N�g�E�� - �v���C���[����
			float dx2 = (Check.CenterPos.x + Check.CenterLength.x) - (CenterPos.x - CenterLength.x);
			//�I�u�W�F�N�g��� - �v���C���[����
			float dy1 = (Check.CenterPos.y - Check.CenterLength.y) - (CenterPos.y + CenterLength.y);
			//�I�u�W�F�N�g���� - �v���C���[���
			float dy2 = (Check.CenterPos.y + Check.CenterLength.y) - (CenterPos.y - CenterLength.y);



			PushBack.x = fabsf(dx1) < fabsf(dx2) ? dx1 : dx2;//:?: �������Z�q
			PushBack.y = fabsf(dy1) < fabsf(dy2) ? dy1 : dy2;
			if (fabsf(PushBack.x) < fabsf(PushBack.y))
			{
				PushBack.y = 0.0f;
			}
			else
			{
				PushBack.x = 0.0f;
			}

			/*	�����߂�����	*/
			FixPosition += PushBack;
			CreateCollider(FixPosition);

			if (PushBack.y < 0) {
				//printf("���n!");
				isHit_underBlock = true;
			}
			if (PushBack.y > 0) {
				//printf("���Ԃ���!");
				isHit_overBlock = true;
			}
			if (PushBack.x < 0) {
				//printf("�E!");
				isHit_rightBlock = true;
			}
			if (PushBack.x > 0) {
				//printf("��!");
				isHit_leftBlock = true;
			}

			//printf("\n");

			/*	�q�b�g�I�u�W�F�N�g�i�[	*/
			m_HitObjectList.push_back(Check.Owner->GetName());
			m_HitObjectIdList.push_back(Check.Owner->GetId());
		}
	}
	//�`�F�b�N�I�u�W�F�N�g���g�p�����̂ŏ���������
	m_CheckList.clear();

}

//==============================================================================
//!	@fn		CreateCollider
//!	@brief�@�R���C�_����
//!	@param	
//==============================================================================
void GameEngine::BoxCollider2D::CreateCollider()
{
	//�T�C�Y�̔����̒��������߂�(�X�V)
	CenterLength.x = (m_ObjectSize.x * Owner->transform->Scale.x) / 2.0f;
	CenterLength.y = (m_ObjectSize.y * Owner->transform->Scale.y) / 2.0f;

	/*	�R���C�_�T�C�Y�ݒ�	*/
	CenterLength.x *= Size.x;
	CenterLength.y *= Size.y;

	/*	���S�_���W�X�V	*/
	//�Z���^�[pos��transform��position������ď�ɍX�V�i�X�V�j
	CenterPos.x = Owner->transform->Position.x + (Offset.x * CenterLength.x);
	CenterPos.y = Owner->transform->Position.y + (Offset.y * CenterLength.y);

	//�R���C�_�[�ɒl���ăZ�b�g�ōX�V
	//�i���T�C�Y�A�c�T�C�Y�AOwner.X���W�AOwner.Y���W�j
	Rect.Set(CenterLength.x * 2, CenterLength.y * 2, CenterPos.x, CenterPos.y);
}

//==============================================================================
//!	@fn		CreateCollider
//!	@brief�@�R���C�_����
//!	@param	XY���W
//==============================================================================
void GameEngine::BoxCollider2D::CreateCollider(Math::Vector2& Pos)
{
	//�T�C�Y�̔����̒��������߂�(�X�V)
	CenterLength.x = (m_ObjectSize.x * Owner->transform->Scale.x) / 2.0f;
	CenterLength.y = (m_ObjectSize.y * Owner->transform->Scale.y) / 2.0f;

	/*	�R���C�_�T�C�Y�ݒ�	*/
	CenterLength.x *= Size.x;
	CenterLength.y *= Size.y;

	/*	���S�_���W�X�V	*/
	//�Z���^�[pos��transform��position������ď�ɍX�V�i�X�V�j
	CenterPos.x = Pos.x + (Offset.x * CenterLength.x);
	CenterPos.y = Pos.y + (Offset.y * CenterLength.y);

	//�R���C�_�[�ɒl���ăZ�b�g�ōX�V
	//�i���T�C�Y�A�c�T�C�Y�AOwner.X���W�AOwner.Y���W�j
	Rect.Set(CenterLength.x * 2, CenterLength.y * 2, CenterPos.x, CenterPos.y);
}
