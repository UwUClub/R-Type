/*
** EPITECH PROJECT, 2023
** bs
** File description:
** World
*/

#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <any>
#include <cstddef>
#include <exception>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <vector>
#include "SparseArray.hpp"
// #include <boost/container/flat_map.hpp>

namespace ECS::Core {
    /**
     * @brief A class that contains all the components and entities and systems
     * @details This class is a singleton, it contains all the components and entities and systems, it uses SparseArray
as Component container
     * @details It all works with templates, see How to use section for more details
     */
    class World
    {
        public:
            //-------------- INSTANCE --------------//
            /**
             * @brief Get the Instance object (Singleton)
             *
             * @return World& The instance of the World
             */
            static World &getInstance()
            {
                static World sharedInstance;

                return sharedInstance;
            }

            //-------------- METHODS COMPONENT --------------//
            /**
             * @brief Register a component in the World class.
             *
             * @tparam Component Represents the type of the component being registered. (Can be anything but I recommend
             * struct)
             * @return SparseArray<Component>&
             */
            template<class Component>
            SparseArray<Component> &registerComponent()
            {
                if (_components.find(std::type_index(typeid(Component))) != _components.cend()) {
                    throw RegistryException("Component already registered");
                }
                auto &component = _components[std::type_index(typeid(Component))] = SparseArray<Component>();
                _eraseFunctions[std::type_index(typeid(Component))] = [](World &registry, const std::size_t &idx) {
                    auto &component = registry.getComponent<Component>();

                    component.erase(idx);
                };
                _addFunctions[std::type_index(typeid(Component))] = [](World &registry, const std::size_t &idx) {
                    auto &component = registry.getComponent<Component>();

                    component.emplaceAt(idx, Component());
                };
                return std::any_cast<SparseArray<Component> &>(component);
            }

            /**
             * @brief Get the Component object
             *
             * @tparam Component Represents the type of the component being retrieved.
             * @return SparseArray<Component>& The component
             */
            template<class Component>
            SparseArray<Component> &getComponent()
            {
                try {
                    auto &component =
                        std::any_cast<SparseArray<Component> &>(_components.at(std::type_index(typeid(Component))));
                    return component;
                } catch (const std::bad_any_cast &e) {
                    throw RegistryException("There is no component of this type");
                }
            }

            /**
             * @brief Get the Component object
             *
             * @tparam Component Represents the type of the component being retrieved.
             * @return SparseArray<Component> const& The component
             */
            template<class Component>
            SparseArray<Component> const &getComponent() const
            {
                try {
                    auto &component = std::any_cast<SparseArray<Component> const &>(
                        _components.at(std::type_index(typeid(Component))));
                    return component;
                } catch (const std::bad_any_cast &e) {
                    throw RegistryException("There is no component of this type");
                }
            }

            //-------------- METHODS ENTITY --------------//
            /**
             * @brief Kill an entity
             * @details This method will call the erase function of all the components
             * @param aIdx The index of the entity
             */
            void killEntity(const std::size_t &aIdx)
            {
                for (auto &component : _components) {
                    _eraseFunctions[component.first](*this, aIdx);
                }
                _reusableIds.push_back(aIdx);
            }

            /**
             * @brief Create an entity
             * @details This method will create an entity and return its index, if there is reusable ids, it will use
             * @return std::size_t The index of the entity
             */
            std::size_t createEntity()
            {
                if (_reusableIds.empty()) {
                    for (auto &component : _components) {
                        _addFunctions[component.first](*this, _id);
                    }
                    return _id++;
                }
                auto &idx = _reusableIds.back();

                _reusableIds.pop_back();
                return idx;
            }

            /**
             * @brief Add an entity to a component
             *
             * @tparam Component The component to add the entity to
             * @param aIdx The index of the entity (index in the sparse array)
             * @param aComponent The component to add (can be anything but I recommend struct, same as when you
             * registered component)
             * @return SparseArray<Component>::referenceType The reference to the component
             */
            template<class Component>
            typename SparseArray<Component>::referenceType addEntityComponent(const std::size_t &aIdx,
                                                                              Component &&aComponent)
            {
                try {
                    auto &componentArray = getComponent<Component>();

                    return componentArray.emplaceAt(aIdx, std::forward<Component>(aComponent));
                } catch (const RegistryException &e) {
                    throw RegistryException("There is no component of this type in the registry");
                }
            }

            /**
             * @brief Add an entity to a component
             *
             * @tparam Component The component to add the entity to
             * @tparam Args The arguments to pass to the constructor of the component
             * @param aIdx The index of the entity (index in the sparse array)
             * @param aArgs The arguments to pass to the constructor of the component
             * @return SparseArray<Component>::referenceType
             */
            template<class Component, typename... Args>
            typename SparseArray<Component>::referenceType emplaceEntityComponent(const std::size_t &aIdx,
                                                                                  Args &&...aArgs)
            {
                try {
                    auto &componentArray = getComponent<Component>();

                    return componentArray.emplaceAt(aIdx, std::forward<Args>(aArgs)...);
                } catch (const RegistryException &e) {
                    throw RegistryException("There is no component of this type in the registry");
                }
            }

            /**
             * @brief Remove an entity from a component
             *
             * @tparam Component The component to remove the entity from
             * @param aIdx The index of the entity (index in the sparse array)
             */
            template<class Component>
            void removeComponent(const std::size_t &aIdx)
            {
                try {
                    auto &componentArray = getComponent<Component>();

                    componentArray.erase(aIdx);
                } catch (const RegistryException &e) {
                    throw RegistryException("There is no component of this type in the registry");
                }
            }

            //-------------- METHODS SYSTEM --------------//
            /**
             * @brief Add a system to the World
             * @details A system is a function that need a special signature, it needs to take a World and the
             * components, pay attention to the How to use section
             * @tparam Components The components that the system needs
             * @tparam Function Inferred by the compiler
             * @param aFunction The function to add as a system
             */
            template<class... Components, typename Function>
            void addSystem(Function &&aFunction)
            {
                _systems.push_back([this, func = std::forward<Function>(aFunction)](World &aReg) {
                    callSystem<Components...>(func, aReg);
                });
            }

            /**
             * @brief Run all the systems, giving them automatically the World and the components the need
             *
             */
            void runSystems()
            {
                for (auto &system : _systems) {
                    system(*this);
                }
            }

            /**
             * @brief Get delta time
             *
             * @return float The delta time
             */
            float getDeltaTime() const
            {
                return _deltaTime;
            }

            /**
             * @brief Set delta time
             *
             * @param aDeltaTime The delta time
             */
            void setDeltaTime(float aDeltaTime)
            {
                _deltaTime = aDeltaTime;
            }

        private:
            /**
             * @brief Call a system, this is what is stored in the vector of systems
             *
             * @tparam Components The components that the system needs
             * @tparam Function Inferred by the compiler
             * @param aFunction The function to call
             * @param aReg The World
             */
            template<typename... Components, typename Function>
            void callSystem(Function &&aFunction, World &aReg)
            {
                aFunction(aReg, getComponent<Components>()...);
            }

            //-------------- EXCEPTION --------------//
            /**
             * @brief Exception class for the World class
             *
             */
            class RegistryException : public std::exception
            {
                public:
                    explicit RegistryException(const char *message)
                        : _message(message)
                    {}

                    const char *what() const noexcept override
                    {
                        return _message;
                    }

                private:
                    const char *_message;
            };
            World() = default;

        private:
            size_t _id {0};
            std::map<std::type_index, std::any> _components;
            std::map<std::type_index, std::function<void(World &, const std::size_t &)>> _eraseFunctions;
            std::map<std::type_index, std::function<void(World &, const std::size_t &)>> _addFunctions;
            std::vector<std::size_t> _reusableIds;

            using systemFunction = std::function<void(World &)>;
            std::vector<systemFunction> _systems;

            float _deltaTime = 0;
    };
} // namespace ECS::Core

#endif /* !WORLD_HPP_ */
