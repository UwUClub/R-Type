target_sources(client PRIVATE
        System+CreateBot.cpp
        System+UpdateBotPosition.cpp
        System+TriggerBotShoot.cpp
        System+BotHit.cpp
        System+TriggerBotDeath.cpp
        System+TriggerBotDisconnect.cpp
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
