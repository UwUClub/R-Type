# How to use the sound plugin
## Contents

- [Plug the Sound](#Plug-the-sound)
- [Create the sound component](#create-sound-component)
- [Stop a sound](#stop-a-sound)
- [Pause a sound](#pause-a-sound)
- [Check if a sound is playing](#check-if-is-playing)

## Plug the sound
To plug the sound it's very simple, all you have to do is, in your main add these lines:

```c++
#include "EwECS/Sound/Sound.hpp

ECS::SoundPlugin soundPlugin;

soundPlugin.plug(world, assetManager);
```

And voila! Your sound is now plug and is ready to be used.

## Create a sound component

Now that the Sound is pluged to your project, you need to create a sound component linked to an entity for exemple:

```c++
auto entity_id = AddEntity::addEntity(
                ECS::Utils::Vector2f {payload.posX, payload.posY}, Component::Speed {BULLET_SPEED},
                Component::TypeEntity {false, false, false, true, false,false, false, payload.bulletId, false},
                Component::LoadedSprite {"config/missiles.json"},
                Component::HitBox {BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT}, Component::IsAlive {false, 0});
                

world.emplaceEntityComponent<Component::SoundComponent>(entity_id, "assets/sounds/pew.mp3", 40, false);
```

in this exemple we have created an entity "missile" with all the attributes she need and with this line:

```c++
world.emplaceEntityComponent<Component::SoundComponent>(entity_id, "assets/sounds/pew.mp3", 40, false);
```

we have linked a song to this entity, so every time the entity "missile" is created, a sound is going to be played in our case: "pew.mp3"

the parameters of the sound component are:
- the path of the sound
- the volume of the sound
- a boolean to know if the sound is looping or not

## Stop a sound
To stop a sound you just have to change the "_state" of the sound component to STOP:

```c++
world.getComponent<Component::SoundComponent>(entity_id)._state = Component::SoundComponent::State::STOP;
```

## Pause a sound
To pause a sound you just have to change the "_state" of the sound component to PAUSE:

```c++
world.getComponent<Component::SoundComponent>(entity_id)._state = Component::SoundComponent::State::PAUSE;
```

## Check if is playing
To check if a sound is playing you can use the function "isPlaying" of the sound component:

```c++
world.getComponent<Component::SoundComponent>(entity_id).isPlaying();
```
it will return a boolean, true if the sound is playing, false if not.
