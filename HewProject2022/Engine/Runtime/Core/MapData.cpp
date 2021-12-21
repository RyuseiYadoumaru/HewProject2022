//*****************************************************************************
//!	@file	Engime/Runtime/Core/MapData.cpp
//!	@brief	
//!	@note	�}�b�v�f�[�^�N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "MapData.h"
#include<iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include "../Tools/Log.h"
#include "../../../Tile.h"

using namespace std;
//==============================================================================
//!	@fn		Load
//!	@brief�@�}�b�v�f�[�^���[�h
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool MapData::Load(std::string in_FileName)
{
	string F_Name = "assets/MapData/" + in_FileName + ".csv";
	string line, one;

	ifstream ifs(F_Name);
	if (!ifs)
	{
		Log::LogError("�}�b�v�f�[�^�t�@�C����������܂���I");
		return false;

	}
	int x = 0, y = 0;
	/*	�s�ǂݍ���	*/
	while (getline(ifs, line, '\n'))
	{
		Map.push_back(vector<char>());

		//1�s�̒l��istringstream�ɕϊ�
		istringstream stream(line);
		while (getline(stream, one, ','))
		{

			if (one == "NB")
			{
				Map[y].push_back(NB);
			}
			else if (one == "C1")
			{
				Map[y].push_back(C1);
			}
			else if (one == "C2")
			{
				Map[y].push_back(C2);

			}
			else if (one == "C3")
			{
				Map[y].push_back(C3);

			}
			else if (one == "GR")
			{
				Map[y].push_back(GR);

			}
			else if (one == "NO")
			{
				Map[y].push_back(NO);

			}
			else
			{
				Map[y].push_back(NO);
			}

		}
		y++;
	}

	Size.x = Map[0].size();
	Size.y = Map.size();


	return true;
}

//==============================================================================
//!	@fn		Set
//!	@brief�@�}�b�v�f�[�^�Z�b�g
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool MapData::Set(MapData& in_MapData)
{
	Map = *in_MapData.GetMapData();
	Size.x = in_MapData.GetSize().x;
	Size.y = in_MapData.GetSize().y;
	return true;
}
