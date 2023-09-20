#include <iostream>
#include <memory>
#include "ResourcesManager.hpp"

int &load(std::string &val)
{
    std::cout << "load" << std::endl;
    return *(new int(42));
}

std::string &load2(std::string &val)
{
    std::cout << "load2" << std::endl;
    return *(new std::string("4222"));
}

int main()
{
    auto &rm = ECS::Core::ResourcesManager::getInstance();

    std::string path = "test";
    std::string path2 = "test2";

    auto &ret = rm.loadRessource<int>(path, load);
    auto &ret2 = rm.loadRessource<std::string>(path2, load2);

    std::cout << ret << std::endl;
    std::cout << ret2 << std::endl;

    auto &get = rm.getRessource<int>(path);
    auto &get2 = rm.getRessource<std::string>(path2);

    std::cout << get << std::endl;
    std::cout << get2 << std::endl;

    return 0;
}