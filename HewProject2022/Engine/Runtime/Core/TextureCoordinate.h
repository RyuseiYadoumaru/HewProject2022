//*****************************************************************************
//!	@file	Engine/Runtime/Core/TextureCoordinate.h
//!	@brief	
//!	@note	UV���W
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once


class TextureCoordinate
{
public:
	TextureCoordinate() {
		/*	�T�C�Y	*/
		SizeX = 1.0f; SizeY = 1.0f;
		/*	UV���W	*/
		LeftU = 0.0f; RightU = LeftU + SizeX;
		TopV = 0.0f; ButtomV = TopV + SizeY;
	}
	TextureCoordinate(float in_SizeX, float in_SizeY) {
		/*	�T�C�Y	*/
		SizeX = in_SizeX; SizeY = in_SizeY;

		/*	UV���W	*/
		LeftU = 0.0f; RightU = LeftU + SizeX;
		TopV = 0.0f; ButtomV = TopV + SizeY;
	}

	TextureCoordinate(float in_SizeX, float in_SizeY,
		float in_U, float in_V) {
		/*	�T�C�Y	*/
		SizeX = in_SizeX; SizeY = in_SizeY;

		/*	UV���W	*/
		LeftU = in_U * SizeX; RightU = LeftU + SizeX;
		TopV = in_V * SizeY; ButtomV = TopV + SizeY;

	}

public:
	void SetSize(float in_SizeX, float in_SizeY) {
		/*	�T�C�Y	*/
		SizeX = in_SizeX; SizeY = in_SizeY;
		/*	UV���W	*/
		LeftU = 0 * SizeX; RightU = LeftU + SizeX;
		TopV = 0 * SizeY; ButtomV = TopV + SizeY;
	}


	void SetPattarn(float in_U, float in_V) {
		/*	UV���W	*/
		LeftU = in_U * SizeX; RightU = LeftU + SizeX;
		TopV = in_V * SizeY; ButtomV = TopV + SizeY;
	}

	void SetTiling(float in_UTiling, float in_VTiling) {
		LeftU = in_UTiling; RightU = LeftU + SizeX;
		TopV = in_VTiling; ButtomV = TopV + SizeY;

	}

public:
	float LeftU;
	float RightU;
	float TopV;
	float ButtomV;

private:
	float SizeX;
	float SizeY;
};

