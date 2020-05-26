//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                /core/transactions/memberInvestment.h
// SUBSYSTEM:           Functions performing transactions
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           core::accountTransactions
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
// HISTORY:             2020-05-02/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/core/accountTransactions/memberInvestment.h"

  // Miscellaneous library header files

#include <GCL>

  // investmentManager header files.

#include "include/core/functions/guid.h"
#include "include/database/tbl_accountMapping.h"
#include "include/database/tbl_accounts.h"
#include "include/database/tbl_transactions.h"

namespace core
{
  namespace accountTransactions
  {
    /// @brief Creates the various transactions for a member investement.
    /// @details  A member investment occurs when a member invests funds into the fund. An investment is considered to be a cash
    ///           investment. The transactions that need to be created are:
    ///           @li 1. Accounting transaction - Cash account - Debit, Member Equity - Credit
    ///           @li 2. Member Investement Register - Increase number of member units
    /// @param[in] session: The database session to use.
    /// @param[in] memberID: The ID of the member investing.
    /// @param[in] investmentDate: The date of the investment
    /// @param[in] investmentValue: The value of the investment.
    /// @throws
    /// @version 2020-05-05/GGB - Function created.

    void memberInvestment(Wt::Dbo::Session &session, database::index_t memberID, std::tm investmentDate, double investmentValue)
    {
      std::string transactionGUID;
      std::string description("Member Investement");

        // Get the GUID for the cash account and the member equity account.

      std::string cashAccount = database::tbl_accountMapping::accountGUID(session,
                                                                          database::tbl_accountMapping::INVESTMENTCASHDEPOSIT);
      std::string memberEquity = database::tbl_accountMapping::accountGUID(session,
                                                                           database::tbl_accountMapping::MEMBERS_EQUITY);

      std::string currencyGUID = *database::tbl_accounts::commodityGUID(session, cashAccount);

        /* Create the transaction in the gnuCash 'transaction' table.
         * The insert transaction function does all the work, the function creates the GUID for the transaction and
         * inserts the transaction with the required data.
         * GUID - Needs to be created as this is not created by the database.
         * currencyGUID -
         * num -
         * post_date - Posting date, effective date.
         * enter_date - Entry date, date transaction has been entered
         * description - Description
         */

      transactionGUID = database::tbl_transactions::insertTransaction(session, currencyGUID, "", investmentDate, description);


    }
  }
}
