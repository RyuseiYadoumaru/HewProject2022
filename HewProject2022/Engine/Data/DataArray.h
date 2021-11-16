//*****************************************************************************
//!	@file	Engine/Data/DataArray.h
//!	@brief	
//!	@note	ゲームで使用するデータをまとめたクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include "../Runtime/Core/Sprite.h"
#include "../Runtime/Core/vsShader.h"
#include "../Runtime/Core/psShader.h"

#include <map>
#include <vector>
#include <string>

namespace GameEngine
{
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

	};
}


