//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_splits
// SUBSYSTEM:           gnuCash splits table
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
// OVERVIEW:            The commodities table is organised as a namespace:mnemonic pair. The namespace does not sit in a different
//                      table, so the data is stored multiple times in the table.
//
// HISTORY:             2020-05-26/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/database/tbl_splits.h"

  // Wt++ framework header files

#include <Wt/Dbo/Transaction.h>

  // Miscellaneous library header files

#include <GCL>

  // investmentManager header files

#include "include/core/functions/guid.h"

namespace database
{

  /// @brief Inserts the splits for a transactions
  /// @param[in] session: The session to use for the insertion.
  /// @param[in[ transactionGUID: The transaction GUID
  /// @param[in] splits: A STL container containing the list of splits.
  /// @throws
  /// @pre 1. The transaction must be created and valid in the calling function. This function does not create the transaction
  ///         this is to allow transactional integrity and atomic insertions with the transactions.
  /// @version 2020-05-26/GGB - Function created.

  void tbl_splits::insertSplits(Wt::Dbo::Session &session, std::string const &transactionGUID, splits_t const &splits)
  {

    /* Split fields
     *  guid - Auto create before insertion
     *  tx_guid - Transaction guid
     *  account_guid - The account associated with the split
     *  memo - Memo to associate with the split
     *  action - The action (Sell)
     *  reconcile_state - Set to 'n'
     *  reconcile_date - Use creation date
     *  value_num - Value numerator
     *  value_denom - Value denominator
     *  quantity_num - Quantity
     *  quantity_denom -
     *  lot_guid - NULL
     */

    std::time_t t = std::time(nullptr);
    std::tm reconcileDate = *std::localtime(&t);

    GCL::sqlWriter sqlWriter;

    sqlWriter.insertInto("splits",
                         { "guid", "tx_guid", "account_guid", "memo", "action", "reconcile_state", "reconcile_date",
                           "value_num", "value_denom", "quantity_num", "quantity_denom", "lot_guid"})
             .values({{ GCL::sqlWriter::bindValue("?"),    // guid
                       transactionGUID,                   // tx_guid
                       GCL::sqlWriter::bindValue("?"),    // account_guid
                       GCL::sqlWriter::bindValue("?"),    // memo
                       GCL::sqlWriter::bindValue("?"),    // action
                       "n",                               // reconcile_state
                       reconcileDate,                     // reconcile_date
                       GCL::sqlWriter::bindValue("?"),    // value_num
                       GCL::sqlWriter::bindValue("?"),    // value_denom
                       GCL::sqlWriter::bindValue("?"),    // quantity_num
                       GCL::sqlWriter::bindValue("?"),    // quantity_denom
                       "NULL"                             // lot_guid
                     }});

    splits_t::const_iterator iterator = splits.begin();
    std::string sqlString = sqlWriter.string();

    while (iterator != splits.end())
    {


      session.execute(sqlString)
          .bind(core::generateGUID())
          .bind(iterator->account_guid)
          .bind(iterator->memo)
          .bind(iterator->action)
          .bind(1);
    };

  }
}
