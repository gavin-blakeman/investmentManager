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

#ifndef TBL_SPLITS_H
#define TBL_SPLITS_H

  // Standard C++ library header files

#include <string>
#include <vector>

  // Wt++ framework header files

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Session.h>

namespace database
{
  class tbl_splits
  {
  public:
    struct split_t
    {
      std::string account_guid;
      std::string memo;
      std::string action;
      double value;
      double quantity;
    };
    using splits_t = std::vector<split_t>;

    static void insertSplits(Wt::Dbo::Session &, std::string const &, splits_t const &);
  };
}

#endif // TBL_SPLITS_H
