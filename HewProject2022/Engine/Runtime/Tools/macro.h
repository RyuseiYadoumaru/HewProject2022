//*****************************************************************************
//!	@file	Engine/Runtime/Tools/macro.h
//!	@brief	
//!	@note	�}�N����`
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once


/****	�|�C���^�Ƀf���[�g����	****/
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

/****	�A���C�������g	****/
#define ALIGN16 _declspec(align(16))
