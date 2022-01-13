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

#define ANIMATION_STOP			   (1)
#define ANIMATION_PLAY			   (0)
#define ANIMATION_FINISH		  (-1)
#define ANIMATION_DELETE		  (-2)
#define ANIMATION_NAME_ERROR	(-404)

namespace
{
	class AnimationTable
	{
	public:
		std::vector<int> m_Frame;
		std::vector<int> m_Kind;
		std::vector<float> m_Key;

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

		/*	�A�j���[�V�����L�[�Z�b�g	*/
		template<class... FLOAT>
		void SetKey(FLOAT... key)
		{
			//�ϔz��̒��g��Copy����
			for (int k : std::initializer_list<float>{ key... })
			{
				m_Key.push_back(k);
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
		int Play(std::string AnimName);
		int Delete();
		int Stop();

	public:
		int GetFrame() { return m_animationFrame; }  //�t���[���擾
		int GetKind() { return m_kind; }			//��ސ��擾
		int GetFrameMax() { return FrameMax; }		//�t���[���ő吔�擾
		int GetKindMax() { return KindMax; }		//��ލő吔�擾

	protected:
		void CreateAnimation(std::string in_Name, ::AnimationTable in_AnimTable);

	protected:
		int m_animationFrame;	// �t���[��
		int m_kind;				// �A�j���[�V�����̎��

		int FrameMax;			//�t���[���̍ő吔
		int KindMax;			//��ލő吔

		std::map<std::string, ::AnimationTable> AnimationTableList;

	private:
		void AnimStart(std::string in_AnimName);

	private:
		std::string m_AnimationName;	//�A�j���[�V�����̖��O
		float m_time;	// �o�ߎ���
		int m_AnimationCounter;	//�A�j���[�V�����J�E���^
	};
}

