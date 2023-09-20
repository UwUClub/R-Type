/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** RessourcesManager
*/

#ifndef RESSOURCESMANAGER_HPP_
#define RESSOURCESMANAGER_HPP_

#include <any>
#include <functional>
#include <memory>
#include <string>
#include <typeindex>
#include <utility>
#include <unordered_map>

namespace ECS::Core {
    class ResourcesManager
    {
        public:
            static ResourcesManager &getInstance()
            {
                static ResourcesManager instance;
                return instance;
            }

            ResourcesManager(const ResourcesManager &aOther) = default;
            ResourcesManager(ResourcesManager &&aOther) noexcept = default;

            ResourcesManager &operator=(const ResourcesManager &aOther) = default;
            ResourcesManager &operator=(ResourcesManager &&aOther) noexcept = default;

            //-------------- PUBLIC METHODS --------------//
            template<class Resource>
            Resource &loadRessource(std::string &aPath, std::function<Resource &(std::string &path)> aLoader)
            {
                if (_resources.find(std::type_index(typeid(Resource))) == _resources.cend()) {
                    _resources[std::type_index(typeid(Resource))] = std::unordered_map<std::string, std::any>();
                }
                if (_resources[std::type_index(typeid(Resource))].find(aPath)
                    == _resources[std::type_index(typeid(Resource))].cend()) {
                    _resources[std::type_index(typeid(Resource))][aPath] = std::any(aLoader(aPath));
                }
                return std::any_cast<Resource &>(_resources[std::type_index(typeid(Resource))][aPath]);
            }

            template<class Resource>
            Resource &getRessource(std::string &aPath)
            {
                if (_resources.find(std::type_index(typeid(Resource))) == _resources.cend()) {
                    throw std::runtime_error("Ressource not found");
                }
                if (_resources[std::type_index(typeid(Resource))].find(aPath)
                    == _resources[std::type_index(typeid(Resource))].cend()) {
                    throw std::runtime_error("Ressource not found");
                }
                return std::any_cast<Resource &>(_resources[std::type_index(typeid(Resource))][aPath]);
            }

        private:
            //-------------- PRIVATE MEMBERS --------------//
            std::unordered_map<std::type_index, std::unordered_map<std::string, std::any>> _resources;

        private:
            //-------------- CTOR --------------//
            ResourcesManager() = default;
    };
} // namespace ECS::Core

#endif /* !RESSOURCESMANAGER_HPP_ */