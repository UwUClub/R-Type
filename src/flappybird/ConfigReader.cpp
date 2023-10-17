#include "ConfigReader.hpp"
#include <fstream>
#include <iostream>
#include "Values.hpp"

void ConfigReader::loadConfig()
{
    std::ifstream f(CONFIG_PATH);
    _data = json::parse(f);
}

json &ConfigReader::get()
{
    return _data;
}
