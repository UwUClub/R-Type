#include "ConfigReader.hpp"
#include <fstream>
#include "Values.hpp"

void ConfigReader::loadConfig()
{
    std::ifstream playerFile(CONFIG_PATH + CONFIG_PLAYER);
    _player = json::parse(playerFile);
    std::ifstream physicsFile(CONFIG_PATH + CONFIG_PHYSICS);
    _physics = json::parse(physicsFile);
}

json &ConfigReader::getPlayer()
{
    return _player;
}

json &ConfigReader::getPhysics()
{
    return _physics;
}
