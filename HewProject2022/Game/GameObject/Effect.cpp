//*****************************************************************************
//!	@file	Game/GameObject/Effect.cpp
//!	@brief	
//!	@note	�G�t�F�N�g�N���X
//!	@note	�G�t�F�N�g�̊��N���X
//!	@note	�G�t�F�N�g�Q�[���I�u�W�F�N�g�Ɍp������
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Effect.h"
#include "../../Engine/Create/Scene.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param
//==============================================================================
Create::Effect::Effect() : GameObject()
{
	m_Owner = nullptr;
	m_SpriteRenderer = AddRenderer<GameEngine::SpriteRenderer>();
}

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	�I�u�W�F�N�g���O
//==============================================================================
Create::Effect::Effect(std::string in_Name) : GameObject(in_Name)
{
	m_Owner = nullptr;
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
bool Create::Effect::Start()
{
	m_SpriteRenderer->Init();
	return true;
}

//==============================================================================
//!	@fn		Update
//!	@brief	�X�V
//!	@note	�V�������������������Ƃ��̓I�[�o�[���C�h���Ă�������
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Create::Effect::Update()
{
	return true;
}

//==============================================================================
//!	@fn		End
//!	@brief	�I��
//!	@note	�V�������������������Ƃ��̓I�[�o�[���C�h���Ă�������
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Create::Effect::End()
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
bool Create::Effect::Render()
{
	if (Active == true)
	{
		m_SpriteRenderer->Render();
	}

	return true;
}

//==============================================================================
//!	@fn		SetSize
//!	@brief	�Z�b�g�T�C�Y
//!	@note	�摜�̃T�C�Y�𒲐�����
//!	@retval	
//==============================================================================
void Create::Effect::SetSize(float in_SizeX, float in_SizeY)
{
	m_SpriteRenderer->SetSize(in_SizeX, in_SizeY);
}

//==============================================================================
//!	@fn		Sprite
//!	@brief	�X�v���C�g
//!	@note	�`�悵�����摜�̖��O������
//!	@retval	
//==============================================================================
void Create::Effect::Sprite(std::string in_SpriteName)
{
	m_SpriteRenderer->SpriteName = in_SpriteName;
	m_SpriteRenderer->SetSprite(in_SpriteName);
}

//==============================================================================
//!	@fn		Vertex
//!	@brief	���_�V�F�[�_�[
//!	@note	�g���������_�V�F�[�_�[�̖��O������
//!	@retval	
//==============================================================================
void Create::Effect::Vertex(std::string in_VertexName)
{
	m_SpriteRenderer->VertexShaderName = in_VertexName;
	m_SpriteRenderer->SetVertexShader(in_VertexName);
}

//==============================================================================
//!	@fn		Pixcel
//!	@brief	�s�N�Z���V�F�[�_�[
//!	@note	�g�������s�N�Z���V�F�[�_�[�̖��O������
//!	@retval	
//==============================================================================
void Create::Effect::Pixcel(std::string in_PixcelName)
{
	m_SpriteRenderer->PixcelShaderName = in_PixcelName;
	m_SpriteRenderer->SetPixcelShader(in_PixcelName);
}

//==============================================================================
//!	@fn		SetOwnerTransform
//!	@brief	�g�����X�t�H�[���ݒ�
//!	@note	�I�[�i�[�̃g�����X�t�H�[����ݒ肷��
//!	@retval	
//==============================================================================
void Create::Effect::SetOwnerTransform()
{
	if (m_Owner != nullptr)
	{
		transform = m_Owner->transform;
	}
}
