#include "Precompiled.h"
#include "Raycast.h"

#include "PhysicsWorld.h"

using namespace SumEngine;
using namespace SumEngine::Math;
using namespace SumEngine::Physics;
using namespace SumEngine::Graphics;

Raycast::Raycast()
{
    mRaycastHit = new RaycastHit();
}

Raycast::~Raycast()
{
    delete(mRaycastHit);
    mRaycastHit = nullptr;
}

bool Raycast::Cast(const Vector3& origin, const Vector3& direction, float maxDistance)
{
    mOrigin = origin;
    mDirection = direction;
    mMaxDistance = maxDistance;

    PhysicsWorld* physicsWorld = PhysicsWorld::Get();
    btDynamicsWorld* dynamicsWorld = physicsWorld->GetDynamicsWorld();

    btVector3 btOrigin = TobtVector3(origin);
    btVector3 btDirection = TobtVector3(direction);

    btVector3 to = btOrigin + btDirection.normalized() * maxDistance;

    btCollisionWorld::ClosestRayResultCallback rayCallback(btOrigin, to);
    dynamicsWorld->rayTest(btOrigin, to, rayCallback);

    if (rayCallback.hasHit())
    {
        const btCollisionObject* colObj = rayCallback.m_collisionObject;

        mRaycastHit->point = rayCallback.m_hitPointWorld;
        mRaycastHit->normal = rayCallback.m_hitNormalWorld;
        mRaycastHit->hitObject = colObj;
        rayCallback.m_collisionObject->getUserPointer();
        mRaycastHit->distance = (mRaycastHit->point - btOrigin).length();
        mRaycastHit->hit = true;
        mRaycastHit->gameObject = static_cast<GameObject*>(colObj->getUserPointer());
        return true;
    }

    return false;
}

void Raycast::DebugUI()
{
    SimpleDraw::AddLine(mOrigin, mDirection * mMaxDistance, Colors::Red);
}

RaycastHit* Raycast::GetRaycastResult()
{
    return mRaycastHit;
}
