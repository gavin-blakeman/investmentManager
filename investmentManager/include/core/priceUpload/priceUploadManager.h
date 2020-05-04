//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                /core/priceUpload/priceUploadManager.h
// SUBSYSTEM:           Manage the plugis that provide price upload functionality.
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           core::priceUpload
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

#ifndef PRICEUPLOADMANAGER_H
#define PRICEUPLOADMANAGER_H

  // Standard C++ library header files

#include <ctime>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

  // Wt++ framework header files

#include <Wt/Dbo/Session.h>

  // Miscellaneous library header files

#include "boost/filesystem.hpp"

namespace core
{
  namespace priceUpload
  {
    class CPriceUpload;

    class CPriceUploadManager
    {
    public:
      using pricesVector_t = std::vector<std::pair<std::tm, double>>;
      using parseFunctionReturn_t = std::optional<pricesVector_t>;

      using nameFunction_t = std::function<std::string()>;
      using validateFunction_t = std::function<bool(boost::filesystem::path const &)>;
      using parseFileFunction_t = std::function<parseFunctionReturn_t(boost::filesystem::path const &)>;
      using plugin_t = std::tuple<nameFunction_t, validateFunction_t, parseFileFunction_t>;

    private:
      using pricePlugin_t = std::unordered_map<std::string, plugin_t>;

      CPriceUploadManager() {}                                                // Not user creatable.
      CPriceUploadManager(CPriceUploadManager const &) = delete;              // Cannot copy
      CPriceUploadManager(CPriceUploadManager &&) = delete;                   // Cannot move
      CPriceUploadManager &operator =(CPriceUploadManager const &) = delete;  // Cannot copy.

      static pricePlugin_t &pluginMap();
      static nameFunction_t nameFunction(std::string);
      static validateFunction_t validateFunction(std::string);
      static parseFileFunction_t parseFileFunction(std::string);
      static std::vector<std::string> registeredPlugins();

    public:
      static bool registerPlugin(plugin_t);

      static bool validateFile(boost::filesystem::path const &);
      static parseFunctionReturn_t parseFile(boost::filesystem::path const &);
    };

  } // namespace priceUpload
} // namespace core

#endif // PRICEUPLOADMANAGER_H
