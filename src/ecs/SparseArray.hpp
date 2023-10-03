/*
** EPITECH PROJECT, 2023
** bs
** File description:
** SparseArray
*/

#ifndef SPARSEARRAY_HPP_
#define SPARSEARRAY_HPP_

#include <optional>
#include <vector>

namespace ECS::Core {

    /**
     * @brief SparseArray class is a container that store a component in a sparse array
     *
     * @tparam Component The type of the component to store
     */
    template<typename Component>
    class SparseArray
    {
        public:
            //-------------- TYPEDEFS --------------//
            using valueType = std::optional<Component>;
            using referenceType = valueType &;
            using constReferenceType = const valueType &;
            using containerT = std::vector<valueType>;
            using sizeType = typename containerT::size_type;
            using iterator = typename containerT::iterator;
            using constIterator = typename containerT::const_iterator;

        public:
            //-------------- CTOR, DTOR, OPERATORS --------------//
            SparseArray() = default;
            ~SparseArray() = default;

            SparseArray(const SparseArray &aOther)
                : _container(aOther._container)
            {}
            SparseArray(SparseArray &&aOther) noexcept
                : _container(std::move(aOther._container))
            {}

            SparseArray &operator=(const SparseArray &aOther)
            {
                _container = aOther._container;
                return *this;
            }
            SparseArray &operator=(SparseArray &&aOther) noexcept
            {
                _container = std::move(aOther._container);
                return *this;
            }

            referenceType operator[](std::size_t aIndex)
            {
                return _container[aIndex];
            }
            constReferenceType operator[](std::size_t aIndex) const
            {
                return _container[aIndex];
            }

            //-------------- METHODS ITERATOR--------------//
            iterator begin()
            {
                return _container.begin();
            }
            constIterator begin() const
            {
                return _container.begin();
            }
            constIterator cbegin() const
            {
                return _container.cbegin();
            }

            iterator end()
            {
                return _container.end();
            }
            constIterator end() const
            {
                return _container.end();
            }
            constIterator cend() const
            {
                return _container.cend();
            }

            sizeType size() const
            {
                return _container.size();
            }

            //-------------- METHODS --------------//
            /**
             * @brief Insert a component at the position aPos
             *
             * @param aPos The position to insert the component (Index of the Entity)
             * @param aValue The component to insert
             * @return referenceType A reference to the component inserted
             */
            referenceType insertAt(sizeType aPos, constReferenceType aValue)
            {
                if (aPos >= _container.size()) {
                    _container.resize(aPos + 1);
                }
                _container[aPos] = aValue;
                return _container[aPos];
            }

            /**
             * @brief Insert a component at the position aPos
             *
             * @param aPos The position to insert the component (Index of the Entity)
             * @param aValue The component to insert
             * @return referenceType A reference to the component inserted
             */
            referenceType insertAt(sizeType aPos, valueType &&aValue)
            {
                if (aPos >= _container.size()) {
                    _container.resize(aPos + 1);
                }
                _container[aPos] = std::move(aValue);
                return _container[aPos];
            }

            /**
             * @brief Emplace and build a component at the position aPos
             *
             * @tparam Args Inferred type of the arguments
             * @param aPos The position to insert the component (Index of the Entity)
             * @param aArgs The list of arguments to build the component
             * @return referenceType
             */
            template<typename... Args>
            referenceType emplaceAt(sizeType aPos, Args &&...aArgs)
            {
                if (aPos >= _container.size()) {
                    _container.resize(aPos + 1);
                }
                _container[aPos].emplace(Component(std::forward<Args>(aArgs)...));
                return _container[aPos];
            }

            /**
             * @brief Remove a component at the position aPos
             *
             * @param aPos The position to remove the component (Index of the Entity)
             */
            void erase(sizeType aPos)
            {
                if (aPos >= _container.size()) {
                    return;
                }
                _container[aPos].reset();
            }

            /**
             * @brief Get the index of a component
             *
             * @param aValue The component to get the index
             * @return sizeType The index of the component, or the size of the container if not found
             */
            sizeType getIndex(constReferenceType aValue) const
            {
                for (sizeType i = 0; i < _container.size(); i++) {
                    if (_container[i] == aValue) {
                        return i;
                    }
                }
                return _container.size();
            }

        private:
            containerT _container;
    };
} // namespace ECS::Core

#endif /* !SPARSEARRAY_HPP_ */
