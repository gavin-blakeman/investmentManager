//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_users
// SUBSYSTEM:           User Database Table definitions
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

#ifndef TBL_USERS_H
#define TBL_USERS_H

  // Standard C++ library headers

#include <stdint.h>
#include <string>

  // Wt framework header files

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>

  // investmentManager header files

#include "include/database/databaseDefinitions.h"

namespace database
{

  class tbl_users
  {
  public:
    index_t role;
    std::string surname;
    std::string firstName;

    template<class Action>
    void persist(Action & a)
    {
    }
  };

} // namespace database


DBO_EXTERN_TEMPLATES(database::tbl_users)

#endif // TBL_USERS_H
