//*****************************************************************************
//!	@file	Engine/Create/Scene.cpp
//!	@brief	
//!	@note	�V�[���N���X
//!	@note	�V�[���̌��ƂȂ�B�p�����邱�ƂŃV�[�����쐬�ł���
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Scene.h"
#include "../Runtime/Graphics/DirectXGraphics.h"
using namespace Create;

//-----------------------------------------------------------------------------
// �X�^�e�B�b�N�@�����o�[
//-----------------------------------------------------------------------------
Create::Scene::STATE							Create::Scene::State = Create::Scene::START;
Create::Camera*									Create::Scene::camera = nullptr;
std::map<std::string, Create::GameObject*>		Create::Scene::ObjectArray;
std::map<std::string, std::vector<Component*>>	Create::Scene::ComponenArray;
int												Create::Scene::ObjectCnt = 0;
std::vector<NAME>								Create::Scene::DestroyNameList;

//==============================================================================
//!	@fn		Find
//!	@brief	�I�u�W�F�N�g�T��
//!	@param	
//!	@retval	�I�u�W�F�N�g�A�h���X�i����������NULL��Ԃ��j
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
//!	@brief	�R���X�g���N�^
//!	@param
//==============================================================================
Create::Scene::Scene()
{
	ObjectCnt = 0;
	Object::ObjectNum = 0;
}

//==============================================================================
//!	@fn		Render
//!	@brief	�V�[���`��
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Create::Scene::Render()
{

	/****	��ʃN���A	****/
	ClearDisplay();

	/****	��ʕ`��	****/
	SwapChain();

	return true;

}

//==============================================================================
//!	@fn		SetCamera
//!	@brief	�V�[���ɃJ�������Z�b�g����
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
//!	@brief	�Q�[���ɓo�ꂷ��S�ẴV�X�e�����X�V����
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
//!	@brief	�Q�[���ɓo�ꂷ��S�ẴI�u�W�F�N�g�̍X�V����
//!	@retval	
//==============================================================================
void Create::Scene::ObjectUpdate()
{
	/****	�I�u�W�F�N�g�j��	****/
	ObjectListDestroy();

	/****	�I�u�W�F�N�g�X�V	****/
	for (auto& Object : ObjectArray)
	{
		Object.second->Update();
	}
}

//==============================================================================
//!	@fn		ObjectEnd
//!	@brief	�Q�[���ɓo�ꂷ��S�ẴI�u�W�F�N�g�̏I������������
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
//!	@brief	�V�[����Ԏ擾
//!	@param
//!	@retval	�V�[�����
//==============================================================================
Create::Scene::STATE Create::Scene::GetState() const
{
	return Create::Scene::State;
}

//==============================================================================
//!	@fn		SetState
//!	@brief	�V�[����ԃZ�b�g
//!	@param
//!	@retval
//==============================================================================
void Create::Scene::SetState(const STATE in_State)
{
	Create::Scene::State = in_State;
}

//==============================================================================
//!	@fn		ClearDisplay
//!	@brief	��ʃN���A
//!	@param
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Create::Scene::ClearDisplay()
{
	/****	�f�o�C�X�R���e�L�X�g�擾	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	/****	�����_�[�^�[�Q�b�g�r���[�擾	****/
	ID3D11RenderTargetView* RenderTargetView = DirectXGraphics::Instance()->GetRenderTargetView();

	/****	�w�i�N���A	****/
	Math::Color* c = camera->GetBackgroundColor();
	float clearColor[4] = { c->r, c->g, c->b, c->a };
	deviceContext->ClearRenderTargetView(RenderTargetView, clearColor);

	return true;
}

//==============================================================================
//!	@fn		ClearDisplay
//!	@brief	��ʃN���A
//!	@param
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Create::Scene::SwapChain()
{
	/****	�X���b�v�`�F�C���擾	****/
	IDXGISwapChain* SwapChain = DirectXGraphics::Instance()->GetSwapChain();

	/****	�_�u���o�b�t�@�̈�R�s�[	****/
	SwapChain->Present(0, 0);

	return true;
}

//==============================================================================
//!	@fn		Releace
//!	@brief	�����[�X����
//!	@param
//!	@retval	true:����I���@false:�ُ�I��
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
//!	@brief	�I�u�W�F�N�g���X�g��j������
//!	@param	
//!	@retval	
//==============================================================================
void Create::Scene::ObjectListDestroy()
{
	if (DestroyNameList.empty() == true) return;

	/****	�I�u�W�F�N�g�j��	****/
	for (auto& ObjName : DestroyNameList)
	{
		Destroy(ObjName);
	}
	DestroyNameList.clear();
}
