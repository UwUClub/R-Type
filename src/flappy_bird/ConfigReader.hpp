#ifndef CONFIG_READER_HPP_
#define CONFIG_READER_HPP_

#include <nlohmann/json.hpp>
using json = nlohmann::json;

/**
 * @brief ConfigReader class is used to read the config files
 */
class ConfigReader
{
    private:
        json _player;
        json _physics;

    public:
        /**
         * @brief Construct a new ConfigReader object
         *
         */
        ConfigReader() = default;

        /**
         * @brief Destroy the ConfigReader object
         *
         */
        ~ConfigReader() = default;

        /**
         * @brief Get an Instance of the ConfigReader (singleton)
         *
         * @return ConfigReader&
         */
        static ConfigReader &getInstance()
        {
            static ConfigReader instance;

            return instance;
        }

        /**
         * @brief Load the config file
         *
         */
        void loadConfig();

        /**
         * @brief Get player data
         *
         * @return Player data
         */
        json &getPlayer();

        /**
         * @brief Get physics data
         *
         * @return Physics data
         */
        json &getPhysics();
};

#endif
