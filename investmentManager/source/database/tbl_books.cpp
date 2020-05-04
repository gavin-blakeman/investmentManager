//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_books.cpp
// SUBSYSTEM:           Table management to match the gnuCash 'books' table.
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
// HISTORY:             2020-05-04/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/database/tbl_books.h"

  // Standard C++ library header files

#include <exception>

  // Wt++ framework header files

#include <Wt/Dbo/Exception.h>
#include <Wt/Dbo/Transaction.h>

  // Miscellaneous library header files

#include <GCL>

namespace database
{
  /// @brief Returns the root account GUID for the books.
  /// @param[in] session: The sesion to use for database access.
  /// @returns A string containing the GUID.
  /// @throws std::runtime_error
  /// @version 2020-05-04/GGB - Function created.

  std::string tbl_books::rootAccountGUID(Wt::Dbo::Session &session)
  {
    GCL::sqlwriter::CSQLWriter sqlWriter;

    sqlWriter.select({"root_account_guid"}).from("books");
    std::string returnValue;

    try
    {
      Wt::Dbo::Transaction transaction { session };

      returnValue = session.query<std::string>(sqlWriter.string());
    }
    catch(Wt::Dbo::Exception const &e)
    {
        // This is a critical error as we cannot open the books. Might as well throw and exit.

      CRITICALMESSAGE(e.what());
      throw std::runtime_error(e.what());
    };

    return returnValue;
  }
}
