//*****************************************************************************
//!	@file	Engine/Component/BaxColliuder2D.h
//!	@brief	
//!	@note	2Dボックスコライダ
//!	@note	コライダ
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include "Transform.h"
#include "SpriteRenderer.h"
#include "../Math/CRect.h"
#include "../Create/GameObject.h"

namespace GameEngine
{
	class BoxCollider2D
	{
	private:
		Math::Vector2 CenterPos;//中心点座標
		Math::Vector2 CenterLength;//中心点から各辺への直線距離
		Math::CRect m_CRect;//コライダー生成

		//GameEngine::SpriteRenderer m_SpriteRenderer;//保留

	protected:

		Create::GameObject* Owner;//コライダーの所有者

		bool isActive;	//状態判定

		bool isHit;	//ヒット判定

		//bool isPush;//プッシュバック判定

		XMFLOAT2 Offset;	//オフセット

		std::string HitObject;

		Math::Vector2 PushBack;	//押し戻し

		Math::Vector2 keep_position;

	private:


	public:

		//四角形を生成

		virtual void Init(Create::GameObject* in_Owner, Math::Vector2 in_Size);	//初期化

		void Update(Create::GameObject *in_Owner, Math::Vector2 in_Size);	//更新

		void SetOffset(float in_OffsetX, float in_OffsetY);		//オフセット設定

		void HitCheckBox(BoxCollider2D &in_objcollider);		//当たり判定
		void SetisActive(bool in_isactive);					//アクティブ有効設定
		bool GetisActive();

		void SetisHit(bool in_ishit);
		bool GetisHit();

		/*void SetisPush(bool in_isPush);
		bool GetisPush();*/



		//押し戻し処理
		void PushBackObject(Create::GameObject *in_Owner);

		std::string GetHitObject();

		//流れ↓
		//SpriteRendererのgetsizeで画像のサイズを読み取る->格納//保留
		//CRectのset()関数でそのサイズの四角形を生成
	};

}




