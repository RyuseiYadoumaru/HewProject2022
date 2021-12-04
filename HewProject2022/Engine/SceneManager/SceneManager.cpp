//*****************************************************************************
//!	@file	Engine/SceneManager.cpp
//!	@brief	
//!	@note	�V�[���}�l�[�W���[�N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************
#include "SceneManager.h"
#include "../Runtime/Tools/Log.h"
#include "../../SceneList.h"
#include "../Runtime/Tools/Log.h"

//-----------------------------------------------------------------------------
// �X�^�e�B�b�N�@�����o�[
//-----------------------------------------------------------------------------

int GameEngine::SceneManager::SceneCount = 0;
Create::Scene* GameEngine::SceneManager::scene = NULL;
Create::Scene* GameEngine::SceneManager::NextScene = NULL;
std::map<std::string, Create::Scene*> GameEngine::SceneManager::SceneList;

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
GameEngine::SceneManager::SceneManager()
{

	CreateScene("TitleScene", new GamePlay::TitleScene);
	CreateScene("ResultScene", new GamePlay::ResultScene);
	CreateScene("SampleScene", new GamePlay::SampleScene);
	CreateScene("StageTestScene", new StageTestScene);
	CreateScene("ProtScene", new ProtScene);
	NextScene = SceneList["ProtScene"];
}

//==============================================================================
//!	@fn		CreateScene
//!	@brief	�V�[�����X�g�ɃV�[���𐶐�����
//!	@param	�V�[���̖��O
//!	@param	�V�[���A�h���X
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::SceneManager::CreateScene(std::string SceneName, Create::Scene* create)
{
	/****	�G���[�`�F�b�N	****/
	if (create == NULL)
	{
		Log::LogError("��������V�[����������܂���");
		return false;
	}

	SceneList.insert(std::make_pair(SceneName, create));
	SceneCount++;
	return true;
}

//==============================================================================
//!	@fn		LoadScene
//!	@brief	�V�[�������[�h����
//!	@param	���[�h����V�[���̖��O
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::SceneManager::LoadScene(std::string SceneName)
{
	if (SceneList.empty())
	{
		Log::LogError("�V�[��������܂���");
		return false;
	}

	NextScene = NULL;
	NextScene = SceneList[SceneName];

	/****	�G���[�`�F�b�N	****/
	if (scene == NULL)
	{
		Log::LogError("���[�h�V�[���Ɏ��s���܂���");
		return false;
	}

	/****	�V�[����ԕύX	****/
	scene->SetState(Create::Scene::END);

	return true;

}

//==============================================================================
//!	@fn		SetUp
//!	@brief	�V�[���̐ݒ���s��
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::SceneManager::SetUp()
{
	/****	�V�[���ύX	****/
	scene = NextScene;

	/****	�V�[����ԕύX	****/
	scene->SetState(Create::Scene::PLAY);

	return true;
}

//==============================================================================
//!	@fn		Releace
//!	@brief	�V�[���}�l�[�W���[�������
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::SceneManager::Releace()
{
	SceneList.clear();
	delete NextScene;

	return true;
}
