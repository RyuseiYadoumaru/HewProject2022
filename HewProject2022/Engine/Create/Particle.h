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
		template<class... INT>
		void SetFrame(INT... frame)
		{
			//可変配列の中身をCopyする
			for (int k : std::initializer_list<int>{ frame... })
			{
				m_Frame.push_back(k);
			}
		}

		/*	アニメーションキーセット	*/
		template<class... FLOAT>
		void SetKey(FLOAT... key)
		{
			//可変配列の中身をCopyする
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
		int GetFrame() { return m_ParticleFrame; }  //フレーム取得
		int GetFrameMax() { return FrameMax; }		//フレーム最大数取得
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
		float m_time;	//経過時間
		int m_Counter;	//カウンタ
		int State;


	};

}
