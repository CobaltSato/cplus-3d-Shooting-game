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
	void LoadTextures()override;
	void BuildSkullGeometry();

	// framework methods
	virtual void OnKeyboardInput(const GameTimer& gt) override;
	virtual void OnMouseMove(WPARAM btnState, int x, int y);
	virtual bool Initialize()override;
	virtual void Update(const GameTimer& gt)override;
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
	float mPlayerX = 0.0f;
	float mPlayerY = 1.5f;
	float mPlayerZ = -2.0f;
	float mPlayerTheta = 0.0f;
	int mPlayerRenderIdx = 2;
	const float PLAYER_RADIUS = 1.5f;

	Enemy mEnemySkull;
	//CollisionEngine::GameObject mEnemySkull;
	//CollisionEngine::GameObject mPlayer;
	Player mPlayer;

	int mCurrCameraDir = 1; // tracking camera direction
	const float mCollisionDiscount = 0.85f;
	float mExplodeDelay_secs = 5.1f;

	void setExploSound() {
		if (mExplodeDelay_secs > 5.0f)
			mExplodeDelay_secs = 0.5f;
		//testLife--;
		//if (testLife < 0) testLife = 0;
	}
	void UpdateDashboard();
};
#endif
