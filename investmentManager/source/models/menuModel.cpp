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
// OVERVIEW:						Sub-system for managing the application
//
// HISTORY:             2020-04-19/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/models/menuModel.h"

  // Standard C++ library header files.

#include <any>

  // Wt++ library header files

#include <Wt/Dbo/collection.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Transaction.h>

  // Miscellaneous library header files

#include <GCL>
#include <SCL>

  // investmentManager header files.



namespace models
{

//  struct SMenuEntry
//  {
//    transaction_t parentID;
//    std::string   menuText;
//    std::string   transactionCode;
//    bool          selectable;
//    std::uint8_t  menuLevel;

//    //SMenuEntry(transaction_t pid, std::string const &mt, std::string const &tc, bool s, std::uint8_t ml)
//    //  : parentID(pid), menuText(mt), transactionCode(tc), selectable(s), menuLevel(ml) {}

//  };

//  typedef std::map<transaction_t, SMenuEntry> menuMap_t;

  /// @brief Constructor for the menu model. This also loads the data from the menu data table.
  /// @param[in] sqlSession: The SQL session to use for loading the data.
  /// @pre The user must be authenticated as the user ID is needed to load the relevant transactions only.
  /// @throws std::bad_alloc
  /// @version 2020-04-20/GGB - Function created.

  CMenuModel::CMenuModel(Wt::Dbo::Session &sqlSession) : WStandardItemModel()
  {
    populateMenu(sqlSession);
  }

  /// @brief Creates the main menu for the application. This is loaded from the SQL database and is performed per user, based on
  ///        the transactions that the user is allowed to access.
  /// @param[in] sqlSession: The session to use.
  /// @version 2019-10-10/GGB - Function created.

  void CMenuModel::populateMenu(Wt::Dbo::Session &sqlSession)
  {
    using hierarchy_t = SCL::hierarchy<transaction_t, std::pair<std::string, std::string>, 0>;

      /* A map is used rather than a vector, as a vector needs the [] operator to refer to already constructed objects.
       * the map [] creates an object as required. */

    hierarchy_t menuHierarchy;
    std::map<SCL::hierarchy<std::int32_t, std::string, 0>::size_type, Wt::WStandardItem *> levelPointers;
    hierarchy_t::iterator iterator;
    hierarchy_t::iterator::size_type level;
    std::unique_ptr<Wt::WStandardItem> newItem;

    {
      Wt::Dbo::Transaction transaction { sqlSession };

      Wt::Dbo::collection<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::string, std::string>> transactionResult;

      transactionResult = sqlSession.query<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::string, std::string>>
              ("SELECT DISTINCT tbl_transactions.ID, tbl_transactions.parentID, "
               "                tbl_transactions.SortOrder, tbl_transactions.MenuText, tbl_transactions.TransactionCode " \
               "FROM tbl_transactions");

      for (auto iterator = transactionResult.begin(); iterator != transactionResult.end(); ++iterator)
      {
//        menuHierarchy.insert(std::get<0>(*iterator), std::get<1>(*iterator),
//                             std::make_pair(std::get<2>(*iterator) + " - " + std::get<3>(*iterator),
//                                            std::get<4>(*iterator).empty() ? false : true));
      };
    };

    clear();  // Clear the data from the WStandardItemModel

    for(iterator = menuHierarchy.begin(); iterator != menuHierarchy.end(); ++iterator)
    {
      level = std::get<0>(*iterator);     // Level in the hierarchy

      //std::string itemName = std::get<2>(*iterator);    // Not sure why this is working.

      //newItem = std::make_unique<Wt::WStandardItem>(itemName);
      newItem->setData(std::get<1>(*iterator), Wt::ItemDataRole::User); // Index = transaction ID

      if (level == 0) // Special case for level 0.
      {
        levelPointers[level] = newItem.get();
        appendRow(std::move(newItem));
      }
      else
      {
        levelPointers[level] = newItem.get();
        levelPointers[level-1]->appendRow(std::move(newItem));
      };
    };

    setHeaderData(0, Wt::Orientation::Horizontal, std::string("Main Menu"));

  }

} // namespace models
