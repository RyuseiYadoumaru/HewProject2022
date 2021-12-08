//*****************************************************************************
//!	@file	Engine/Create/GameObject.cpp
//!	@brief	
//!	@note	�Q�[���I�u�W�F�N�g�N���X
//!	@note	�Q�[���I�u�W�F�N�g�̌��ƂȂ�
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "GameObject.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
Create::GameObject::GameObject()
{
	Active = true;
	name = "NoName";
	id += ObjectNum + GAMEOBJECT_ID;
	transform = AddComponent<GameEngine::Transform>();
}

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	�I�u�W�F�N�g���O
//==============================================================================
Create::GameObject::GameObject(std::string in_Name)
{
	Active = true;
	name = in_Name;
	id += ObjectNum + GAMEOBJECT_ID;
	transform = AddComponent<GameEngine::Transform>();

}

//==============================================================================
//!	@fn		GetTransform
//!	@brief	�g�����X�t�H�[���擾
//!	@param	
//!	@retval	transform
//==============================================================================
Transform Create::GameObject::GetTransform()
{
	return *transform;
}
