//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                models/menuModel.cpp
// SUBSYSTEM:           Main Menu Model - Provide the data for the main menu.
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

#ifndef MENUMODEL_H
#define MENUMODEL_H

  // Standard C++ library header files

#include <memory>
#include <string>

  // Wt++ framework header files

#include <Wt/WStandardItem.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WString.h>

  // investmentManager header files

#include "include/transactions.h"

namespace models
{
  class CMenuModel : public Wt::WStandardItemModel
  {
  private:
    void populateMenu(Wt::Dbo::Session &);

      // Remove unneeded constructors.

    CMenuModel() = delete;
    CMenuModel(CMenuModel const &) = delete;
    CMenuModel(CMenuModel const &&) = delete;
    CMenuModel &operator =(CMenuModel const &) = delete;

  public:
    CMenuModel(Wt::Dbo::Session &);


  };  // class CMenuModel

} // namespace models

#endif // MENUMODEL_H
