//*****************************************************************************
//!	@file	Engine/Create/Animation.h
//!	@brief	
//!	@note	アニメーションクラス
//!	@note	アニメーションの基底クラス。継承することで使用できる。
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
		/****	アニメーション種類セット	****/
		template<class... INT>
		void SetKind(INT... kind)
		{
			//可変配列の中身をCopyする
			for (int k : std::initializer_list<int>{ kind... })
			{
				m_Kind.push_back(k);
			}
		}

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
		int GetFrame() { return m_animationFrame; }  //フレーム取得
		int GetKind() { return m_kind; }			//種類数取得
		int GetFrameMax() { return FrameMax; }		//フレーム最大数取得
		int GetKindMax() { return KindMax; }		//種類最大数取得
		float GetSpeed() { return m_speed; }		//スピード取得

	protected:
		//void CreateAnimation(std::string in_Name, std::vector<int> in_AnimTable);
		void CreateAnimation(std::string in_Name, ::AnimationTable in_AnimTable);

	protected:
		float m_speed;			// アニメーションスピード
		int m_animationFrame;	// フレーム
		int m_kind;				// アニメーションの種類

		int FrameMax;			//フレームの最大数
		int KindMax;			//種類最大数

		std::map<std::string, std::vector<int>> AnimationList;
		std::map<std::string, ::AnimationTable> AnimationTableList;

	private:
		float m_time;	// 経過時間
	};
}

