//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_accountMapping.h
// SUBSYSTEM:           Account mapping table. Table to map gnuCash account GUID to application defined accounts.
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
// HISTORY:             2020-05-05/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef TBL_ACCOUNTMAPPING_H
#define TBL_ACCOUNTMAPPING_H

  // Standard C++ library header files

#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>

  // Wt++ framework header files

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Session.h>

namespace database
{
  class tbl_accountMapping
  {
  public:
    enum EAccountMapping
    {
      INVESTMENTCASHDEPOSIT = 1,  ///< Investment cash deposit account
      TRADINGCASH,                ///< Trading cash account
      MEMBERS_EQUITY,             ///< Members equity account.
      RETAINED_EQUITY,            ///< Retained equity after closing of books. Accumulative.
    };

    static std::string accountGUID(Wt::Dbo::Session &, EAccountMapping);
    static void updateAccount(Wt::Dbo::Session &, EAccountMapping, std::string);
    static std::unordered_map<EAccountMapping, std::string> const &accountMap();
  };
} // namespace database

#endif // TBL_ACCOUNTMAPPING_H
