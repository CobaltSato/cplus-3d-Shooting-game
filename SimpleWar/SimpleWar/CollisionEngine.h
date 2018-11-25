//***************************************************************************************
// CollisionEngine.cpp by Cobalt Sato.
//  provides the class GameObject with collision detection functionality.
//***************************************************************************************
#pragma once 
#ifndef _COLLISION_H
#define _COLLISION_H

#include "../../Common/d3dUtil.h"
using namespace DirectX;
namespace CollisionEngine {
	class GameObject {
	public:
		GameObject() {};
		~GameObject() {};
		//GameObject(const GameObject& rhs);
		//GameObject& operator=(const GameObject& rhs);
	protected:
		float mPosX=0.0f;
		float mPosY=0.0f;
		float mPosZ=0.0f;
		float mCenterX=0.0f;
		float mCenterY=0.0f;
		float mCenterZ=0.0f;
		BoundingBox mBoundingBox;
		BoundingSphere mBoundingSphere;
		BoundingFrustum mBoundingFrustum;
		BoundingOrientedBox mBoundingOrientedBox;

		// we should update center position before collision detection
		void updateCenter() {
			XMFLOAT3 vCenterf(
				mCenterX + mPosX,
				mCenterY + mPosY,
				mCenterZ + mPosZ
			);
			XMVECTOR vCenter = XMLoadFloat3(&vCenterf);
			XMStoreFloat3(&mBoundingBox.Center, vCenter);
			XMStoreFloat3(&mBoundingSphere.Center, vCenter);
			XMStoreFloat3(&mBoundingOrientedBox.Center, vCenter);
		}

		// collision detection
		// in assumptions that this object has bounding box.
		bool boxIntersect(GameObject other) {
			switch (other.mIBounding)
			{
			case IS_BOX:
				return mBoundingBox.Intersects(other.mBoundingBox);
			case IS_SPHERE:
				return mBoundingBox.Intersects(other.mBoundingSphere);
			}
			return false;
		}

		// collision detection
		// in assumptions that this object has bounding sphere.
		bool sphereIntersect(GameObject other) {
			switch (other.mIBounding)
			{
			case IS_BOX:
				return mBoundingSphere.Intersects(other.mBoundingBox);
			case IS_SPHERE:
				return mBoundingSphere.Intersects(other.mBoundingSphere);
			}
			return false;
		}

		enum {
			IS_BOX,
			IS_SPHERE,
			IS_FRUSTUM,
			IS_ORIENTED_BOX
		} mIBounding;

	public:
		void setPosition(float x, float y, float z) {
			mPosX = x;
			mPosY = y;
			mPosZ = z;
		}

		// overloaded method to set bounding data structure.
		void setBounding(BoundingBox bb) {
			mIBounding = IS_BOX;
			mCenterX = bb.Center.x;
			mCenterY = bb.Center.y;
			mCenterZ = bb.Center.z;
			mBoundingBox = bb;
		};
		void setBounding(const BoundingSphere &bs) {
			mIBounding = IS_SPHERE;
			mCenterX = bs.Center.x;
			mCenterY = bs.Center.y;
			mCenterZ = bs.Center.z;
			mBoundingSphere = bs;
		};
		void setBounding(const BoundingFrustum &bf) {
			mIBounding = IS_FRUSTUM;
			mCenterX = 0;
			mCenterY = 0;
			mCenterZ = 0;
			mBoundingFrustum = bf;
		};
		void setBounding(const BoundingOrientedBox &bob) {
			mIBounding = IS_ORIENTED_BOX;
			mCenterX = bob.Center.x;
			mCenterY = bob.Center.y;
			mCenterZ = bob.Center.z;
			mBoundingOrientedBox = bob;
		};

		bool intersect(GameObject other) {
			updateCenter();
			other.updateCenter();
			switch (mIBounding) {
			case IS_BOX:
				return boxIntersect(other);
			case IS_SPHERE:
				return sphereIntersect(other);
				//case IS_FRUSTUM:
				//case IS_ORIENTED_BOX:
			};
			return false;
		}
	};
};
#endif