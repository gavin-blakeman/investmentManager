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

#include "include/database/tbl_accountMapping.h"

  // Standard C++ library header files

#include <exception>

  // Wt++ framework header files

#include <Wt/Dbo/Exception.h>
#include <Wt/Dbo/Transaction.h>

  // Miscellaneous library header files

#include <GCL>

namespace database
{
  static std::unordered_map<tbl_accountMapping::EAccountMapping, std::string> accountMapData =
  {
    {tbl_accountMapping::INVESTMENTCASHDEPOSIT, "Investment Cash Deposit"},
    {tbl_accountMapping::TRADINGCASH, "Trading Cash Deposit"},
    {tbl_accountMapping::MEMBERS_EQUITY, "Members Equity"},
    {tbl_accountMapping::RETAINED_EQUITY, "Retained Equity"},
  };

  /// @brief Obtains account GUID's for specified accounts. These GUID's are based on the account mappings that need to be set up.
  /// @param[in] session: The session to use
  /// @param[in] accountMap: The specified account to map to GUID.
  /// @returns A std::string containing the specified account GUID.
  /// @throws
  /// @version 2020-05-05/GGB - Function created.

  std::string tbl_accountMapping::accountGUID(Wt::Dbo::Session &session, EAccountMapping accountMap)
  {
    std::string returnValue;
    GCL::sqlWriter sqlWriter;

    try
    {
      sqlWriter.select({"AccountGUID"}).from("im_accountMapping").where("ID", "=", accountMap);

      Wt::Dbo::Transaction transaction(session);
    }
    catch(Wt::Dbo::Exception &e)
    {
      CRITICALMESSAGE(e.what());
      throw std::runtime_error(e.what());
    };

   return returnValue;
  }

  /// @brief Returns a constant reference to the list of all possible accounts to map.
  /// @returns a const reference to the accountMapData map.
  /// @throws None.
  /// @version 2020-05-05/GGB - Function created.

  std::unordered_map<tbl_accountMapping::EAccountMapping, std::string> const &tbl_accountMapping::accountMap()
  {
    return accountMapData;
  }


} // namespace database
