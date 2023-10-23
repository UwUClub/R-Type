#include "AddEntity.hpp"
#include "World.hpp"

size_t AddEntity::addEntity(ECS::Utils::Vector2f aPos, Component::Speed aSpeed, Component::TypeEntity aType,
                                   Component::LoadedSprite aSprite, Component::HitBox aHitBox,
                                   Component::IsAlive aIsAlive)
{
    ECS::Core::World &world = ECS::Core::World::getInstance();
    auto &vec = world.getComponent<ECS::Utils::Vector2f>();
    auto &spd = world.getComponent<Component::Speed>();
    auto &type = world.getComponent<Component::TypeEntity>();
    auto &sprite = world.getComponent<Component::LoadedSprite>();
    auto &hitbox = world.getComponent<Component::HitBox>();
    auto &isAlive = world.getComponent<Component::IsAlive>();
    const size_t idx = world.createEntity();

    vec.insertAt(idx, aPos);
    spd.insertAt(idx, aSpeed);
    type.insertAt(idx, aType);
    sprite.insertAt(idx, aSprite);
    hitbox.insertAt(idx, aHitBox);
    isAlive.insertAt(idx, aIsAlive);
    return idx;
}