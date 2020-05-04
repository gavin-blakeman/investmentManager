//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_accounts.h
// SUBSYSTEM:           Table management to match the gnuCash 'accounts' table.
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
// HISTORY:             2020-05-03/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/database/tbl_accounts.h"

  // Standard C++ library header files

#include <unordered_map>
#include <vector>

  // Wt++ framework header files

#include <Wt/Dbo/collection.h>
#include <Wt/Dbo/Exception.h>

  // Miscellaneous library header files

#include <GCL>

namespace database
{
  static std::unordered_map< tbl_accounts::EAccountType, std::string> szAccountTypes =
  {
    {tbl_accounts::NONE, "This is an apple"},
    {tbl_accounts::ASSET, "ASSET"},
    {tbl_accounts::INCOME, "INCOME"},
    {tbl_accounts::EXPENSE, "EXPENSE"},
    {tbl_accounts::EQUITY, "EQUITY"},
    {tbl_accounts::MUTUAL, "MUTUAL"},
    {tbl_accounts::STOCK, "STOCK"},
    {tbl_accounts::BANK, "BANK"},
    {tbl_accounts::ROOT, "ROOT"},
    {tbl_accounts::LIABILITY, "LIABILITY"},
  };

  /// @brief Returns an account hierarchy for a specific type of accounts.
  /// @param[in] session: The session to use for DBMS access.
  /// @param[in] accountType: The account types to return.
  /// @returns A hierarchy of account types.
  /// @throws
  /// @version 2020-05-03/GGB - Function created.

  void tbl_accounts::buildHierarchy(Wt::Dbo::Session &session,
                                    EAccountType accountType,
                                    accountHierarchy_t &accountHierarchy)
  {
    using accountsTable_t = std::tuple<std::string,    // [0] accounts.guid
                                       std::string,    // [1] accounts.parent_guid
                                       std::string,    // [2] accounts.name
                                       std::string,    // [3] accounts.description
                                       std::string,    // [4] accounts.commodity_guid
                                       std::int32_t,   // [5] accounts.commodity_scu
                                       std::int32_t>;  // [6] accounts.non_std_scu

    GCL::sqlwriter::CSQLWriter sqlWriter;
    Wt::Dbo::collection<accountsTable_t>  accountCollection;
    std::vector<accountsTable_t> accountVector;

    sqlWriter
        .select({
                  "accounts.guid",
                  "accounts.parent_guid",
                  "accounts.name",
                  "accounts.description",
                  "accounts.commodity_guid",
                  "accounts.commodity_scu",
                  "accounts.non_std_scu"})
        .from("accounts")
        .where("accounts.account_type", "=", szAccountTypes[accountType]);

    try
    {
      accountCollection = session.query<accountsTable_t>(sqlWriter.string());
      accountVector.assign(accountCollection.begin(), accountCollection.end());
    }
    catch(Wt::Dbo::Exception &e)
    {
      ERRORMESSAGE(e.what());
    };

      // Now create the hierarchy.

    for (auto const element: accountVector)
    {
      accountHierarchy.insert(std::get<0>(element),
                              std::get<1>(element),
                              std::make_tuple(std::get<2>(element),
                                              std::get<3>(element),
                                              std::get<4>(element),
                                              std::get<6>(element) == 0 ? std::get<5>(element) : std::get<6>(element),
                                              0));
    };
  }


} // namespace database
