//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                /core/transactions/assetValue.cpp
// SUBSYSTEM:           Function to detemine total asset value
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
// HISTORY:             2020-05-27/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/core/accountTransactions/assetValue.h"

  // investmentManager header files

#include "include/database/tbl_accounts.h"

namespace core
{
  namespace accountTransactions
  {
    /// @brief Determine the total asset value of a fund.
    /// @param[in] session: The dbo session to utilise.
    /// @param[in] date: The date to determine the asset value as at.
    /// @throws
    /// @version 2020-05-27/GGB - Function created.

    double netAssetValue(Wt::Dbo::Session &session, std::tm &date)
    {
        /* To sum the values of the various accounts us not as simple as summing the values in the tables as the num, denom
         * storage of data can create issues. The denom appears to be either 100 or 1, it is still not possible to sum the values
         * in the database.
         *
         * To sum the asset values, it is necessary to enumerate each account in the asset hierarchy in turn, pull all the
         * transactions and calculate all the transactions. This is highly inefficient, but is largely driven by the design on the
         * gnuCash database.
         *
         * In order to calculate the asset value, we will need to get all the asset and liability accounts hierarchies and to
         * calculate all the values.
         */

      database::tbl_accounts::accountHierarchy_t assetAccountHierarchy("");
      database::tbl_accounts::accountHierarchy_t liabilityAccountHierarchy("");

      database::tbl_accounts::buildHierarchy(session, database::tbl_accounts::ASSET, assetAccountHierarchy);
      database::tbl_accounts::buildHierarchy(session, database::tbl_accounts::LIABILITY, liabilityAccountHierarchy);
    }
  }
}
