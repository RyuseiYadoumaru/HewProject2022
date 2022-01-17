//*****************************************************************************
//!	@file	Engine/Component/Physics/BaxColliuder2D.h
//!	@brief	
//!	@note	2Dボックスコライダ
//!	@note	コライダ
//!	@author	YoshidaKouki
//*****************************************************************************
#pragma once
#include <vector>
#include "../Component.h"
#include "../../Math/CRect.h"
#include "../../Create/GameObject.h"
#include "../../Runtime/Core/psShader.h"
#include "../../Runtime/Core/vsShader.h"

namespace GameEngine
{
	class BoxCollider2D : public Component
	{
	public:

		BoxCollider2D();

		void Init(Math::Vector2 in_Size);	//初期化
		bool Update() override;		//更新
		void Debug(float red = 0.0f, float green = 1.0f, float blue = 0.0f);

		void HitCheckBox(BoxCollider2D &in_objcollider);		//当たり判定

		void PushBackObject();//押し戻し処理

		void SetOffset(float in_OffsetX, float in_OffsetY);		//オフセット設定
		void SetSize(float in_SizeX, float in_SizeY);			//サイズ設定
		void SetisActive(bool in_isactive);					//アクティブ有効設定
		bool GetisActive();

		//三木原追加
		bool GetisHit() { return isHit; }
		bool GetisHit_overBlock() { return isHit_overBlock; }
		bool GetisHit_underBlock() { return isHit_underBlock; }
		bool GetisHit_rightBlock() { return isHit_rightBlock; }
		bool GetisHit_leftBlock() { return isHit_leftBlock; }
		void SetisHit_underBlock(bool flg) { isHit_underBlock = flg; }

		Math::Vector2& GetCenterPos() { return CenterPos; }
		Math::Vector2& GetCenterLength() { return CenterLength; }


		std::vector<std::string>& GetHitObject() { return m_HitObjectList; }
		std::vector<ID> GetHitObjectId()& { return m_HitObjectIdList; }

	private:
		Math::Vector2 CenterPos;	//中心点座標
		Math::Vector2 CenterLength;	//中心点から各辺への直線距離
		Math::Vector2 Offset;		//オフセット
		Math::Vector2 Size;			//サイズ

		Math::Vector2 m_ObjectSize;	//オブジェクトサイズ

		Math::CRect Rect;		//コライダー生成
		bool isActive;	//状態判定
		bool isHit;	//ヒット判定

		//三木原追加
		bool isHit_overBlock; //自分より上のブロックとの当たり判定
		bool isHit_underBlock; //自分より下のブロックとの当たり判定
		bool isHit_rightBlock; //自分より右のブロックとの当たり判定
		bool isHit_leftBlock; //自分より左のブロックとの当たり判定

		std::vector< BoxCollider2D > m_CheckList;
		std::vector< Math::Vector2 > m_PushBackList;
		std::vector< std::string > m_HitObjectList;
		std::vector< ID > m_HitObjectIdList;

		Math::Vector2 FixPosition;

	private:
		void HitCheck();

		void CreateCollider();
		void CreateCollider(Math::Vector2& Pos);

	private:
		struct VERTEX_RECT
		{
			DirectX::XMFLOAT3 Position;
			DirectX::XMFLOAT4 Color;
		};

		ID3D11Buffer* VertexBuffer = nullptr;
		vsShader vertexShader;
		psShader pixcelShader;

	};
}




