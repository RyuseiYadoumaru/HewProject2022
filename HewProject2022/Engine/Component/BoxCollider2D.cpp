#include "BoxCollider2D.h"

using namespace Math;
using namespace Create;
using namespace GameEngine;

//���̊֐����g���Ǝl�p�`����
void BoxCollider2D::Init(Create::GameObject* in_Owner, Math::Vector2 in_Size)
{
	/*	�I�[�i�[�ݒ�	*/
	Owner = in_Owner;

	isActive = true;

	isHit = false;

	//isPush = false;

	Offset = { 0, 0 };			//�I�t�Z�b�g�f�t�H���g�l
	CenterLength = { 0,0 };

	//�T�C�Y�̔����̒��������߂�(�����l)
	CenterLength.x = in_Size.x / 2;
	CenterLength.y = in_Size.y / 2;

	//�Z���^�[pos��transform��position������ď�ɍX�V�i�����l�j
	CenterPos.x = Owner->transform.Position.x;
	CenterPos.y = Owner->transform.Position.y;


	//size��owner���Ɏ����ɂ��� 
	//�l�p�`����
	//m_CRect.Set(in_Size.x, in_Size.y, CenterPos.x, CenterPos.y);

}

void BoxCollider2D::Update(Create::GameObject *in_Owner, Vector2 in_Size)
{
	//
	Owner = in_Owner;

	//�T�C�Y�̔����̒��������߂�(�X�V)
	CenterLength.x = in_Size.x / 2;
	CenterLength.y = in_Size.y / 2;

	/*	���S�_���W�X�V	*/
	//�Z���^�[pos��transform��position������ď�ɍX�V�i�X�V�j
	CenterPos.x = Owner->transform.Position.x;
	CenterPos.y = Owner->transform.Position.y;

	/*	���S�_�����X�V	*/
	//CenterLength.x = in_Size.x * Owner->transform.Scale.x;
	//CenterLength.y = in_Size.y * Owner->transform.Scale.y;

	//CenterLength =
	//{
	//	fabsf(CenterPos.x - (Vertex.GetTopLeft().x + CenterLength.x)),
	//	fabsf(CenterPos.y - (Vertex.GetTopLeft().y + CenterLength.y)),
	//};


	/*	���S�_�����ݒ�	*/
	/*CenterLength.x *= Size.x;
	CenterLength.y *= Size.y;*/

	/*	���S�_���W�ݒ�	*/
	//CenterPos.x += Offset.x * CenterLength.x;
	//CenterPos.y += Offset.y * CenterLength.y;


	//�R���C�_�[�ɒl���ăZ�b�g�ōX�V
	//�i���T�C�Y�A�c�T�C�Y�AOwner.X���W�AOwner.Y���W�j
	m_CRect.Set(CenterLength.x * 2, CenterLength.y * 2, Owner->transform.Position.x, Owner->transform.Position.y);

	//
	//	/*	Rect�X�V	*/
	//	Vector2 TopLeft;
	//	Vector2 TopRight;
	//	Vector2 ButtomLeft;
	//	Vector2 ButtomRight;
	//
	//#pragma region UpdateRect
	//	//�e4���_�̍X�V
	//
	//	TopLeft.x = Owner->transform.Position.x + Offset.x;
	//	TopLeft.y = Owner->transform.Position.y + Offset.y;
	//
	//
	//	ButtomLeft.x = Owner->transform.Position.x + Offset.x;
	//	ButtomLeft.y = Owner->transform.Position.y + (CenterLength.y * 2) + Offset.y;
	//
	//
	//	TopRight.x = Owner->transform.Position.x + (CenterLength.x * 2) + Offset.x;
	//	TopRight.y = Owner->transform.Position.y + Offset.y;
	//
	//	ButtomRight.x = Owner->transform.Position.x + (CenterLength.x * 2) + Offset.x;
	//	ButtomRight.y = Owner->transform.Position.y + (CenterLength.y * 2) + Offset.y;
	//

	//#pragma endregion Rect�̒l���X�V
		//�������܂��ł��ĂȂ�
		//���Ȃ炱������Ȃ��񂶂�ˁH

		/*Vertex.SetTopLeft(TopLeft);
		Vertex.SetButtomLeft(ButtomLeft);
		Vertex.SetTopRight(TopRight);
		Vertex.SetButtomRight(ButtomRight);*/

}

void BoxCollider2D::SetOffset(float in_OffsetX, float in_OffsetY)
{
	Offset.x = in_OffsetX;
	Offset.y = in_OffsetY;
}

/****	�{�b�N�X�R���C�_�����蔻��	****/
void BoxCollider2D::HitCheckBox(BoxCollider2D &in_ObjCollider)
{
	Vector2 Distance;
	Vector2 HalfTotalLength;

	//�A�N�e�B�u�o�Ȃ��Ȃ�isHit��false��
	if (isActive == false || in_ObjCollider.isActive == false)
	{
		isHit = false;
		return;
	}

	/*	�����蔻��	*/
	//����̒��S���W�[�����̒��S���W
	Distance.x = fabsf(in_ObjCollider.CenterPos.x - CenterPos.x);
	Distance.y = fabsf(in_ObjCollider.CenterPos.y - CenterPos.y);

	/*	Box�̏c/������	*/
	HalfTotalLength.x = CenterLength.x + in_ObjCollider.CenterLength.x;
	HalfTotalLength.y = CenterLength.y + in_ObjCollider.CenterLength.y;

	/*	�Փ˔���	*/
	if (Distance.x < HalfTotalLength.x &&
		Distance.y < HalfTotalLength.y)
	{
		isHit = true;//�Փ�
		keep_position.x = Owner->transform.Position.x;
		keep_position.y = Owner->transform.Position.y;

	}
	else
	{
		isHit = false;//��Փ�
		return;
	}

	/*	�����߂��l�v�Z	*/

	//�I�u�W�F�N�g���� - �v���C���[�E��
	float dx1 = (in_ObjCollider.CenterPos.x - in_ObjCollider.CenterLength.x) - (CenterPos.x + CenterLength.x);
	//�I�u�W�F�N�g�E�� - �v���C���[����
	float dx2 = (in_ObjCollider.CenterPos.x + in_ObjCollider.CenterLength.x) - (CenterPos.x - CenterLength.x);
	//�I�u�W�F�N�g��� - �v���C���[����
	float dy1 = (in_ObjCollider.CenterPos.y - in_ObjCollider.CenterLength.y) - (CenterPos.y + CenterLength.y);
	//�I�u�W�F�N�g���� - �v���C���[���
	float dy2 = (in_ObjCollider.CenterPos.y + in_ObjCollider.CenterLength.y) - (CenterPos.y - CenterLength.y);

	PushBack.x = fabsf(dx1) < fabsf(dx2) ? dx1 : dx2;
	PushBack.y = fabsf(dy1) < fabsf(dy2) ? dy1 : dy2;

	if (fabsf(PushBack.x) < fabsf(PushBack.y))
	{
		PushBack.y = 0.0f;
	}
	else
	{
		PushBack.x = 0.0f;
	}

	//PushBackObject(Owner);

	//if (PushBack.x > 0 && PushBack.y > 0) {

	//	isPush = true;
	//	//PushBackObject(Owner);
	//}
	//else 
	//{
	//	return;
	//}

	//�����܂��ł��ĂȂ�->�������ł���
	//HitObject = in_ObjCollider.Owner->GetName();


}

void BoxCollider2D::SetisActive(bool in_isActive)
{
	isActive = in_isActive;

}

bool BoxCollider2D::GetisActive()
{
	return isActive;
}

void BoxCollider2D::SetisHit(bool in_isHit)
{
	isHit = in_isHit;
}

bool BoxCollider2D::GetisHit()
{
	return isHit;
}

//void GameEngine::BoxCollider2D::SetisPush(bool in_isPush)
//{
//	isPush = in_isPush;
//}
//
//bool GameEngine::BoxCollider2D::GetisPush()
//{
//	return isPush;
//}

void BoxCollider2D::PushBackObject(Create::GameObject *in_Owner)
{

	Owner->transform.Position.x += PushBack.x;
	Owner->transform.Position.y += PushBack.y;
	PushBack.x = 0;
	PushBack.y = 0;
	//�R���C�_�[�ɒl���ăZ�b�g�ōX�V
	//�i���T�C�Y�A�c�T�C�Y�AOwner.X���W�AOwner.Y���W�j
	//m_CRect.Set(CenterLength.x * 2, CenterLength.y * 2, Owner->transform.Position.x, Owner->transform.Position.y);
	m_CRect.Set(CenterLength.x * 2, CenterLength.y * 2, keep_position.x, keep_position.y);
	//Update(Owner,);


}

/****	�Փ˂����I�u�W�F�N�g�̖��O�擾	****/
std::string BoxCollider2D::GetHitObject()
{
	return HitObject;
}



