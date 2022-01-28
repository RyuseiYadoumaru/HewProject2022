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
#include <stdarg.h>

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
		void SetKind(int kind, ...)
		{
			int data = kind;
			va_list args;
			va_start(args, kind);
			//�ϔz��̒��g��Copy����
			while (data != ANIMATION_FINISH)
			{
				m_Kind.push_back(data);
				data = va_arg(args, int);
			}

			//�ψ������
			va_end(args);
		}

		/*	�A�j���[�V�����t���[���Z�b�g	*/
		void SetFrame(int frame, ...)
		{
			int data = frame;
			m_Frame.push_back(data);
			va_list args;
			va_start(args, frame);

			//�ϔz��̒��g��Copy����
			do
			{
				data = va_arg(args, int);
				m_Frame.push_back(data);

			} while (data != ANIMATION_FINISH);

			//�ψ������
			va_end(args);
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

