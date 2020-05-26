//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                mainMenu.cpp
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

#ifndef MENUDATA_H
#define MENUDATA_H

  // Standard C++ library header files.

#include <cstdint>
#include <map>
#include <utility>

// Wt framework header files

#include <Wt/Dbo/Session.h>

  // SAMAP55 header files.

#include "menuConstants.h"

struct SMenuEntry
{
  transaction_t parentID;
  std::string   menuText;
  std::string   transactionCode;
  bool          selectable;
  std::uint8_t  menuLevel;

  //SMenuEntry(transaction_t pid, std::string const &mt, std::string const &tc, bool s, std::uint8_t ml)
  //  : parentID(pid), menuText(mt), transactionCode(tc), selectable(s), menuLevel(ml) {}

};

extern std::map<transaction_t, SMenuEntry> menuMap;


void loadMenuData(Wt::Dbo::Session &sqlSession);


#endif // MENUDATA_H
