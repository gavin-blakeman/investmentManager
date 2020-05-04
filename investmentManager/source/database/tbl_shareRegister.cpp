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

#include "include/database/tbl_shareRegister.h"

namespace database
{

  /// @brief Inserts a share transaction into the database.
  /// @param[in] session:


  void tbl_shareRegister::addShareTransaction(Wt::Dbo::Session &, index_t, std::tm &, std::string const &, double, double, double)
  {

  }

} // namespace database
