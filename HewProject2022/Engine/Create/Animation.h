//*****************************************************************************
//!	@file	Engine/Create/Animation.h
//!	@brief	
//!	@note	アニメーションクラス
//!	@note	アニメーションの基底クラス。継承することで使用できる。
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
		int GetFrame() { return m_animationFrame; }   //フレーム取得
		int GetKind() { return m_kind; }			//種類数取得
		float GetSpeed() { return m_speed; }		//スピード取得

	protected:
		float m_speed;			// アニメーションスピード
		int m_animationFrame;	// フレーム
		int m_kind;				// アニメーションの種類

	private:
		float m_time;	// 経過時間
	};
}

