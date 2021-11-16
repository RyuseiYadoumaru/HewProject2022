//*****************************************************************************
//!	@file	Engine/Runtime/Tools/FileSystem.cpp
//!	@brief	
//!	@note	ファイル操作の便利関数をまとめたクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "FileSystem.h"
#include "Log.h"
#include <Windows.h>
#include <stdexcept>

//==============================================================================
//!	@fn		Instance
//!	@brief	ファイルシステムインスタンス取得
//!	@param	
//!	@retval	インスタンス
//==============================================================================
FileSystem* FileSystem::Instance()
{
	static FileSystem Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		GetFileName
//!	@brief	ファイルの名前取得
//!	@param	ファイルパス
//!	@retval	ファイル名
//==============================================================================
std::string FileSystem::GetFileName(const char* FilePath)
{
	std::string filepath(FilePath);
	std::string filename;
	int Index = filepath.find_last_of("/");

	filename = filepath.substr(Index + 1);

	return filename;
}

//==============================================================================
//!	@fn		GetFileName_NotExt
//!	@brief	ファイルの名前取得
//!	@param	ファイルパス
//!	@retval	ファイル名
//==============================================================================
std::string FileSystem::GetFileName_NotExt(const char * FilePath)
{
	std::string filepath(FilePath);
	std::string filename;
	int Index = filepath.find_last_of("/");
	int Length = filepath.find_last_of(".");
	Length = Length - (Index + 1);
	filename = filepath.substr(Index + 1, Length);

	return filename;
}

//==============================================================================
//!	@fn		GetFileExt
//!	@brief	ファイル拡張子取得
//!	@param	ファイル名
//!	@retval	拡張子
//==============================================================================
std::string FileSystem::GetFileExt(const char* FileName)
{
	std::string filename(FileName);
	std::string extname;

	int Index = filename.find_last_of(".");
	extname = filename.substr(Index + 1, filename.size() - Index);

	return extname;
}

//==============================================================================
//!	@fn		GetImageSize
//!	@brief	画像サイズを取得
//!	@param	ファイルパス
//!	@retval	画像サイズ
//==============================================================================
XMFLOAT2 FileSystem::GetImageSize(std::string FilePath)
{
	XMFLOAT2 Size = { 0.0f, 0.0f };
	unsigned char num[8];
	float Width = 0.0f;
	float Height = 0.0f;
#pragma warning(suppress : 4996)
	FILE* fp = fopen(FilePath.c_str(), "rb");

	if (fp == NULL)
	{
		Log::LogError("画像サイズの取得に失敗しました");
		return Size;
	}

	if (GetFileExt(FilePath.c_str()) == "png")
	{
		fseek(fp, 16L, SEEK_SET);
		fread(num, sizeof(int), 2, fp);
		Width = num[0] * (float)pow(2, 24) + num[1] * (float)pow(2, 16) + num[2] * (float)pow(2, 8) + num[3];
		Height = num[4] * (float)pow(2, 24) + num[5] * (float)pow(2, 16) + num[6] * (float)pow(2, 8) + num[7];

	}

	Size.x = Width;
	Size.y = Height;

	fclose(fp);

	return Size;
}
//==============================================================================
//!	@fn		SearchImageFilePath
//!	@brief	フォルダ内の画像のパスを全て出力
//!	@param	フォルダパス
//!	@retval	ファイルパス一覧
//==============================================================================
std::vector<std::string> FileSystem::SearchImageFilePath(std::string FolderPath)
{
	std::vector<std::string> Path;

	HANDLE hFind;
	WIN32_FIND_DATA win32fd;

	std::string ext[2] = { "png" ,"jpg" };

	for (int i = 0; i < 2; i++)
	{
		std::string SearchName = FolderPath + "*." + ext[i];
		hFind = FindFirstFile(SearchName.c_str(), &win32fd);

		if (hFind == INVALID_HANDLE_VALUE) continue;

		do
		{
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {}

			else
			{
				Path.push_back(FolderPath + win32fd.cFileName);
			}

		} while (FindNextFile(hFind, &win32fd));

		FindClose(hFind);
	}

	return Path;
}
