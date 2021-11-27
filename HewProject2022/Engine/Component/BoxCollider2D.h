//*****************************************************************************
//!	@file	Engine/Component/BaxColliuder2D.h
//!	@brief	
//!	@note	2D�{�b�N�X�R���C�_
//!	@note	�R���C�_
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include "Transform.h"
#include "SpriteRenderer.h"
#include "../Math/CRect.h"
#include "../Create/GameObject.h"

namespace GameEngine
{
	class BoxCollider2D
	{
	private:
		Math::Vector2 CenterPos;//���S�_���W
		Math::Vector2 CenterLength;//���S�_����e�ӂւ̒�������
		Math::CRect m_CRect;//�R���C�_�[����

		//GameEngine::SpriteRenderer m_SpriteRenderer;//�ۗ�

	protected:

		Create::GameObject* Owner;//�R���C�_�[�̏��L��

		bool isActive;	//��Ԕ���

		bool isHit;	//�q�b�g����

		//bool isPush;//�v�b�V���o�b�N����

		XMFLOAT2 Offset;	//�I�t�Z�b�g

		std::string HitObject;

		Math::Vector2 PushBack;	//�����߂�

		Math::Vector2 keep_position;

	private:


	public:

		//�l�p�`�𐶐�

		virtual void Init(Create::GameObject* in_Owner, Math::Vector2 in_Size);	//������

		void Update(Create::GameObject *in_Owner, Math::Vector2 in_Size);	//�X�V

		void SetOffset(float in_OffsetX, float in_OffsetY);		//�I�t�Z�b�g�ݒ�

		void HitCheckBox(BoxCollider2D &in_objcollider);		//�����蔻��
		void SetisActive(bool in_isactive);					//�A�N�e�B�u�L���ݒ�
		bool GetisActive();

		void SetisHit(bool in_ishit);
		bool GetisHit();

		/*void SetisPush(bool in_isPush);
		bool GetisPush();*/



		//�����߂�����
		void PushBackObject(Create::GameObject *in_Owner);

		std::string GetHitObject();

		//���ꁫ
		//SpriteRenderer��getsize�ŉ摜�̃T�C�Y��ǂݎ��->�i�[//�ۗ�
		//CRect��set()�֐��ł��̃T�C�Y�̎l�p�`�𐶐�
	};

}




