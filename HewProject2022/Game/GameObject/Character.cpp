//*****************************************************************************
//!	@file	Game/GameObject/Character.cpp
//!	@brief	
//!	@note	�L�����N�^�[�N���X
//!	@note	�L�����N�^�[�I�u�W�F�N�g�̊��N���X
//!	@note	�L�����N�^�[�̃Q�[���I�u�W�F�N�g�Ɍp������
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Character.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	�I�u�W�F�N�g���O
//==============================================================================
Create::Character::Character(std::string in_Name) : GameObject(in_Name)
{
	m_SpriteRenderer = AddRenderer<GameEngine::SpriteRenderer>();
}

//==============================================================================
//!	@fn		Start
//!	@brief	������
//!	@note	�V�������������������Ƃ��̓I�[�o�[���C�h���Ă�������
//!	@note	�����ɃX�v���C�g�����_�[������������K���L�q���Ă�������
//!	@note	����L�q���Ȃ��Ă����悤�ɂ���\��ł�
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Create::Character::Start()
{
	m_SpriteRenderer->Init();
	AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
	return true;
}

//==============================================================================
//!	@fn		Update
//!	@brief	�X�V
//!	@note	�V�������������������Ƃ��̓I�[�o�[���C�h���Ă�������
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Create::Character::Update()
{

	return true;
}

//==============================================================================
//!	@fn		End
//!	@brief	�I��
//!	@note	�V�������������������Ƃ��̓I�[�o�[���C�h���Ă�������
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Create::Character::End()
{
	return true;
}

//==============================================================================
//!	@fn		Render
//!	@brief	�`��
//!	@note	��{�I�ɂ͐V���������������K�v������܂���B
//!	@note	�V�[���N���X��Render�ɕ`�悵�������Ԃɏ����Ă�������
//!	@note	���Ԃ�����Ύ����ŕ`�悷�鏈�������܂��B���҂��Ȃ��ł�ˁB
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Create::Character::Render()
{
	if (Active == true)
	{
		m_SpriteRenderer->Render();
	}

	return true;
}

//==============================================================================
//!	@fn		Sprite
//!	@brief	�X�v���C�g
//!	@note	�`�悵�����摜�̖��O������
//!	@retval	
//==============================================================================
void Create::Character::Sprite(std::string in_SpriteName)
{
	m_SpriteRenderer->SpriteName = in_SpriteName;
}

//==============================================================================
//!	@fn		Vertex
//!	@brief	���_�V�F�[�_�[
//!	@note	�g���������_�V�F�[�_�[�̖��O������
//!	@retval	
//==============================================================================
void Create::Character::Vertex(std::string in_VertexName)
{
	m_SpriteRenderer->VertexShaderName = in_VertexName;
}

//==============================================================================
//!	@fn		Pixcel
//!	@brief	�s�N�Z���V�F�[�_�[
//!	@note	�g�������s�N�Z���V�F�[�_�[�̖��O������
//!	@retval	
//==============================================================================
void Create::Character::Pixcel(std::string in_PixcelName)
{
	m_SpriteRenderer->PixcelShaderName = in_PixcelName;
}

