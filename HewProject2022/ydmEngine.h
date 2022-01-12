//*****************************************************************************
//!	@file	ydmEngine.h
//!	@brief	
//!	@note	ydmEngine
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once

//==============================================================================
//!	@region	Game
//!	@brief	�Q�[�����
//!	@note		
//==============================================================================
#include "StageInfo.h"

//==============================================================================
//!	@region	Runtime
//!	@brief	�����^�C��
//!	@note		
//==============================================================================
#include "Engine/Runtime/Application.h"

//==============================================================================
//!	@region	GameEngine
//!	@brief	�Q�[���G���W��
//!	@note	using GameEngine::�Ŏg�p��	
//==============================================================================
#include "Engine/Component/SpriteRenderer.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component//Physics/BoxCollider2D.h"
#include "Engine/Component/Physics/Rigidbody2d.h"
#include "Engine/Component/Miscellaneous/Animator.h"
#include "Engine/Component/Miscellaneous/ParticleSystem.h"
#include "Engine/Data/DataArray.h"
#include "Engine/Input/Input.h"
#include "Engine/SceneManager/SceneManager.h"
#include "Engine/Runtime/Sound/Sound.h"
#include "Engine/Runtime/Core/TagList.h"
#include "Engine/Timer/GameTimer.h"

//==============================================================================
//!	@region	Math
//!	@brief	���w�f�[�^
//!	@note	using Math::�Ŏg�p��	
//==============================================================================
#include "Engine/Math/Vector3.h"
#include "Engine/Math/Vector2.h"
#include "Engine/Math/Vector.h"
#include "Engine/Math/CRect.h"
#include "Engine/Math/Color.h"

//==============================================================================
//!	@region	Create
//!	@brief	�I�u�W�F�N�g����
//!	@note	using Create::
//==============================================================================
#include "Game/GameObject/Camera.h"
#include "Engine/Create/GameObject.h"
#include "Engine/Create/Scene.h"
#include "Engine/Create/Animation.h"
#include "Engine/Create/AnimationController.h"
#include "Engine/Create/Particle.h"
#include "Game/GameObject/Actor.h"
#include "Game/GameObject/Character.h"
#include "Game/GameObject/Effect.h"

//==============================================================================
//!	@region	Tools
//!	@brief	�֗��N���X
//!	@note
//==============================================================================
#include "Engine/Runtime/Tools/FileSystem.h"
#include "Engine/Runtime/Tools/Log.h"
#include "Engine/Runtime/Tools/macro.h"
#include "Engine/Runtime/Tools/SystemTimer.h"
#include "Engine/Runtime/Graphics/Shader.h"

//==============================================================================
//!	@region	std
//!	@brief	�W�����C�u����
//!	@note	using std::
//==============================================================================
#include <string>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <memory>
#include <cmath>
#include <cstdlib>

//==============================================================================
//!	@region	C
//!	@brief	�W�����C�u����
//!	@note
//==============================================================================
#include<time.h>
#include<stdlib.h>


//==============================================================================
//!	@region	DirectX
//!	@brief	DirectX���C�u����
//!	@note	using DirectX::
//==============================================================================
#include <DirectXMath.h>

//==============================================================================
//!	@region	using namespace
//!	@brief	���O��Ԑ錾
//!	@note	�Œ�������g�p���Ȃ�
//==============================================================================
using namespace std;
using namespace GameEngine;
