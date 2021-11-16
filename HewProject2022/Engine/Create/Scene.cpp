//*****************************************************************************
//!	@file	Engine/Create/Scene.cpp
//!	@brief	
//!	@note	シーンクラス
//!	@note	シーンの元となる。継承することでシーンを作成できる
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Scene.h"
#include "../Runtime/Graphics/DirectXGraphics.h"

//-----------------------------------------------------------------------------
// スタティック　メンバー
//-----------------------------------------------------------------------------
Create::Scene::STATE Create::Scene::State = Create::Scene::START;


//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param
//==============================================================================
Create::Scene::Scene()
{
}

//==============================================================================
//!	@fn		Render
//!	@brief	シーン描画
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Create::Scene::Render()
{

	/****	画面クリア	****/
	ClearDisplay();

	/****	画面描画	****/
	SwapChain();

	return true;

}

//==============================================================================
//!	@fn		Instance
//!	@brief	シーンにオブジェクトを生成する
//!	@param	オブジェクト
//!	@retval	
//==============================================================================
void Create::Scene::Instance(Object* out_Object)
{
	out_Object->Active = true;
	out_Object->Start();
	ObjectArray.insert(std::make_pair(out_Object->ToString(), out_Object));
}

//==============================================================================
//!	@fn		Destroy
//!	@brief	シーンにオブジェクトを破棄する
//!	@param	オブジェクトの名前
//!	@retval	
//==============================================================================
void Create::Scene::Destroy(std::string in_ObjectName)
{
	ObjectArray[in_ObjectName]->Active = false;
	ObjectArray.erase(in_ObjectName);
}

//==============================================================================
//!	@fn		GetState
//!	@brief	シーン状態取得
//!	@param
//!	@retval	シーン状態
//==============================================================================
Create::Scene::STATE Create::Scene::GetState() const
{
	return Create::Scene::State;
}

//==============================================================================
//!	@fn		SetState
//!	@brief	シーン状態セット
//!	@param
//!	@retval
//==============================================================================
void Create::Scene::SetState(const STATE in_State)
{
	Create::Scene::State = in_State;
}

//==============================================================================
//!	@fn		ClearDisplay
//!	@brief	画面クリア
//!	@param
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Create::Scene::ClearDisplay()
{
	/****	デバイスコンテキスト取得	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	/****	レンダーターゲットビュー取得	****/
	ID3D11RenderTargetView* RenderTargetView = DirectXGraphics::Instance()->GetRenderTargetView();

	/****	背景クリア	****/
	Math::Color* c = camera->GetBackgroundColor();
	float clearColor[4] = { c->r, c->g, c->b, c->a };
	deviceContext->ClearRenderTargetView(RenderTargetView, clearColor);

	return true;
}

//==============================================================================
//!	@fn		ClearDisplay
//!	@brief	画面クリア
//!	@param
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Create::Scene::SwapChain()
{
	/****	スワップチェイン取得	****/
	IDXGISwapChain* SwapChain = DirectXGraphics::Instance()->GetSwapChain();

	/****	ダブルバッファ領域コピー	****/
	SwapChain->Present(0, 0);

	return true;
}
