//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                /core/priceUpload/priceUploadManager.cpp
// SUBSYSTEM:           Manage the plugis that provide price upload functionality.
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           N/A
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2020 Gavin Blakeman.
//                      This file is part of the investmentManager Project
//
//                      investmentManager is free software: you can redistribute it and/or modify it under the terms of the GNU
//                      General Public License as published by the Free Software Foundation, either version 2 of the License, or (at
//                      your option) any later version.
//
//                      investmentManager is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
//                      even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
//                      Public License for more details.
//
//                      You should have received a copy of the GNU General Public License along with investmentManager.  If not,
//                      see <http://www.gnu.org/licenses/>.
//
// OVERVIEW:
//
// HISTORY:             2020-04-26/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/core/priceUpload/priceUploadManager.h"

namespace core
{
  namespace priceUpload
  {
    /// @brief Function to return a reference to the plugin map used to record all the plugins.
    /// @returns Reference to the plugin map.
    /// @throws std::bad_alloc
    /// @version 2020-04-26/GGB - Function created.

    CPriceUploadManager::pricePlugin_t &CPriceUploadManager::pluginMap()
    {
      static pricePlugin_t *pricePluginMap = new pricePlugin_t();

      return *pricePluginMap;
    }

    /// @brief Returns a vector of the names of all registered plugins.
    /// @returns std::vector<std::string> with all the names of the plugins.
    /// @throws
    /// @version 2020-04-26/GGB - Function created.

    std::vector<std::string> CPriceUploadManager::registeredPlugins()
    {
      std::vector<std::string> returnValue;

      for (auto plugin : pluginMap())
      {
        returnValue.emplace_back(plugin.first);
      };

      return std::move(returnValue);
    }

    /// @brief Function to register a plugin with the plugin manager.
    /// @param[in] pluginData: tuple containing the data for registration.
    /// @returns Always returns true. Return value is provided to allow static initialisation.
    /// @throws std::bad_alloc
    /// @version 2020-04-26/GGB - Function created.

    bool CPriceUploadManager::registerPlugin(plugin_t pluginData)
    {
      pluginMap().insert_or_assign(std::get<0>(pluginData)(), pluginData); // Use the name function call to get the name.

      return true || false;
    }

    /// @brief Returns the function pointer to the specified name function.
    /// @param[in] pluginName: The plugin to find.
    /// @returns Function pointer.
    /// @throws std::runtime_error
    /// @version 2020-04-26/GGB - Function created.

    CPriceUploadManager::nameFunction_t CPriceUploadManager::nameFunction(std::string pluginName)
    {
      pricePlugin_t::const_iterator iterator = pluginMap().find(pluginName);

      if (iterator == pluginMap().end())
      {
        throw std::runtime_error("The specified plugin has not been registered.");
      }
      else
      {
        return std::get<0>(iterator->second);
      }
    }

    /// @brief Returns the function pointer to the validation function.
    /// @param[in] pluginName: The plugin to find.
    /// @returns Function pointer.
    /// @throws std::runtime_error
    /// @version 2020-04-26/GGB - Function created.

    CPriceUploadManager::validateFunction_t CPriceUploadManager::validateFunction(std::string pluginName)
    {
      pricePlugin_t::const_iterator iterator = pluginMap().find(pluginName);

      if (iterator == pluginMap().end())
      {
        throw std::runtime_error("The specified plugin has not been registered.");
      }
      else
      {
        return std::get<1>(iterator->second);
      }
    }

    /// @brief Returns the function pointer to the upload function.
    /// @param[in] pluginName: The plugin to find.
    /// @returns Function pointer.
    /// @throws std::runtime_error
    /// @version 2020-04-26/GGB - Function created.

    CPriceUploadManager::uploadFileFunction_t CPriceUploadManager::uploadFileFunction(std::string pluginName)
    {
      pricePlugin_t::const_iterator iterator = pluginMap().find(pluginName);

      if (iterator == pluginMap().end())
      {
        throw std::runtime_error("The specified plugin has not been registered.");
      }
      else
      {
        return std::get<2>(iterator->second);
      }
    }

    /// @brief Attempts to validate the file. Each of the plugins are tried in turn until one manages to validate the file.
    /// @param[in] filePath: Path to the file to validate.
    /// @returns true - If the file was validated.
    /// @throws
    /// @version 2020-04-26/GGB - Function created.

    bool CPriceUploadManager::validateFile(boost::filesystem::path const &filepath)
    {
      bool returnValue = false;

      if (!pluginMap().empty())
      {
        pricePlugin_t::const_iterator iterator = pluginMap().begin();

        while (!returnValue && (iterator != pluginMap().end()))
        {
          returnValue = std::get<1>(iterator++->second)(filepath);
        };
      };

      return returnValue;
    }

  }  // namespace priceUpload
} // namespace core
