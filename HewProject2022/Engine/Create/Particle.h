//*****************************************************************************
//!	@file	Engine/Create/Particle.h
//!	@brief	
//!	@note	�p�[�e�B�N���N���X
//!	@note	�p�[�e�B�N���̊��N���X�B�p�����邱�ƂŎg�p�ł���B
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include <vector>
#include <map>

#define PARTICLE_STOP			   (1)
#define PARTICLE_PLAY			   (0)
#define PARTICLE_FINISH			  (-1)
#define PARTICLE_DELETE			  (-2)
#define PARTICLE_NAME_ERROR		(-404)

namespace
{
	class ParticleTable
	{
	public:
		std::vector<int> m_Frame;
		std::vector<float> m_Key;

	public:
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

using ParticleData = ::ParticleTable;

namespace Create
{
	class Particle
	{

	public:
		Particle();
		virtual void Init();
		int Play();
		int PlayOneShot();
		int End();

	public:
		int GetFrame() { return m_ParticleFrame; }  //�t���[���擾
		int GetFrameMax() { return FrameMax; }		//�t���[���ő吔�擾
		void StateStop() { State = PARTICLE_STOP; }
		void StateFinish() { State = PARTICLE_FINISH; }
	protected:
		void Create(ParticleData set) { m_Particle = set; }

	protected:
		int m_ParticleFrame;
		int FrameMax;
		ParticleData m_Particle;

	private:
		bool ParticleStart();

	private:
		std::string m_ParticleName;
		float m_time;	//�o�ߎ���
		int m_Counter;	//�J�E���^
		int State;


	};

}
