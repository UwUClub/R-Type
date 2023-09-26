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
#include <iostream>
#include <memory>
#include <string>
#include <typeindex>
#include <utility>
#include <boost/container/flat_map.hpp>
#include <boost/type_index.hpp>

namespace ECS::Core {
    class IResourceHandlerBase
    {
        public:
            virtual ~IResourceHandlerBase() = default;
    };

    /**
     * @brief ResourcesManager class is a singleton that store all the resources
     *
     */
    template<typename Resource, typename... Args>
    class ResourceHandler : public IResourceHandlerBase
    {
        public:
            using ResourceMap = boost::container::flat_map<std::string, Resource *>;
            using Loader = std::function<Resource *(Args...)>;
            using Unloader = std::function<void(Resource *)>;

        public:
            //------------------- CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Resource Handler object
             *
             * @param aLoader The function that load the resource
             * @param aUnloader The function that unload the resource
             */
            ResourceHandler(Loader aLoader, Unloader aUnloader)
                : _loader(aLoader),
                  _unloader(aUnloader)
            {}

            /**
             * @brief Destroy the Resource Handler object
             * @details Unload all the resources
             */
            ~ResourceHandler() override
            {
                unloadAll();
            }

            //------------------- OPERATORS-------------------//
            ResourceHandler(const ResourceHandler &aOther) = default;
            ResourceHandler(ResourceHandler &&aOther) noexcept = default;
            ResourceHandler &operator=(const ResourceHandler &aOther) = default;
            ResourceHandler &operator=(ResourceHandler &&aOther) noexcept = default;

            //------------------- PUBLIC METHODS-------------------//
            /**
             * @brief Get the Resource object
             *
             * @param aName The name of the resource
             * @return Resource* A pointer to the resource
             */
            Resource *get(const std::string &aName)
            {
                auto itx = _resources.find(aName);

                if (itx == _resources.end()) {
                    return nullptr;
                }
                return itx->second;
            }

            /**
             * @brief A function that load a resource
             *
             * @tparam FuncArgs (Inferred)
             * @param aName The name of the resource (can be the path of the resource)
             * @param aArgs The arguments to pass to the loader
             * @return Resource* A pointer to the resource
             */
            template<typename... FuncArgs>
            Resource *load(const std::string &aName, FuncArgs &&...aArgs)
            {
                auto itx = _resources.find(aName);

                if (itx != _resources.end()) {
                    return itx->second;
                }
                auto *resource = _loader(std::forward<FuncArgs>(aArgs)...);

                _resources[aName] = resource;
                return resource;
            }

            /**
             * @brief A function that unload a resource
             *
             * @param aName The name of the resource
             */
            void unload(const std::string &aName)
            {
                auto itx = _resources.find(aName);

                if (itx == _resources.end()) {
                    return;
                }
                _unloader(itx->second);
                _resources.erase(itx);
            }

            /**
             * @brief A function that unload all the resources
             *
             */
            void unloadAll()
            {
                for (auto &resource : _resources) {
                    _unloader(resource.second);
                }
                _resources.clear();
            }

        private:
            ResourceMap _resources;
            Loader _loader;
            Unloader _unloader;
    };
    class ResourcesManager
    {
        public:
            template<typename Resource, typename... Args>
            void registerHandler(const std::string &key, typename ResourceHandler<Resource, Args...>::Loader loaderFunc,
                                 typename ResourceHandler<Resource, Args...>::Unloader unloaderFunc)
            {
                if (_handlers.find(key) != _handlers.end()) {
                    throw std::runtime_error("Handler for this key already registered.");
                }
                _handlers[key] = std::make_unique<ResourceHandler<Resource, Args...>>(loaderFunc, unloaderFunc);
            }

            template<typename Resource>
            ResourceHandler<Resource> &getHandler(const std::string &key)
            {
                if (_handlers.find(key) == _handlers.end()) {
                    throw std::runtime_error("Handler for this key not found.");
                }
                return *dynamic_cast<ResourceHandler<Resource> *>(_handlers[key].get());
            }

            void unregisterHandler(const std::string &key)
            {
                if (_handlers.find(key) == _handlers.end()) {
                    throw std::runtime_error("Handler for this key not found.");
                }
                _handlers.erase(key);
            }

            void unregisterAllHandlers()
            {
                _handlers.clear();
            }

        private:
            std::unordered_map<std::string, std::unique_ptr<IResourceHandlerBase>> _handlers;
    };

} // namespace ECS::Core

#endif /* !RESSOURCESMANAGER_HPP_ */
