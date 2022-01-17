//*****************************************************************************
//!	@file	Engine/Component/Physics/BaxColliuder2D.h
//!	@brief	
//!	@note	2D�{�b�N�X�R���C�_
//!	@note	�R���C�_
//!	@author	YoshidaKouki
//*****************************************************************************
#pragma once
#include <vector>
#include "../Component.h"
#include "../../Math/CRect.h"
#include "../../Create/GameObject.h"
#include "../../Runtime/Core/psShader.h"
#include "../../Runtime/Core/vsShader.h"

namespace GameEngine
{
	class BoxCollider2D : public Component
	{
	public:

		BoxCollider2D();

		void Init(Math::Vector2 in_Size);	//������
		bool Update() override;		//�X�V
		void Debug(float red = 0.0f, float green = 1.0f, float blue = 0.0f);

		void HitCheckBox(BoxCollider2D &in_objcollider);		//�����蔻��

		void PushBackObject();//�����߂�����

		void SetOffset(float in_OffsetX, float in_OffsetY);		//�I�t�Z�b�g�ݒ�
		void SetSize(float in_SizeX, float in_SizeY);			//�T�C�Y�ݒ�
		void SetisActive(bool in_isactive);					//�A�N�e�B�u�L���ݒ�
		bool GetisActive();

		//�O�،��ǉ�
		bool GetisHit() { return isHit; }
		bool GetisHit_overBlock() { return isHit_overBlock; }
		bool GetisHit_underBlock() { return isHit_underBlock; }
		bool GetisHit_rightBlock() { return isHit_rightBlock; }
		bool GetisHit_leftBlock() { return isHit_leftBlock; }
		void SetisHit_underBlock(bool flg) { isHit_underBlock = flg; }

		Math::Vector2& GetCenterPos() { return CenterPos; }
		Math::Vector2& GetCenterLength() { return CenterLength; }


		std::vector<std::string>& GetHitObject() { return m_HitObjectList; }
		std::vector<ID> GetHitObjectId()& { return m_HitObjectIdList; }

	private:
		Math::Vector2 CenterPos;	//���S�_���W
		Math::Vector2 CenterLength;	//���S�_����e�ӂւ̒�������
		Math::Vector2 Offset;		//�I�t�Z�b�g
		Math::Vector2 Size;			//�T�C�Y

		Math::Vector2 m_ObjectSize;	//�I�u�W�F�N�g�T�C�Y

		Math::CRect Rect;		//�R���C�_�[����
		bool isActive;	//��Ԕ���
		bool isHit;	//�q�b�g����

		//�O�،��ǉ�
		bool isHit_overBlock; //��������̃u���b�N�Ƃ̓����蔻��
		bool isHit_underBlock; //������艺�̃u���b�N�Ƃ̓����蔻��
		bool isHit_rightBlock; //�������E�̃u���b�N�Ƃ̓����蔻��
		bool isHit_leftBlock; //������荶�̃u���b�N�Ƃ̓����蔻��

		std::vector< BoxCollider2D > m_CheckList;
		std::vector< Math::Vector2 > m_PushBackList;
		std::vector< std::string > m_HitObjectList;
		std::vector< ID > m_HitObjectIdList;

		Math::Vector2 FixPosition;

	private:
		void HitCheck();

		void CreateCollider();
		void CreateCollider(Math::Vector2& Pos);

	private:
		struct VERTEX_RECT
		{
			DirectX::XMFLOAT3 Position;
			DirectX::XMFLOAT4 Color;
		};

		ID3D11Buffer* VertexBuffer = nullptr;
		vsShader vertexShader;
		psShader pixcelShader;

	};
}




