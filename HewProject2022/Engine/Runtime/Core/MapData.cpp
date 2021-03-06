//*****************************************************************************
//!	@file	Engime/Runtime/Core/MapData.cpp
//!	@brief	
//!	@note	マップデータクラス
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
//!	@brief　マップデータロード
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool MapData::Load(std::string in_FileName)
{
	string F_Name = "assets/MapData/" + in_FileName + ".csv";
	string line, one;

	ifstream ifs(F_Name);
	if (!ifs)
	{
		Log::LogError("マップデータファイルが見つかりません！");
		return false;

	}
	int x = 0, y = 0;
	/*	行読み込み	*/
	while (getline(ifs, line, '\n'))
	{
		Map.push_back(vector<char>());

		//1行の値をistringstreamに変換
		istringstream stream(line);
		while (getline(stream, one, ','))
		{

			if (one == "NB")
			{
				Map[y].push_back(NB);
			}
			else if (one == "NO")
			{
				Map[y].push_back(NO);

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
			else if (one == "C4")
			{
				Map[y].push_back(C4);

			}
			else if (one == "GR")
			{
				Map[y].push_back(GR);

			}
			else if (one == "NB2")
			{
				Map[y].push_back(NB2);

			}
			else if (one == "NB3")
			{
				Map[y].push_back(NB3);

			}
			else if (one == "NB4")
			{
				Map[y].push_back(NB4);

			}
			else if (one == "NB5")
			{
				Map[y].push_back(NB5);

			}
			else if (one == "NB6")
			{
				Map[y].push_back(NB6);

			}
			else if (one == "NB7")
			{
				Map[y].push_back(NB7);

			}
			else if (one == "NB8")
			{
				Map[y].push_back(NB8);

			}
			else if (one == "NB9")
			{
				Map[y].push_back(NB9);

			}
			else if (one == "NB10")
			{
				Map[y].push_back(NB10);

			}


			else if (one == "LC1")
			{
				Map[y].push_back(LC1);

			}
			else if (one == "LC2")
			{
				Map[y].push_back(LC2);

			}
			else if (one == "LC3")
			{
				Map[y].push_back(LC3);

			}
			else if (one == "LC4")
			{
				Map[y].push_back(LC4);

			}

			//入れ替えブロック(真)
			//3色変化
			else if (one == "CR3")
			{
				Map[y].push_back(CR3);

			}
			else if (one == "CB3")
			{
				Map[y].push_back(CB3);

			}
			else if (one == "CG3")
			{
				Map[y].push_back(CG3);

			}
			//4色変化
			else if (one == "CR4")
			{
				Map[y].push_back(CR4);

			}
			else if (one == "CB4")
			{
				Map[y].push_back(CB4);

			}
			else if (one == "CG4")
			{
				Map[y].push_back(CG4);

			}
			else if (one == "CP4")
			{
				Map[y].push_back(CP4);

			}

			//星
			else if (one == "ST")
			{
				Map[y].push_back(ST);

			}
			else
			{
				Map[y].push_back(NO);
			}

		}
		y++;
	}

	Size.x = (float)Map[0].size();
	Size.y = (float)Map.size();

	return true;
}

//==============================================================================
//!	@fn		Set
//!	@brief　マップデータセット
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool MapData::Set(MapData& in_MapData)
{
	Map = *in_MapData.GetMapData();
	Size.x = in_MapData.GetSize().x;
	Size.y = in_MapData.GetSize().y;
	return true;
}
