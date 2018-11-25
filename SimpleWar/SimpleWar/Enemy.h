//***************************************************************************************
// Enemy.h by Cobalt Sato.
//***************************************************************************************
#pragma once
using namespace DirectX;
#include "CollisionEngine.h"
class Enemy : public CollisionEngine::GameObject {
public:
	Enemy() {};
	//Enemy(const Enemy& rhs);
	//Enemy& operator=(const Enemy& rhs);
	//void RunAI() {};
	
protected:
	int mHitPoint;
	
};
