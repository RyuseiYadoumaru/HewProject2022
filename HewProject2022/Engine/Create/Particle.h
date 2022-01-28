//*****************************************************************************
//!	@file	Engine/Create/Particle.h
//!	@brief	
//!	@note	パーティクルクラス
//!	@note	パーティクルの基底クラス。継承することで使用できる。
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include <vector>
#include <map>
#include <stdarg.h>

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
		/*	アニメーションフレームセット	*/
		void SetFrame(int frame, ...)
		{
			int data = frame;
			m_Frame.push_back(data);
			va_list args;
			va_start(args, frame);

			//可変配列の中身をCopyする
			do
			{
				data = va_arg(args, int);
				m_Frame.push_back(data);

			} while (data != PARTICLE_FINISH);

			//可変引数解放
			va_end(args);
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
		int GetFrame() { return m_ParticleFrame; }  //フレーム取得
		int GetFrameMax() { return FrameMax; }		//フレーム最大数取得
		void StateStop() { State = PARTICLE_STOP; }
		void StateFinish() { State = PARTICLE_FINISH; }
		int GetState()const { return State; }
	protected:
		void Create(ParticleData set) { m_Particle = set; }

	protected:
		int m_ParticleFrame;
		int FrameMax;
		ParticleData m_Particle;

	private:
		std::string m_ParticleName;
		float m_time;	//経過時間
		int m_Counter;	//カウンタ
		int State;
	};

}
