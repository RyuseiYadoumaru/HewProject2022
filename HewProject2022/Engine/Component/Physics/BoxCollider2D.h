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
		void Debug();

		void HitCheckBox(BoxCollider2D &in_objcollider);		//�����蔻��

		void PushBackObject();//�����߂�����

		void SetOffset(float in_OffsetX, float in_OffsetY);		//�I�t�Z�b�g�ݒ�
		void SetisActive(bool in_isactive);					//�A�N�e�B�u�L���ݒ�
		bool GetisActive();

		std::string GetHitObject();

	private:
		Math::Vector2 CenterPos;	//���S�_���W
		Math::Vector2 CenterLength;	//���S�_����e�ӂւ̒�������
		Math::Vector2 Offset;		//�I�t�Z�b�g
		Math::Vector2 Size;			//�T�C�Y

		Math::Vector2 m_ObjectSize;	//�I�u�W�F�N�g�T�C�Y

		Math::CRect Rect;		//�R���C�_�[����
		bool isActive;	//��Ԕ���
		bool isHit;	//�q�b�g����

		std::string HitObject;

		std::vector<BoxCollider2D> m_CheckList;
		std::vector<Math::Vector2> m_PushBackList;
		std::vector<std::string > m_HitObjectList;


	private:
		void HitCheck();

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




