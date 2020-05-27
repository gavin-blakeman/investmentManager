//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                /core/transactions/assetValue.h
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

#ifndef ASSETVALUE_H
#define ASSETVALUE_H

  // Standard C++ library header files

#include <cstdint>
#include <ctime>
#include <string>

  // Wt++ framework header files

#include <Wt/Dbo/Session.h>

namespace core
{
  namespace accountTransactions
  {
    double netAssetValue(Wt::Dbo::Session &, std::tm &);
  }
}

#endif // ASSETVALUE_H
