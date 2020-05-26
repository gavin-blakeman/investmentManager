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

#ifndef MEMBERINVESTMENT_H
#define MEMBERINVESTMENT_H

  // Standard C++ library header files

#include <cstdint>
#include <ctime>

  // Wt++ framework header files

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Session.h>

  // InvestmentManager header files

#include "include/database/databaseDefinitions.h"

namespace core
{
  namespace accountTransactions
  {
    void memberInvestment(Wt::Dbo::Session &, database::index_t);
  }
}

#endif // MEMBERINVESTMENT_H
