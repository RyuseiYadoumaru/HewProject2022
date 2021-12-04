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
		void Debug();

		void HitCheckBox(BoxCollider2D &in_objcollider);		//当たり判定

		void PushBackObject();//押し戻し処理

		void SetOffset(float in_OffsetX, float in_OffsetY);		//オフセット設定
		void SetisActive(bool in_isactive);					//アクティブ有効設定
		bool GetisActive();

		std::string GetHitObject();

	private:
		Math::Vector2 CenterPos;	//中心点座標
		Math::Vector2 CenterLength;	//中心点から各辺への直線距離
		Math::Vector2 Offset;		//オフセット
		Math::Vector2 Size;			//サイズ

		Math::Vector2 m_ObjectSize;	//オブジェクトサイズ

		Math::CRect Rect;		//コライダー生成
		bool isActive;	//状態判定
		bool isHit;	//ヒット判定

		std::string HitObject;

		std::vector<BoxCollider2D> m_CheckList;
		std::vector<Math::Vector2> m_PushBackList;
		std::vector<std::string > m_HitObjectList;


	private:
		void HitCheck();

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




