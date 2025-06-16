#pragma once

namespace SumEngine
{
    class GameObject;
}

namespace SumEngine::Physics
{
    struct RaycastHit
    {
        btVector3 point;
        btVector3 normal;
        SumEngine::GameObject* gameObject = nullptr;
        const btCollisionObject* hitObject = nullptr;
        float distance = 0.0f;
        bool hit = false;
    };

    class Raycast
    {
    public:
        Raycast();
        ~Raycast();

        bool Cast(const SumEngine::Math::Vector3& origin, const SumEngine::Math::Vector3& direction, float maxDistance);
        void DebugUI();

        RaycastHit* GetRaycastResult();

    private:
        RaycastHit* mRaycastHit = nullptr;
        SumEngine::Math::Vector3 mOrigin;
        SumEngine::Math::Vector3 mDirection;
        float mMaxDistance = 0.0f;
    };
}