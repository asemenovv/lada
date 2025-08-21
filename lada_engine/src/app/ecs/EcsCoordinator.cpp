#include "EcsCoordinator.h"

namespace Lada {
    EcsCoordinator::EcsCoordinator() {
        mComponentManager = std::make_unique<ComponentManager>();
        mEntityManager = std::make_unique<EntityManager>();
        mSystemManager = std::make_unique<SystemManager>();
    }

    Entity EcsCoordinator::CreateEntity() const {
        return mEntityManager->CreateEntity();
    }

    void EcsCoordinator::DestroyEntity(const Entity entity) const {
        mEntityManager->DestroyEntity(entity);
        mComponentManager->EntityDestroyed(entity);
        mSystemManager->EntityDestroyed(entity);
    }

    template <typename T>
    void EcsCoordinator::RegisterComponent() const {
        mComponentManager->RegisterComponent<T>();
    }

    template <typename T>
    void EcsCoordinator::AddComponent(const Entity entity, T component) {
        mComponentManager->AddComponent<T>(entity, component);

        auto signature = mEntityManager->GetSignature(entity);
        signature.set(mComponentManager->GetComponentType<T>(), true);
        mEntityManager->SetSignature(entity, signature);

        mSystemManager->EntitySignatureChanged(entity, signature);
    }

    template <typename T>
    void EcsCoordinator::RemoveComponent(const Entity entity) const {
        mComponentManager->RemoveComponent<T>(entity);

        auto signature = mEntityManager->GetSignature(entity);
        signature.set(mComponentManager->GetComponentType<T>(), false);
        mEntityManager->SetSignature(entity, signature);

        mSystemManager->EntitySignatureChanged(entity, signature);
    }

    template <typename T>
    T& EcsCoordinator::GetComponent(const Entity entity) {
        return mComponentManager->GetComponent<T>(entity);
    }

    template <typename T>
    ComponentType EcsCoordinator::GetComponentType() const {
        return mComponentManager->GetComponentType<T>();
    }

    template <typename T>
    std::shared_ptr<T> EcsCoordinator::RegisterSystem() {
        return mSystemManager->RegisterSystem<T>();
    }

    template <typename T>
    void EcsCoordinator::SetSystemSignature(const Signature signature) const {
        mSystemManager->SetSignature<T>(signature);
    }
}
