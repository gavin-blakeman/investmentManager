//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                /core/priceUpload/yahooPrices.h
// SUBSYSTEM:           Classes to upload commodity prices from file.
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
// HISTORY:             2020-04-25/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef CORE_PRICEUPLOAD_YAHOOPRICES_H
#define CORE_PRICEUPLOAD_YAHOOPRICES_H

  // investmentManager header files

#include "include/core/priceUpload/priceUploadManager.h".h"

namespace core
{
  namespace priceUpload
  {

    class CYahooPriceUpload
    {
    private:
      static bool pluginRegistered;

    public:
      static std::string nameFunction() { return "Yahoo"; }
      static bool validateFunction(boost::filesystem::path const &);
      static CPriceUploadManager::parseFunctionReturn_t uploadFileFunction(boost::filesystem::path const &);

    };

  } // namespace priceUpload
} // namespace core

#endif // CORE_PRICEUPLOAD_YAHOOPRICES_H
