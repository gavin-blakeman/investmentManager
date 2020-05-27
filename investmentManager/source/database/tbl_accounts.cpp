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

#include <iterator>
#include <unordered_map>
#include <vector>

  // Wt++ framework header files

#include <Wt/Dbo/collection.h>
#include <Wt/Dbo/Exception.h>

  // Miscellaneous library header files

#include <GCL>

  // investmentManager header files

#include "include/database/tbl_books.h"

namespace database
{
  namespace tbl_accounts
  {
    static std::unordered_map< tbl_accounts::EHierarchyType, std::string> szAccountTypes =
    {
      {tbl_accounts::ASSET, "ASSET"},
      {tbl_accounts::INCOME, "INCOME"},
      {tbl_accounts::EXPENSE, "EXPENSE"},
      {tbl_accounts::EQUITY, "EQUITY"},
      {tbl_accounts::LIABILITY, "LIABILITY"},
    };

    /// @brief Determines the account value of the specified account.
    /// @details This function is more complicate than it looks at first. To determine the value of stock or bond accounts takes
    ///          lookups into the stock value tables. (If available.)
    /// @param[in] session: The session to use for database access.
    /// @param[in] accountGUID: The guid of the account being totalled.
    /// @param[in] closingDate: The closing date to determine the value on.
    /// @throws
    /// @version 2020-05-27/GGB - Function created.

    std::optional<double> accountValue(Wt::Dbo::Session &session, std::string, std::tm &)
    {

    }

    /// @brief Returns an account hierarchy for a specific type of accounts.
    /// @param[in] session: The session to use for DBMS access.
    /// @param[in] accountType: The account types to return.
    /// @returns A hierarchy of account types.
    /// @throws
    /// @version 2020-05-03/GGB - Function created.

    void buildHierarchy(Wt::Dbo::Session &session,
                        EHierarchyType accountType,
                        accountHierarchy_t &accountHierarchy)
    {
      /* Any account hierarchy starts with the root account, available from the 'books' table. To build the table of accounts,
       * an iterative approach needs to be taken, building each level recursively using the parent_guid. This is necessary as the
       * accounts need not all be of the same type. (IE stocks can be children of Assets. The account_type field is used more
       * to determine how the books look than the actual account type.
       */

      using accountsTable_t = std::tuple<std::string,    // [0] accounts.guid
      std::string,    // [1] accounts.parent_guid
      std::string,    // [2] accounts.name
      std::string,    // [3] accounts.description
      std::string,    // [4] accounts.commodity_guid
      std::int32_t,   // [5] accounts.commodity_scu
      std::int32_t,   // [6] accounts.non_std_scu
      std::string>;   // [7] accounts.account_type

      GCL::sqlWriter sqlWriter;
      Wt::Dbo::collection<accountsTable_t>  accountCollection;
      std::vector<accountsTable_t> accountVector; // The accountVector is used to store all the accounts as they are loaded.
      std::string rootAccountGUID = tbl_books::rootAccountGUID(session);
      std::vector<accountsTable_t>::size_type accountIndex = 0;

      sqlWriter
          .select({
                    "guid",
                    "parent_guid",
                    "name",
                    "description",
                    "commodity_guid",
                    "commodity_scu",
                    "non_std_scu",
                    "account_type"})
          .from("accounts")
          .where({ {"account_type", "=", szAccountTypes[accountType]},
                   {"parent_guid", "=", GCL::sqlWriter::bindValue("?")} });

      try
      {
        accountCollection = session.query<accountsTable_t>(sqlWriter.string()).bind(rootAccountGUID);
        accountVector.insert(accountVector.end(), accountCollection.begin(), accountCollection.end());
      }
      catch(Wt::Dbo::Exception &e)
      {
        ERRORMESSAGE(e.what());
      };

      /* When iterating to find the entire account hierarchy, using iterators is not possible as if the memory in the vector needs
       * to be reallocated if the vector grows, the iterators are invalidated.
       * So rather than using iterators, lets use indexes into the vector.
       */

      sqlWriter.resetWhere();

      sqlWriter.where("parent_guid", "=", GCL::sqlWriter::bindValue("?"));

      do
      {
        try
        {
          accountCollection = session.query<accountsTable_t>(sqlWriter.string()).bind(std::get<1>(accountVector[accountIndex]));
          accountVector.insert(accountVector.end(), accountCollection.begin(), accountCollection.end());
        }
        catch(Wt::Dbo::Exception &e)
        {
          ERRORMESSAGE(e.what());
        };
        accountIndex++;
      }
      while (accountIndex != accountVector.size());

      // Now create the hierarchy.

      accountHierarchy.setRootValue(rootAccountGUID);

      for (auto const element: accountVector)
      {
        accountHierarchy.insert(std::get<0>(element),
                                std::get<1>(element),
                                std::make_tuple(std::get<7>(element),
                                                std::get<2>(element),
                                                std::get<3>(element),
                                                std::get<4>(element),
                                                std::get<6>(element) == 0 ? std::get<5>(element) : std::get<6>(element),
                                                0));
      };
    }

    /// @brief Returns the commodity GUID for the specified account GUID.
    /// @param[in] session: The session to use.
    /// @param[in] accountGUID: The account GUID to find the currency for.
    /// @returns A std::optional containing the commodityGUID if found.

    std::optional<std::string> commodityGUID(Wt::Dbo::Session &session, std::string const &accountGUID)
    {
      std::optional<std::string> returnValue;
      GCL::sqlWriter sqlWriter;

      sqlWriter.select({"commodity_guid"}).from("accounts").where("guid", "=", accountGUID);
      try
      {
        Wt::Dbo::Transaction transaction(session);

        returnValue = session.query<std::string>(sqlWriter.string());
      }
      catch(Wt::Dbo::Exception &e)
      {
        ERRORMESSAGE(e.what());
      };

      return returnValue;
    }

  } // namespace tbl_accounts
} // namespace database
