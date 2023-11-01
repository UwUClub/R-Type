# How to use the music plugin
## Contents

- [Plug the music](#Plug-the-music)
- [Create the music component](#create-music-component)
- [Stop a music](#stop-a-music)
- [Pause a music](#pause-a-music)
- [Check if a music is playing](#check-if-is-playing)

## Plug the music
To plug the music it's very simple, all you have to do is, in your main add these lines:

```c++
#include "EwECS/music/music.hpp

ECS::musicPlugin musicPlugin;

musicPlugin.plug(world, assetManager);
```

And voila! Your music is now plug and is ready to be used.

## Create a music component

Now that the music is pluged to your project, you need to create a music component linked to an entity for exemple:

```c++
auto idx = AddEntity::addEntity(ECS::Utils::Vector2f {0, 0},
            Component::Speed {BACKGROUND_SPEED},
            Component::TypeEntity {false, false, false, false, false, false, true},
            Component::LoadedSprite {"config/background.json"}, Component::HitBox {}, Component::IsAlive {false, 0});
                    
                    
world.emplaceEntityComponent<Component::MusicComponent>(idx, "assets/sounds/rtype.mp3", 100, true);
```

in this exemple we have created an entity "missile" with all the attributes she need and with this line:

```c++
world.emplaceEntityComponent<Component::musicComponent>(entity_id, "assets/sounds/rtype.mp3", 100, true);
```

we have linked a song to this entity, so every time the entity "missile" is created, a music is going to be played in our case: "rtype.mp3"

the parameters of the music component are:
- the path of the music
- the volume of the music
- a boolean to know if the music is looping or not

## Stop a music
To stop a music you just have to change the "_state" of the music component to STOP:

```c++
world.getComponent<Component::musicComponent>(entity_id)._state = Component::musicComponent::State::STOP;
```

## Pause a music
To pause a music you just have to change the "_state" of the music component to PAUSE:

```c++
world.getComponent<Component::musicComponent>(entity_id)._state = Component::musicComponent::State::PAUSE;
```

## Check if is playing
To check if a music is playing you can use the function "isPlaying" of the music component:

```c++
world.getComponent<Component::musicComponent>(entity_id).isPlaying();
```
it will return a boolean, true if the music is playing, false if not.
