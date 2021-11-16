//*****************************************************************************
//!	@file	Engine/Runtime/Tools/macro.h
//!	@brief	
//!	@note	マクロ定義
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once


/****	ポインタにデリートする	****/
#define SAFE_DELETE(value)	\
if(value != NULL){			\
	delete value;			\
	value = NULL;			\
}							\

#define SAFE_DELETE_ARRAY(value)	\
if(value != NULL){					\
	delete[] value;					\
	value = NULL					\
}									\

/****	アラインメント	****/
#define ALIGN16 _declspec(align(16))
