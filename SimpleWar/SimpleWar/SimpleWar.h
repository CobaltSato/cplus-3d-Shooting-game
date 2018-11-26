//***************************************************************************************
// SimpleWar.h by Cobalt Sato.
//***************************************************************************************
#pragma once

#ifndef MY_GAME_H
#define MY_GAME_H
#include "GameEngine.h"
namespace FieldNS{
	float MIN_X = -9.5f;
	float MAX_X = 9.5f;
	float MIN_Y = 0.0f;
	float MAX_Y = 6.0f;
	float MIN_Z = -12.0f;
	float MAX_Z = 16.5f;
};
class SimpleWar : public GameEngine {
public:
	SimpleWar(HINSTANCE hInstance)
		:GameEngine(hInstance)
	{
	};
	SimpleWar(const SimpleWar& rhs) = delete;
	SimpleWar& operator=(const SimpleWar& rhs) = delete;
	~SimpleWar() {};
	virtual void OnKeyboardInput(const GameTimer& gt) override;
	virtual void OnMouseMove(WPARAM btnState, int x, int y);
    virtual bool Initialize()override;
    virtual void Update(const GameTimer& gt)override;
    void LoadTextures()override;
	void BuildSkullGeometry();
	virtual void BuildGeometry()override {
		BuildSkullGeometry();
		BuildShapeGeometry();
	};
	virtual void BuildMaterials()override;
	virtual void BuildRenderItems()override;
	virtual void BuildDescriptorHeaps()override;
	virtual void BuildRootSignature()override;
	virtual void CreateRtvAndDsvDescriptorHeaps()override;
private:
	int mCurrCameraDir = 1; // tracking camera direction
	float mExplodeDelay = 5.1f;
	float mPlayerX = 0.0f;
	float mPlayerY = 1.5f;
	float mPlayerZ = -2.0f;
	float mPlayerTheta = 0.0f;
	int mPlayerRenderIdx = 2;
	const float mCollisionDiscount = 0.85f;

	//Enemy mEnemySkull;
	CollisionEngine::GameObject mEnemySkull;
	CollisionEngine::GameObject mPlayer; // TODO: ->mPlayer
};
#endif
