//*****************************************************************************
//!	@file	Engine/Runtime/Tools/FileSystem.h
//!	@brief	
//!	@note	ファイルシステムクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#include <string>
#include <vector>
#include <DirectXMath.h>

using DirectX::XMFLOAT2;

#define DATA_FOLDER		(true)
#define DATA_FILE		(false)

class FileSystem
{
public:

	static FileSystem* Instance();

	static std::string GetFileName(const char* FilePath);
	static std::string GetFileName_NotExt(const char* FilePath);
	static std::string GetFileExt(const char* FileName);
	static bool JudgeFolderOrFile(std::string DataName);

	static XMFLOAT2 GetImageSize(std::string FilePath);
	static std::vector<std::string> SearchImageFilePath(std::string FolderPath);
	//GetImageSizeFunctoin
};

