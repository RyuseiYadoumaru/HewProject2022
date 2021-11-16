//*****************************************************************************
//!	@file	ydmEngine.h
//!	@brief	
//!	@note	ydmEngine
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once

//==============================================================================
//!	@region	GameEngine
//!	@brief	ゲームエンジン
//!	@note	using GameEngine::で使用可	
//==============================================================================
#include "Engine/Component/SpriteRenderer.h"
#include "Engine/Component/Transform.h"
#include "Engine/Data/DataArray.h"
#include "Engine/Input/Input.h"
#include "Engine/SceneManager/SceneManager.h"

//==============================================================================
//!	@region	Math
//!	@brief	数学データ
//!	@note	using Math::で使用可	
//==============================================================================
#include "Engine/Math/Vector3.h"
#include "Engine/Math/Vector2.h"
#include "Engine/Math/CRect.h"
#include "Engine/Math/Color.h"

//==============================================================================
//!	@region	Create
//!	@brief	オブジェクト生成
//!	@note	using Create::
//==============================================================================
#include "Game/GameObject/Camera.h"
#include "Engine/Create/GameObject.h"
#include "Engine/Create/Scene.h"
#include "Game/GameObject/Actor.h"
#include "Game/GameObject/Character.h"

//==============================================================================
//!	@region	Tools
//!	@brief	便利クラス
//!	@note
//==============================================================================
#include "Engine/Runtime/Tools/FileSystem.h"
#include "Engine/Runtime/Tools/Log.h"
#include "Engine/Runtime/Tools/macro.h"
#include "Engine/Runtime/Tools/SystemTimer.h"
#include "Engine/Runtime/Graphics/Shader.h"

//==============================================================================
//!	@region	std
//!	@brief	標準ライブラリ
//!	@note	using std::
//==============================================================================
#include <string>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <memory>

//==============================================================================
//!	@region	DirectX
//!	@brief	DirectXライブラリ
//!	@note	using DirectX::
//==============================================================================
#include <DirectXMath.h>

//==============================================================================
//!	@region	using namespace
//!	@brief	名前空間宣言
//!	@note	最低限しか使用しない
//==============================================================================
using namespace std;
using namespace GameEngine;
