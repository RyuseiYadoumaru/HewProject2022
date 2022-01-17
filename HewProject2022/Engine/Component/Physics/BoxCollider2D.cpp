//*****************************************************************************
//!	@file	Engine/Component/Physics/BaxColliuder2D.cpp
//!	@brief	
//!	@note	2Dボックスコライダ
//!	@note	コライダ
//!	@author	YoshidaKouki
//*****************************************************************************

#include "BoxCollider2D.h"
#include "../../Runtime/Graphics/DirectXGraphics.h"
#include "../../Data/DataArray.h"
#include "../../Runtime/Graphics/Shader.h"
#include "../../Runtime/Tools/Log.h"

using namespace Math;
using namespace Create;
using namespace GameEngine;

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
GameEngine::BoxCollider2D::BoxCollider2D()
{
	isActive = true;
	isHit = false;
	Offset.Set(0.0f, 0.0f);
	Size.Set(1.0f, 1.0f);//コライダーのサイズ設定
	//三木原追加
	isHit_overBlock = false;
	isHit_underBlock = false;
	isHit_rightBlock = false;
	isHit_leftBlock = false;
}

//==============================================================================
//!	@fn		Init
//!	@brief　初期化
//!	@param	オブジェクトサイズ
//==============================================================================
void BoxCollider2D::Init(Math::Vector2 in_Size)
{

	/*	オブジェクトサイズ保存	*/
	m_ObjectSize.Set(in_Size.x, in_Size.y);


	/****	コライダ再生成	****/
	CreateCollider();

#pragma region Debug
	/****	デバイス取得	****/
	ID3D11Device* device = DirectXGraphics::Instance()->GetDevice();

	/****	デバイスコンテキスト取得	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	/****	頂点シェーダー生成	****/
	vertexShader.Set(DataArray::GetvsShader("vs_Debug"));

	/****	ピクセルシェーダー生成	****/
	pixcelShader.Set(DataArray::GetpsShader("ps_Debug"));

	/****	頂点座標	****/
	VERTEX_RECT vertex[4] =
	{
		XMFLOAT3(Rect.GetButtomLeft().x, Rect.GetButtomLeft().y, 0.0f),	XMFLOAT4(0.0f,1.0f,0.0f,1.0f),
		XMFLOAT3(Rect.GetTopLeft().x,	 Rect.GetTopLeft().y,	 0.0f),	XMFLOAT4(0.0f,1.0f,0.0f,1.0f),
		XMFLOAT3(Rect.GetButtomRight().x,Rect.GetButtomRight().y,0.0f),	XMFLOAT4(0.0f,1.0f,0.0f,1.0f),
		XMFLOAT3(Rect.GetTopRight().x,	 Rect.GetTopRight().y,	 0.0f),	XMFLOAT4(0.0f,1.0f,0.0f,1.0f)

	};

	/****	頂点バッファ生成	****/
	bool sts = false;
	sts = Shader::CreateVertexBuffer
	(
		device,
		sizeof(VERTEX_RECT),
		4,
		vertex,
		&VertexBuffer
	);

	if (sts == false)
	{
		Log::LogError("頂点バッファの生成に失敗しました");
	}
#pragma endregion デバッグ用

}

//==============================================================================
//!	@fn		Update
//!	@brief　更新
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool BoxCollider2D::Update()
{
	//当たっているオブジェクトを初期化する
	m_HitObjectList.clear();
	m_HitObjectIdList.clear();

	/****	コライダ再生成	****/
	CreateCollider();

	/****	当たり判定	****/
	HitCheck();

	return true;

}

//==============================================================================
//!	@fn		Debug
//!	@brief	コライダ描画処理
//!	@param
//==============================================================================
void GameEngine::BoxCollider2D::Debug(float red, float green, float blue)
{
	/****	デバイスコンテキスト取得	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	/****	頂点座標	****/
	VERTEX_RECT vertex[4] =
	{
		XMFLOAT3(Rect.GetButtomLeft().x, Rect.GetButtomLeft().y, 0.0f),	XMFLOAT4(red,green,blue,1.0f),
		XMFLOAT3(Rect.GetTopLeft().x,	 Rect.GetTopLeft().y,	 0.0f),	XMFLOAT4(red,green,blue,1.0f),
		XMFLOAT3(Rect.GetButtomRight().x,Rect.GetButtomRight().y,0.0f),	XMFLOAT4(red,green,blue,1.0f),
		XMFLOAT3(Rect.GetTopRight().x,	 Rect.GetTopRight().y,	 0.0f),	XMFLOAT4(red,green,blue,1.0f)
	};

	/****	頂点データ更新	****/
	deviceContext->UpdateSubresource
	(
		VertexBuffer,		// 更新対象のバッファ
		0,						// インデックス(0)
		NULL,					// 更新範囲(nullptr)
		vertex,					// 反映データ
		0,						// データの1行のサイズ(0)
		0						// 1深度スライスのサイズ(0)
	);

	/****	頂点バッファ設定	****/
	UINT stride = sizeof(VERTEX_RECT);
	UINT offset = 0;

	bool sts = false;

	/****	頂点バッファセット	****/
	deviceContext->IASetVertexBuffers(
		0,						// スタートスロット
		1,						// 頂点バッファ個数
		&VertexBuffer,			// 頂点バッファの先頭アドレス
		&stride,				// ストライド
		&offset);				// オフセット


	/****	トポロジーセット	****/
	deviceContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP));

	/****	頂点レイアウトセット	****/
	deviceContext->IASetInputLayout(vertexShader.GetInputLayout());

	deviceContext->VSSetShader(vertexShader.GetVertexShader(), nullptr, 0);		// 頂点シェーダーをセット
	deviceContext->PSSetShader(pixcelShader.GetPixelShader(), nullptr, 0);		// ピクセルシェーダーをセット

	/****	描画	****/
	deviceContext->Draw(4, 0);
}

//==============================================================================
//!	@fn		HitCheckBox
//!	@brief　当たり判定処理
//!	@param	判定オブジェクト
//==============================================================================
void BoxCollider2D::HitCheckBox(BoxCollider2D& in_ObjCollider)
{
	/*	チェックオブジェクト追加	*/
	m_CheckList.push_back(in_ObjCollider);

}

//==============================================================================
//!	@fn		PushBackObject
//!	@brief　押し戻し処理
//!	@param
//==============================================================================
void BoxCollider2D::PushBackObject()
{

	//当たり判定が複数個分加算されている
	//1つ１つHitCheck＆PushBack処理をかけてあげるとうまくいくと思う！！！！！
	//上手くいった！！！！

	Owner->transform->Position = FixPosition;


}

//==============================================================================
//!	@fn		SetOffset
//!	@brief　オフセット設定
//!	@param	OffsetX, OffsetY
//==============================================================================
void BoxCollider2D::SetOffset(float in_OffsetX, float in_OffsetY)
{
	Offset.x = in_OffsetX;
	Offset.y = in_OffsetY;
}

//==============================================================================
//!	@fn		SetOffset
//!	@brief　オフセット設定
//!	@param	OffsetX, OffsetY
//==============================================================================
void GameEngine::BoxCollider2D::SetSize(float in_SizeX, float in_SizeY)
{
	Size.x = in_SizeX;
	Size.y = in_SizeY;
}

//==============================================================================
//!	@fn		SetisActive
//!	@brief　アクティブ設定
//!	@param	フラグ
//==============================================================================
void BoxCollider2D::SetisActive(bool in_isActive)
{
	isActive = in_isActive;

}

//==============================================================================
//!	@fn		GetisActive
//!	@brief　アクティブ取得
//!	@retval	アクティブフラグ
//==============================================================================
bool BoxCollider2D::GetisActive()
{
	return isActive;
}


//==============================================================================
//!	@fn		HitCheck
//!	@brief　当たり判定を調べる
//!	@param	
//==============================================================================
void GameEngine::BoxCollider2D::HitCheck()
{
	Vector2 PushBack;
	Vector2 Distance;
	Vector2 HalfTotalLength;
	isHit = false;

	isHit_overBlock = false;
	isHit_underBlock = false;
	isHit_rightBlock = false;
	isHit_leftBlock = false;

	//アクティブ出ないならisHitをfalseに
	if (isActive == false)
	{
		isHit = false;

		isHit_overBlock = false;
		isHit_underBlock = false;
		isHit_rightBlock = false;
		isHit_leftBlock = false;
		return;
	}

	/*	座標を保存しておく	*/
	FixPosition = Owner->transform->Position;
	/*	当たり判定	*/
	for (auto Check : m_CheckList)
	{
		//相手の中心座標ー自分の中心座標
		Distance.x = fabsf(Check.CenterPos.x - CenterPos.x);
		Distance.y = fabsf(Check.CenterPos.y - CenterPos.y);

		/*	Boxの縦/横長さ	*/
		HalfTotalLength.x = CenterLength.x + Check.CenterLength.x;
		HalfTotalLength.y = CenterLength.y + Check.CenterLength.y;

		/*	衝突判定	*/
		if (Distance.x < HalfTotalLength.x &&
			Distance.y < HalfTotalLength.y)
		{
			/*	衝突	*/
			isHit = true;

			/*	押し戻し値計算	*/
			//オブジェクト左辺 - プレイヤー右辺
			float dx1 = (Check.CenterPos.x - Check.CenterLength.x) - (CenterPos.x + CenterLength.x);
			//オブジェクト右辺 - プレイヤー左辺
			float dx2 = (Check.CenterPos.x + Check.CenterLength.x) - (CenterPos.x - CenterLength.x);
			//オブジェクト上辺 - プレイヤー下辺
			float dy1 = (Check.CenterPos.y - Check.CenterLength.y) - (CenterPos.y + CenterLength.y);
			//オブジェクト下辺 - プレイヤー上辺
			float dy2 = (Check.CenterPos.y + Check.CenterLength.y) - (CenterPos.y - CenterLength.y);



			PushBack.x = fabsf(dx1) < fabsf(dx2) ? dx1 : dx2;//:?: 条件演算子
			PushBack.y = fabsf(dy1) < fabsf(dy2) ? dy1 : dy2;
			if (fabsf(PushBack.x) < fabsf(PushBack.y))
			{
				PushBack.y = 0.0f;
			}
			else
			{
				PushBack.x = 0.0f;
			}

			/*	押し戻し処理	*/
			FixPosition += PushBack;
			CreateCollider(FixPosition);

			if (PushBack.y < 0) {
				//printf("着地!");
				isHit_underBlock = true;
			}
			if (PushBack.y > 0) {
				//printf("頭ぶつけた!");
				isHit_overBlock = true;
			}
			if (PushBack.x < 0) {
				//printf("右!");
				isHit_rightBlock = true;
			}
			if (PushBack.x > 0) {
				//printf("左!");
				isHit_leftBlock = true;
			}

			//printf("\n");

			/*	ヒットオブジェクト格納	*/
			m_HitObjectList.push_back(Check.Owner->GetName());
			m_HitObjectIdList.push_back(Check.Owner->GetId());
		}
	}
	//チェックオブジェクトを使用したので初期化する
	m_CheckList.clear();

}

//==============================================================================
//!	@fn		CreateCollider
//!	@brief　コライダ生成
//!	@param	
//==============================================================================
void GameEngine::BoxCollider2D::CreateCollider()
{
	//サイズの半分の長さを求める(更新)
	CenterLength.x = (m_ObjectSize.x * Owner->transform->Scale.x) / 2.0f;
	CenterLength.y = (m_ObjectSize.y * Owner->transform->Scale.y) / 2.0f;

	/*	コライダサイズ設定	*/
	CenterLength.x *= Size.x;
	CenterLength.y *= Size.y;

	/*	中心点座標更新	*/
	//センターposにtransformのpositionをいれて常に更新（更新）
	CenterPos.x = Owner->transform->Position.x + (Offset.x * CenterLength.x);
	CenterPos.y = Owner->transform->Position.y + (Offset.y * CenterLength.y);

	//コライダーに値を再セットで更新
	//（横サイズ、縦サイズ、Owner.X座標、Owner.Y座標）
	Rect.Set(CenterLength.x * 2, CenterLength.y * 2, CenterPos.x, CenterPos.y);
}

//==============================================================================
//!	@fn		CreateCollider
//!	@brief　コライダ生成
//!	@param	XY座標
//==============================================================================
void GameEngine::BoxCollider2D::CreateCollider(Math::Vector2& Pos)
{
	//サイズの半分の長さを求める(更新)
	CenterLength.x = (m_ObjectSize.x * Owner->transform->Scale.x) / 2.0f;
	CenterLength.y = (m_ObjectSize.y * Owner->transform->Scale.y) / 2.0f;

	/*	コライダサイズ設定	*/
	CenterLength.x *= Size.x;
	CenterLength.y *= Size.y;

	/*	中心点座標更新	*/
	//センターposにtransformのpositionをいれて常に更新（更新）
	CenterPos.x = Pos.x + (Offset.x * CenterLength.x);
	CenterPos.y = Pos.y + (Offset.y * CenterLength.y);

	//コライダーに値を再セットで更新
	//（横サイズ、縦サイズ、Owner.X座標、Owner.Y座標）
	Rect.Set(CenterLength.x * 2, CenterLength.y * 2, CenterPos.x, CenterPos.y);
}
