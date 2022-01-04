#pragma once
#include "ydmEngine.h"
using Create::Actor;

/****	îwåi	****/
class BackGround : public Actor
{
public:
	BackGround(string in_Name);
	bool Start() override;
};

typedef BackGround LayerFront;
typedef BackGround LayerBack;


