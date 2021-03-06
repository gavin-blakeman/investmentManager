﻿//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_prices
// SUBSYSTEM:           gnuCash prices table
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
// HISTORY:             2020-04-19/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef TBL_PRICES_H
#define TBL_PRICES_H

// C++ standard library header files

#include <cstdint>
#include <string>

// Wt++ framework header files

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Types.h>
#include <Wt/Dbo/Session.h>
#include <Wt/WAbstractTableModel.h>
#include <Wt/WGlobal.h>
#include <Wt/WDate.h>

// Miscellaneous library header files

#include <boost/filesystem.hpp>
#include <MCL>

// investmentManager header files

#include "include/config.h"
#include "include/database/databaseDefinitions.h"
#include "include/database/databaseTables.h"
#include "include/core/priceUpload/priceUploadManager.h"

namespace database
{
  namespace tbl_prices
  {
    std::string const SOURCE_FINANCE = "Finance::Quote";
    std::string const SOURCE_USER = "user:price";
    std::string const TYPE_TRANSACTION = "transaction";
    std::string const TYPE_LAST = "last";

    std::optional<money_t> closingPrice(Wt::Dbo::Session &, std::string const &, std::tm const &);
    void priceUpload(Wt::Dbo::Session &, std::string const &, boost::filesystem::path const &);

  } // namespace tbl_prices
} // namespace database

#endif // TBL_PRICES_H
