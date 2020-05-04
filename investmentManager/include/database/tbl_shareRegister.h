//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_shareRegister
// SUBSYSTEM:           gnuCash prices table
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           database
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

#ifndef TBL_SHAREREGISTER_H
#define TBL_SHAREREGISTER_H

  // Standard C++ library header files

#include <ctime>
#include <memory>
#include <vector>

  // Wt++ framework header files

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Session.h>

  // investmentManager header files

#include <include/database/database>
#include "include/database/databaseDefinitions.h"
#include "include/database/databaseTables.h"

namespace database
{
  class tbl_shareRegister
  {
  public:

    static void addShareTransaction(Wt::Dbo::Session &, index_t, std::tm &, std::string const &, double, double, double);

  };    // class tbl_shareRegister


} // namespace database

#endif // TBL_SHAREREGISTER_H
