//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_transactions.cpp
// SUBSYSTEM:           Table management to match the gnuCash 'transactions' table.
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
// HISTORY:             2020-05-07/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/database/tbl_transactions.h"

  // Wt++ framework header files

#include <Wt/Dbo/Transaction.h>

  // Miscellaneous library header files

#include <GCL>
#include <SCL>

std::ostream &operator<<(std::ostream &, std::tm const &);

  // investmentManager header files

#include "include/core/functions/guid.h"
#include "include/core/helper.h"

namespace database
{
  /// @brief Inserts a transaction into the database table.
  /// @param[in] session: The session to use.
  /// @param[in] currencyGUID:
  /// @param[in] num:
  /// @param[in] postDate: The posting date of the transaction.
  /// @param[in] description: The description to associate with the transaction
  /// @returns guid: The GUID of the transaction.
  /// @throws
  /// @version 2020-05-07/GGB - Function created.

  std::string tbl_transactions::insertTransaction(Wt::Dbo::Session &session,
                                                  std::string const &currencyGUID,
                                                  std::string const &num,
                                                  std::tm &postDate,
                                                  std::string const &description)
  {
    GCL::sqlWriter sqlWriter;

    std::string guid(core::generateGUID());
    std::time_t t = std::time(nullptr);
    std::tm enterDate = *std::localtime(&t);

    {
      Wt::Dbo::Transaction transaction(session);

      sqlWriter.insertInto("transactions",
                           { "guid", "currency_guid", "num", "post_date", "enter_date", "description" })
               .values({{guid, currencyGUID, num, postDate, enterDate, description}});


    };

    return guid;
  }

}   // namespace database
