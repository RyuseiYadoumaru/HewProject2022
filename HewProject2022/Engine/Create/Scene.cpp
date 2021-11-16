//*****************************************************************************
//!	@file	Engine/Create/Scene.cpp
//!	@brief	
//!	@note	�V�[���N���X
//!	@note	�V�[���̌��ƂȂ�B�p�����邱�ƂŃV�[�����쐬�ł���
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Scene.h"
#include "../Runtime/Graphics/DirectXGraphics.h"

//-----------------------------------------------------------------------------
// �X�^�e�B�b�N�@�����o�[
//-----------------------------------------------------------------------------
Create::Scene::STATE Create::Scene::State = Create::Scene::START;


//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param
//==============================================================================
Create::Scene::Scene()
{
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
//!	@fn		Instance
//!	@brief	�V�[���ɃI�u�W�F�N�g�𐶐�����
//!	@param	�I�u�W�F�N�g
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
//!	@brief	�V�[���ɃI�u�W�F�N�g��j������
//!	@param	�I�u�W�F�N�g�̖��O
//!	@retval	
//==============================================================================
void Create::Scene::Destroy(std::string in_ObjectName)
{
	ObjectArray[in_ObjectName]->Active = false;
	ObjectArray.erase(in_ObjectName);
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
