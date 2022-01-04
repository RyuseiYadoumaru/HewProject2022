//*****************************************************************************
//!	@file	Engine/Data/DataArray.h
//!	@brief	
//!	@note	�Q�[���Ŏg�p����f�[�^���܂Ƃ߂��N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "../Runtime/Core/Sprite.h"
#include "../Runtime/Core/vsShader.h"
#include "../Runtime/Core/psShader.h"
#include "../Runtime/Core/MapData.h"

#include <map>
#include <vector>
#include <string>

namespace GameEngine
{
	typedef std::vector<std::string> PATH_LIST;
	typedef const char* PATH_NAME;

	class DataArray
	{
	private:
		static std::map<std::string, Sprite> SpriteData;
		static std::map<std::string, vsShader> vsShaderData;
		static std::map<std::string, psShader> psShaderData;

	public:

		static DataArray* Instance();
		bool Init();

	public:
		static Sprite& GetSpriteData(std::string in_SpriteName);
		static vsShader& GetvsShader(std::string in_vsShaderName);
		static psShader& GetpsShader(std::string in_psShaderName);


	private:
		static PATH_LIST LoadAllImagePath(PATH_NAME in_FilePath);

	};
}


