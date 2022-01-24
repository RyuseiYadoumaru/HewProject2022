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


			//移動ブロック
			else if (one == "MB1")
			{
				Map[y].push_back(MB1);
			}

			else if (one == "MB2")
			{
				Map[y].push_back(MB2);
			}

			else if (one == "MB3")
			{
				Map[y].push_back(MB3);
			}

			else if (one == "MB4")
			{
				Map[y].push_back(MB4);
			}

			else if (one == "MB5")
			{
				Map[y].push_back(MB5);
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
