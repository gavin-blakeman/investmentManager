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
// HISTORY:             2020-04-19/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef TBL_ACCOUNTS_H
#define TBL_ACCOUNTS_H

  // Standard C++ library header files

#include <cstdint>
#include <string>
#include <tuple>
#include <utility>

  // Wt++ Framework header files

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Session.h>

  // Miscellaneous library header files

#include <SCL>

/* The accounts table has the following default layout;
 *  > guid - varchar(32)
 *  > name - varchar(2048)
 *  > account_type  - varchar(2048)
 *  > commodity_guid - varchar(32)
 *  > commodity_scu - int(11)
 *  > non_std_scu - int(11)
 *  > parent_guid - varchar(32)
 *  > code - varchar(2048)
 *  > description - varchar(2048)
 *  > hidden - int(11)
 *  > placeholder - int(11)
 *
 *  Values used for various columns are:
 *  > account_type
 *    >> ASSET
 *    >> INCOME
 *    >> EXPENSE
 *    >> EQUITY
 *    >> MUTUAL
 *    >> STOCK
 *    >> BANK
 *    >> ROOT
 *    >> LIABILITY
 *  > commodity_scu - Also referred to as smallest fraction. This is picked up from the commodity table
 *  > non_std_scu - Smallest fraction. This value is used if the smallest fraction from the commodity::fraction is overridden.
 */

namespace database
{
  class tbl_accounts
  {
  public:
    enum EAccountType
    {
      NONE,
      ASSET,
      INCOME,
      EXPENSE,
      EQUITY,
      MUTUAL,
      STOCK,
      BANK,
      ROOT,
      LIABILITY,
    };

    using accountHierarchy_t = SCL::hierarchy<std::string,                  ///< account.guid
                                              std::tuple<std::string,       ///< account.name
                                                         std::string,       ///< account.description
                                                         std::string,       ///< account.commodity_guid
                                                         std::int32_t,      ///< scu
                                                         double>>;          ///< value

    static void buildHierarchy(Wt::Dbo::Session &, EAccountType, accountHierarchy_t &);

    static std::optional<std::string> commodityGUID(Wt::Dbo::Session &, std::string const &);

  };  // class tbl_accounts

}   // namespace database

#endif // TBL_ACCOUNTS_H
