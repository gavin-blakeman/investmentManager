﻿//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_transactions.h
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

#ifndef TBL_TRANSACTIONS_H
#define TBL_TRANSACTIONS_H

  // Standard C++ library headers

#include <cstdint>
#include <chrono>
#include <string>

  // Wt++ framework header files

#include <Wt/Dbo/Session.h>

namespace database
{
  class tbl_transactions
  {
  public:
    static std::string insertTransaction(Wt::Dbo::Session &, std::string const &, std::string const &, std::tm &, std::string const &);
  };
} // namespace database

#endif // TBL_TRANSACTIONS_H
