//*****************************************************************************
//!	@file	Engine/Create/Animation.h
//!	@brief	
//!	@note	�A�j���[�V�����N���X
//!	@note	�A�j���[�V�����̊��N���X�B�p�����邱�ƂŎg�p�ł���B
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include <vector>
#include <map>

#define ANIMATION_LOOP (-1)

namespace
{
	class AnimationTable
	{
	public:
		std::vector<int> m_Frame;
		std::vector<int> m_Kind;

	public:
		/****	�A�j���[�V������ރZ�b�g	****/
		template<class... INT>
		void SetKind(INT... kind)
		{
			//�ϔz��̒��g��Copy����
			for (int k : std::initializer_list<int>{ kind... })
			{
				m_Kind.push_back(k);
			}
		}

		/*	�A�j���[�V�����t���[���Z�b�g	*/
		template<class... INT>
		void SetFrame(INT... frame)
		{
			//�ϔz��̒��g��Copy����
			for (int k : std::initializer_list<int>{ frame... })
			{
				m_Frame.push_back(k);
			}
		}
	};
}

namespace Create
{

	class Animation
	{
	public:
		Animation();
		virtual void Init();
		void Play(std::string AnimName);
	public:
		int GetFrame() { return m_animationFrame; }  //�t���[���擾
		int GetKind() { return m_kind; }			//��ސ��擾
		int GetFrameMax() { return FrameMax; }		//�t���[���ő吔�擾
		int GetKindMax() { return KindMax; }		//��ލő吔�擾
		float GetSpeed() { return m_speed; }		//�X�s�[�h�擾

	protected:
		//void CreateAnimation(std::string in_Name, std::vector<int> in_AnimTable);
		void CreateAnimation(std::string in_Name, ::AnimationTable in_AnimTable);

	protected:
		float m_speed;			// �A�j���[�V�����X�s�[�h
		int m_animationFrame;	// �t���[��
		int m_kind;				// �A�j���[�V�����̎��

		int FrameMax;			//�t���[���̍ő吔
		int KindMax;			//��ލő吔

		std::map<std::string, std::vector<int>> AnimationList;
		std::map<std::string, ::AnimationTable> AnimationTableList;

	private:
		float m_time;	// �o�ߎ���
	};
}

