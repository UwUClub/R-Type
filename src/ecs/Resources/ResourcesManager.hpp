/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** RessourcesManager
*/

#ifndef RESSOURCESMANAGER_HPP_
#define RESSOURCESMANAGER_HPP_

#include <algorithm>
#include <any>
#include <functional>
#include <memory>
#include <string>
#include <typeindex>
#include <utility>
#include <boost/container/flat_map.hpp>

namespace ECS::Core {
    /**
     * @brief ResourcesManager class is a singleton that store all the resources
     *
     */
    class ResourcesManager
    {
        public:
            //-------------- CTOR, DTOR, OPERATORS --------------//
            static ResourcesManager &getInstance()
            {
                static ResourcesManager instance;
                return instance;
            }

            ~ResourcesManager()
            {
                for (auto &resource : _resources) {
                    auto &unloader = _unloader[std::type_index(resource.second->type())];
                    unloader(resource.second);
                }
            }

            ResourcesManager(const ResourcesManager &aOther) = default;
            ResourcesManager(ResourcesManager &&aOther) noexcept = default;

            ResourcesManager &operator=(const ResourcesManager &aOther) = default;
            ResourcesManager &operator=(ResourcesManager &&aOther) noexcept = default;

            //-------------- PUBLIC METHODS --------------//

            /**
             * @brief Load the resource if it's not already loaded
             *
             * @tparam Resource The type of the resource
             * @param aPath The path to the resource
             * @return Resource& A reference to the resource
             */
            template<class Resource>
            Resource *load(const std::string &aPath)
            {
                try {
                    auto isLoaded = _resources.find(aPath);
                    if (isLoaded != _resources.end()) {
                        return std::any_cast<Resource *>(isLoaded->second);
                    }

                    auto &loader = _loaders[std::type_index(typeid(Resource))];
                    auto *resource = loader(aPath);

                    _resources[aPath] = resource;
                    return std::any_cast<Resource *>(_resources[aPath]);
                } catch (const std::bad_any_cast &e) {
                    throw ResourcesManagerException("Bad cast: " + std::string(e.what()));
                }
            }

            /**
             * @brief Unload the resource
             *
             * @tparam Resource The type of the resource
             * @param aPath The path to the resource
             */
            template<class Resource>
            void unload(const std::string &aPath)
            {
                auto isLoaded = _resources.find(aPath);
                if (isLoaded == _resources.end()) {
                    return;
                }

                auto &unloader = _unloader[std::type_index(typeid(Resource))];
                unloader(isLoaded->second);
                _resources.erase(aPath);
            }

            /**
             * @brief Add both a loader and an unloader for a resource
             *
             * @tparam Resource The type of the resource
             * @param aUnloader The unloader
             * @param aLoader The loader
             */
            template<class Resource>
            void addHandlers(const std::function<void(Resource *)> &aUnloader,
                             const std::function<Resource *(const std::string &)> &aLoader)
            {
                addUnloader<Resource>(aUnloader);
                addLoaders<Resource>(aLoader);
            }

            /**
             * @brief Add a loaded resource to the resources map
             *
             * @tparam Resource The type of the resource
             * @param aValue The name of the resource, for retrieve it
             * @param aResource The resource to store
             * @param aUnloader The unloader of the resource
             */
            template<class Resource>
            void addResource(const std::string &aValue, const Resource *aResource,
                             const std::function<void(Resource *)> &aUnloader)
            {
                if (_resources.find(aValue) != _resources.end()) {
                    return;
                }
                addUnloader<Resource>(aUnloader);
                _resources[aValue] = aResource;
            }

        private:
            //-------------- PRIVATE MEMBERS --------------//
            boost::container::flat_map<std::type_index, std::function<std::any *(const std::string &)>> _loaders;
            boost::container::flat_map<std::type_index, std::function<void(std::any *)>> _unloader;
            boost::container::flat_map<std::string, std::any *> _resources;

        private:
            //-------------- CTOR --------------//
            ResourcesManager() = default;

            /**
             * @brief Add a loader for a resource
             *
             * @tparam Resource The type of the resource
             * @param aLoader The loader
             */
            template<class Resource>
            void addLoaders(const std::function<Resource *(const std::string &)> &aLoader)
            {
                _loaders[std::type_index(typeid(Resource))] = aLoader;
            }

            /**
             * @brief Add an unloader for a resource
             *
             * @tparam Resource The type of the resource
             * @param aUnloader The unloader
             */
            template<class Resource>
            void addUnloader(const std::function<void(Resource *)> &aUnloader)
            {
                _unloader[std::type_index(typeid(Resource))] = aUnloader;
            }

            class ResourcesManagerException : public std::exception
            {
                public:
                    explicit ResourcesManagerException(const std::string &aMessage)
                        : _message(aMessage)
                    {}
                    ~ResourcesManagerException() override = default;

                    const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message;
            };
    };
} // namespace ECS::Core

#endif /* !RESSOURCESMANAGER_HPP_ */
