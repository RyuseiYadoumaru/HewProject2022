//*****************************************************************************
//!	@file	Engine/Create/Scene.cpp
//!	@brief	
//!	@note	シーンクラス
//!	@note	シーンの元となる。継承することでシーンを作成できる
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Scene.h"
#include "../Runtime/Graphics/DirectXGraphics.h"
using namespace Create;

//-----------------------------------------------------------------------------
// スタティック　メンバー
//-----------------------------------------------------------------------------
Create::Scene::STATE							Create::Scene::State = Create::Scene::START;
Create::Camera*									Create::Scene::camera = nullptr;
std::map<std::string, Create::GameObject*>		Create::Scene::ObjectArray;
std::map<std::string, std::vector<Component*>>	Create::Scene::ComponenArray;
int												Create::Scene::ObjectCnt = 0;
std::vector<NAME>								Create::Scene::DestroyNameList;

//==============================================================================
//!	@fn		Find
//!	@brief	オブジェクト探索
//!	@param	
//!	@retval	オブジェクトアドレス（無かったらNULLを返す）
//==============================================================================
GameObject* Create::Scene::Find(ID& id)
{
	for (auto Obj : ObjectArray)
	{
		if (Obj.second->GetId() == id)
		{
			return Obj.second;
		}
	}

	return nullptr;
}

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param
//==============================================================================
Create::Scene::Scene()
{
	ObjectCnt = 0;
	Object::ObjectNum = 0;
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
//!	@fn		SetCamera
//!	@brief	シーンにカメラをセットする
//!	@param	
//!	@retval	
//==============================================================================
void Create::Scene::SetCamera()
{
	camera = new Camera("MainCamera");
	camera->Start();
	ObjectArray[camera->ToString()] = camera;
	ComponenArray.insert(std::make_pair(camera->ToString(), std::vector<Component*>()));

	for (auto Obj : camera->ComponentList)
	{
		ComponenArray[camera->ToString()].push_back(Obj);
	}
	ObjectCnt++;

}

//==============================================================================
//!	@fn		SystemUpdate
//!	@brief	ゲームに登場する全てのシステムを更新する
//!	@retval	
//==============================================================================
void Create::Scene::SystemUpdate()
{
	for (auto Obj : ComponenArray)
	{
		for (auto System : Obj.second)
		{
			System->Update();
		}
	}
}

//==============================================================================
//!	@fn		ObjectUpdate
//!	@brief	ゲームに登場する全てのオブジェクトの更新する
//!	@retval	
//==============================================================================
void Create::Scene::ObjectUpdate()
{
	/****	オブジェクト破棄	****/
	ObjectListDestroy();

	/****	オブジェクト更新	****/
	for (auto& Object : ObjectArray)
	{
		Object.second->Update();
	}
}

//==============================================================================
//!	@fn		ObjectEnd
//!	@brief	ゲームに登場する全てのオブジェクトの終了処理をする
//!	@retval	
//==============================================================================
void Create::Scene::ObjectEnd()
{
	for (auto Object : ObjectArray)
	{
		Object.second->End();
	}
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

//==============================================================================
//!	@fn		Releace
//!	@brief	リリース処理
//!	@param
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool Create::Scene::Releace()
{
	ObjectArray.clear();
	ComponenArray.clear();
	camera = nullptr;
	ObjectCnt = 0;

	return true;
}

//==============================================================================
//!	@fn		ObjectListDestroyDestroy
//!	@brief	オブジェクトリストを破棄する
//!	@param	
//!	@retval	
//==============================================================================
void Create::Scene::ObjectListDestroy()
{
	if (DestroyNameList.empty() == true) return;

	/****	オブジェクト破棄	****/
	for (auto& ObjName : DestroyNameList)
	{
		Destroy(ObjName);
	}
	DestroyNameList.clear();
}
