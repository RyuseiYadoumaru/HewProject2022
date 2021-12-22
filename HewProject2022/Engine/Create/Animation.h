//*****************************************************************************
//!	@file	Engine/Create/Animation.h
//!	@brief	
//!	@note	�A�j���[�V�����N���X
//!	@note	�A�j���[�V�����̊��N���X�B�p�����邱�ƂŎg�p�ł���B
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once

#define ANIMATION_LOOP (-1)
namespace Create
{
	class Animation
	{
	public:
		Animation();
		virtual void Init() = 0;

	public:
		int GetFrame() { return m_animationFrame; }   //�t���[���擾
		int GetKind() { return m_kind; }			//��ސ��擾
		float GetSpeed() { return m_speed; }		//�X�s�[�h�擾

	protected:
		float m_speed;			// �A�j���[�V�����X�s�[�h
		int m_animationFrame;	// �t���[��
		int m_kind;				// �A�j���[�V�����̎��

	private:
		float m_time;	// �o�ߎ���
	};
}

