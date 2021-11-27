#include "BoxCollider2D.h"

using namespace Math;
using namespace Create;
using namespace GameEngine;

//この関数を使うと四角形生成
void BoxCollider2D::Init(Create::GameObject* in_Owner, Math::Vector2 in_Size)
{
	/*	オーナー設定	*/
	Owner = in_Owner;

	isActive = true;

	isHit = false;

	//isPush = false;

	Offset = { 0, 0 };			//オフセットデフォルト値
	CenterLength = { 0,0 };

	//サイズの半分の長さを求める(初期値)
	CenterLength.x = in_Size.x / 2;
	CenterLength.y = in_Size.y / 2;

	//センターposにtransformのpositionをいれて常に更新（初期値）
	CenterPos.x = Owner->transform.Position.x;
	CenterPos.y = Owner->transform.Position.y;


	//sizeをowner毎に自動にする 
	//四角形生成
	//m_CRect.Set(in_Size.x, in_Size.y, CenterPos.x, CenterPos.y);

}

void BoxCollider2D::Update(Create::GameObject *in_Owner, Vector2 in_Size)
{
	//
	Owner = in_Owner;

	//サイズの半分の長さを求める(更新)
	CenterLength.x = in_Size.x / 2;
	CenterLength.y = in_Size.y / 2;

	/*	中心点座標更新	*/
	//センターposにtransformのpositionをいれて常に更新（更新）
	CenterPos.x = Owner->transform.Position.x;
	CenterPos.y = Owner->transform.Position.y;

	/*	中心点長さ更新	*/
	//CenterLength.x = in_Size.x * Owner->transform.Scale.x;
	//CenterLength.y = in_Size.y * Owner->transform.Scale.y;

	//CenterLength =
	//{
	//	fabsf(CenterPos.x - (Vertex.GetTopLeft().x + CenterLength.x)),
	//	fabsf(CenterPos.y - (Vertex.GetTopLeft().y + CenterLength.y)),
	//};


	/*	中心点長さ設定	*/
	/*CenterLength.x *= Size.x;
	CenterLength.y *= Size.y;*/

	/*	中心点座標設定	*/
	//CenterPos.x += Offset.x * CenterLength.x;
	//CenterPos.y += Offset.y * CenterLength.y;


	//コライダーに値を再セットで更新
	//（横サイズ、縦サイズ、Owner.X座標、Owner.Y座標）
	m_CRect.Set(CenterLength.x * 2, CenterLength.y * 2, Owner->transform.Position.x, Owner->transform.Position.y);

	//
	//	/*	Rect更新	*/
	//	Vector2 TopLeft;
	//	Vector2 TopRight;
	//	Vector2 ButtomLeft;
	//	Vector2 ButtomRight;
	//
	//#pragma region UpdateRect
	//	//各4頂点の更新
	//
	//	TopLeft.x = Owner->transform.Position.x + Offset.x;
	//	TopLeft.y = Owner->transform.Position.y + Offset.y;
	//
	//
	//	ButtomLeft.x = Owner->transform.Position.x + Offset.x;
	//	ButtomLeft.y = Owner->transform.Position.y + (CenterLength.y * 2) + Offset.y;
	//
	//
	//	TopRight.x = Owner->transform.Position.x + (CenterLength.x * 2) + Offset.x;
	//	TopRight.y = Owner->transform.Position.y + Offset.y;
	//
	//	ButtomRight.x = Owner->transform.Position.x + (CenterLength.x * 2) + Offset.x;
	//	ButtomRight.y = Owner->transform.Position.y + (CenterLength.y * 2) + Offset.y;
	//

	//#pragma endregion Rectの値を更新
		//ここがまだできてない
		//何ならここいらないんじゃね？

		/*Vertex.SetTopLeft(TopLeft);
		Vertex.SetButtomLeft(ButtomLeft);
		Vertex.SetTopRight(TopRight);
		Vertex.SetButtomRight(ButtomRight);*/

}

void BoxCollider2D::SetOffset(float in_OffsetX, float in_OffsetY)
{
	Offset.x = in_OffsetX;
	Offset.y = in_OffsetY;
}

/****	ボックスコライダ当たり判定	****/
void BoxCollider2D::HitCheckBox(BoxCollider2D &in_ObjCollider)
{
	Vector2 Distance;
	Vector2 HalfTotalLength;

	//アクティブ出ないならisHitをfalseに
	if (isActive == false || in_ObjCollider.isActive == false)
	{
		isHit = false;
		return;
	}

	/*	当たり判定	*/
	//相手の中心座標ー自分の中心座標
	Distance.x = fabsf(in_ObjCollider.CenterPos.x - CenterPos.x);
	Distance.y = fabsf(in_ObjCollider.CenterPos.y - CenterPos.y);

	/*	Boxの縦/横長さ	*/
	HalfTotalLength.x = CenterLength.x + in_ObjCollider.CenterLength.x;
	HalfTotalLength.y = CenterLength.y + in_ObjCollider.CenterLength.y;

	/*	衝突判定	*/
	if (Distance.x < HalfTotalLength.x &&
		Distance.y < HalfTotalLength.y)
	{
		isHit = true;//衝突
		keep_position.x = Owner->transform.Position.x;
		keep_position.y = Owner->transform.Position.y;

	}
	else
	{
		isHit = false;//非衝突
		return;
	}

	/*	押し戻し値計算	*/

	//オブジェクト左辺 - プレイヤー右辺
	float dx1 = (in_ObjCollider.CenterPos.x - in_ObjCollider.CenterLength.x) - (CenterPos.x + CenterLength.x);
	//オブジェクト右辺 - プレイヤー左辺
	float dx2 = (in_ObjCollider.CenterPos.x + in_ObjCollider.CenterLength.x) - (CenterPos.x - CenterLength.x);
	//オブジェクト上辺 - プレイヤー下辺
	float dy1 = (in_ObjCollider.CenterPos.y - in_ObjCollider.CenterLength.y) - (CenterPos.y + CenterLength.y);
	//オブジェクト下辺 - プレイヤー上辺
	float dy2 = (in_ObjCollider.CenterPos.y + in_ObjCollider.CenterLength.y) - (CenterPos.y - CenterLength.y);

	PushBack.x = fabsf(dx1) < fabsf(dx2) ? dx1 : dx2;
	PushBack.y = fabsf(dy1) < fabsf(dy2) ? dy1 : dy2;

	if (fabsf(PushBack.x) < fabsf(PushBack.y))
	{
		PushBack.y = 0.0f;
	}
	else
	{
		PushBack.x = 0.0f;
	}

	//PushBackObject(Owner);

	//if (PushBack.x > 0 && PushBack.y > 0) {

	//	isPush = true;
	//	//PushBackObject(Owner);
	//}
	//else 
	//{
	//	return;
	//}

	//ここまだできてない->すこしできた
	//HitObject = in_ObjCollider.Owner->GetName();


}

void BoxCollider2D::SetisActive(bool in_isActive)
{
	isActive = in_isActive;

}

bool BoxCollider2D::GetisActive()
{
	return isActive;
}

void BoxCollider2D::SetisHit(bool in_isHit)
{
	isHit = in_isHit;
}

bool BoxCollider2D::GetisHit()
{
	return isHit;
}

//void GameEngine::BoxCollider2D::SetisPush(bool in_isPush)
//{
//	isPush = in_isPush;
//}
//
//bool GameEngine::BoxCollider2D::GetisPush()
//{
//	return isPush;
//}

void BoxCollider2D::PushBackObject(Create::GameObject *in_Owner)
{

	Owner->transform.Position.x += PushBack.x;
	Owner->transform.Position.y += PushBack.y;
	PushBack.x = 0;
	PushBack.y = 0;
	//コライダーに値を再セットで更新
	//（横サイズ、縦サイズ、Owner.X座標、Owner.Y座標）
	//m_CRect.Set(CenterLength.x * 2, CenterLength.y * 2, Owner->transform.Position.x, Owner->transform.Position.y);
	m_CRect.Set(CenterLength.x * 2, CenterLength.y * 2, keep_position.x, keep_position.y);
	//Update(Owner,);


}

/****	衝突したオブジェクトの名前取得	****/
std::string BoxCollider2D::GetHitObject()
{
	return HitObject;
}



