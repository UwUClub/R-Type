# How To Use The ECS
## Contents
- [Introduction](#introduction)
- [ECS in the Engine](#ecs-in-the-engine)
- [Create a Component](#create-a-component)
- [Create a System](#create-a-system)
- [Add the Component to the World](#add-the-component-to-the-world)
- [Add the System to the World](#add-the-system-to-the-world)
- [Create an Entity](#create-an-entity)
- [Add a Component to an Entity](#add-a-component-to-an-entity)
- [Kill an Entity](#kill-an-entity)
- [Conclusion](#conclusion)


## Introduction
ECS stands for Entity Component System. It is a design pattern used in game development to organize entities (such as characters, objects, etc.) and their behaviors. In an ECS, entities are composed of one or more components, which define their properties and behaviors. Systems are then used to process the entities and their components, updating their state and behavior over time. This approach can make game development more modular and flexible, allowing for easier reuse of code and more efficient processing of game entities.

## ECS in the Engine
The ECS in the engine is a very simple implementation of the ECS design pattern. It is composed of three main parts: the `Entity`, the `Component`, and the `System`. The `Entity` is a simple container for `Component`s. The `Component` is a simple container for data. The `System` is a simple container for logic. The `System` is responsible for processing the `Component`s of an `Entity` and updating their state and behavior. The `System` is also responsible for adding and removing `Component`s from an `Entity`. The `System` is also responsible for adding and removing `Entity`s from the ECS.
Each `Component` is stored in a `SparseArray`, the index of each row in the array represent the `Entity`.
A `SparseArray` is an array containing the `Component`, it is a an array of *optional values*.
The `Components` are data's struct that can be registered in the `World`.
The `Systems` are functions that can be registered in the `World`, it need to have the component's type that it will process as template parameter.
The `World` is the main class of the ECS, it is the container of the `SparseArray` of `Components` and `Systems`.

## How to use the ECS
### Create a Component
To create a `Component`, you need to create a struct.
```cpp
// Here we create a simple Position component with two float
struct Position
{
    Position(float aX, float aY) : x(aX), y(aY) {}

    float x;
    float y;
};
// Here we create a simple HP component with two int
struct HP
{
    HP(int aHP) : hp(aHP), maxHp(aHP) {}

    int hp;
    int maxHp;
};
// Here we create a simple Damage component with an int
struct Damage
{
    Damage(int aDamage) : damage(aDamage) {}

    int damage;
};

```
### Create a System
To create a `System`, you need to create a function. (I recommend to use a static function in an abstract class)
```cpp
void updatePosition(ECS::SparseArray<Position> &aPositionArray)
{
    for (auto &position : aPositionArray)
    {
        // Check if the entity has a position
        if (!position.hasValue()) {
            continue;
        }
        // Update the position if one is found
        position.value().x += 1;
        position.value().y += 1;
    }
}

void updateHP(ECS::SparseArray<HP> &aHPArray, ECS::SparseArray<Damage> &aDamageArray)
{
    for (auto &hp : aHPArray)
    {
        // Check if the entity has a HP
        if (!hp.hasValue()) {
            continue;
        }
        // Check if the entity has a Damage
        if (!aDamageArray[hp.index()].hasValue()) {
            continue;
        }
        // Update the HP if one is found using the entity own damage (clearly made for example purpose)
        hp.value().hp -= aDamageArray[hp.index()].value().damage;
    }
}
```
### Add the Component to the World
To add a `Component` to the `World`, you need to call the `registerComponent` method of the `World` with the `Component` type as template parameter.
```cpp
int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Register the Position component
    world.registerComponent<Position>();
    // Register the HP component
    world.registerComponent<HP>();
    // Register the Damage component
    world.registerComponent<Damage>();
    return 0;
}
```
### Add the System to the World
To add a `System` to the `World`, you need to call the `registerSystem` method of the `World` with the `System` as parameter.
```cpp
int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Register the Position component
    world.registerComponent<Position>();
    // Register the HP component
    world.registerComponent<HP>();
    // Register the Damage component
    world.registerComponent<Damage>();

    // Register the updatePosition system
    world.registerSystem<Position>(updatePosition);
    // Register the updateHP system
    world.registerSystem<HP, Damage>(updateHP);
    return 0;
}
```
### Create an Entity
To create an `Entity`, you need to call the `createEntity` method of the `World`.
```cpp
int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Register the Position component
    world.registerComponent<Position>();
    // Register the HP component
    world.registerComponent<HP>();
    // Register the Damage component
    world.registerComponent<Damage>();

    // Register the updatePosition system
    world.registerSystem<Position>(updatePosition);
    // Register the updateHP system
    world.registerSystem<HP, Damage>(updateHP);

    // Create an entity
    std::size_t entity = world.createEntity();
    return 0;
}
```
### Add a Component to an Entity
## Using a created Component
To add a `Component` to an `Entity`, you can call the `insertAt` method of the `SparseArray` with the `Entity` and the `Component` as parameters.
```cpp
int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Register the Position component
    auto &positionSystem = world.registerComponent<Position>();
    // Register the HP component
    world.registerComponent<HP>();
    // Register the Damage component
    world.registerComponent<Damage>();

    // Register the updatePosition system
    world.registerSystem<Position>(updatePosition);
    // Register the updateHP system
    world.registerSystem<HP, Damage>(updateHP);

    // Create an entity
    std::size_t entity = world.createEntity();

    auto positionComponent = Position(0, 0);

    // Add a position to the entity
    positionSystem.insertAt(entity, positionComponent);
    return 0;
}
```
## Using a the world
To add a `Component` to an `Entity`, you can use `emplaceAt` method of the `World` with the `Component` as template parameter, the `Entity` and the data to create the `Component` as parameters.
```cpp
int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Register the Position component
    auto &positionSystem = world.registerComponent<Position>();
    // Register the HP component
    world.registerComponent<HP>();
    // Register the Damage component
    world.registerComponent<Damage>();

    // Register the updatePosition system
    world.registerSystem<Position>(updatePosition);
    // Register the updateHP system
    world.registerSystem<HP, Damage>(updateHP);

    // Create an entity
    std::size_t entity = world.createEntity();

    // Add a position to the entity
    world.emplaceEntityComponent<Position>(entity, 0, 0);
    return 0;
}
```

### Kill an Entity
To kill an `Entity`, you need to call the `killEntity` method of the `World` with the `Entity` as parameter.
It will automatically remove all the `Component`s of the `Entity` from the `World`.
```cpp
int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Register the Position component
    auto &positionSystem = world.registerComponent<Position>();
    // Register the HP component
    world.registerComponent<HP>();
    // Register the Damage component
    world.registerComponent<Damage>();

    // Register the updatePosition system
    world.registerSystem<Position>(updatePosition);
    // Register the updateHP system
    world.registerSystem<HP, Damage>(updateHP);

    // Create an entity
    std::size_t entity = world.createEntity();

    // Add a position to the entity
    world.emplaceEntityComponent<Position>(entity, 0, 0);
    world.emplaceEntityComponent<HP>(entity, 100);
    world.emplaceEntityComponent<Damage>(entity, 10);

    // Kill the entity
    world.killEntity(entity);
    return 0;
}
```
## Conclusion
This is just some example of how to use the ECS, you can use it as you want.
Read the full documentation of the ECS on our [website](https://uwuclub.github.io/R-Type/).
