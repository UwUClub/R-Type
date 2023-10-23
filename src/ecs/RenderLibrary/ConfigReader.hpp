#ifndef CONFIG_READER_HPP_
#define CONFIG_READER_HPP_

#include <nlohmann/json.hpp>
using json = nlohmann::json;

static const std::string CONFIG_PATH = "config/flappybird.json";

/**
 * @brief ConfigReader class is used to read the config files
 */
class ConfigReader
{
    private:
        json _data;

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
         * @brief Get all the config
         *
         * @return All the config
         */
        json &get();
};

#endif