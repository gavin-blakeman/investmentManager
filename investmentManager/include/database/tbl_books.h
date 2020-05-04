//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_books.h
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

#ifndef TBL_BOOKS_H
#define TBL_BOOKS_H

  // Standard C++ library header files

#include <string>

  // Wt++ framework header files

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Session.h>

namespace database
{
  class tbl_books
  {
  public:
    static std::string rootAccountGUID(Wt::Dbo::Session &);
  };

} // namespace database

#endif // TBL_BOOKS_H
