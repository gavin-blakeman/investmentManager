//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                menuView.cpp
// SUBSYSTEM:
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

#include "include/views/menuView.h"

  // Standard C++ library header files.

#include <any>

  // investmentmanager header files.

#include "include/application.h"
#include "include/transactions.h"

/// @brief Constructor for the menu tree view.
/// @param[in] np: The application object that owns this.
/// @param[in] menuModel: The menu model containing the menu data.
/// @throws std::bad_alloc
/// @version 2020-04-19/GGB - Function created.

CMenuView::CMenuView(CApplication *np, std::shared_ptr<models::CMenuModel> &menuModel) : Wt::WTreeView(), parent(np)
{
  setModel(menuModel);
  resize(500, Wt::WLength::Auto);
  setLayoutSizeAware(true);
  setSelectionMode(Wt::SelectionMode::Single);
  setSortingEnabled(false);
  expandToDepth(0);
  selectionChanged().connect(this, &CMenuView::menuItemChanged);
}


/// @brief Function called when the menu item that is selected is changed.
/// @note 1. There is the possibility of exceptions being raised during the std::any_cast process. These are intentionally kept
///          within this function and not allowed to propogate.
/// @version 2020-04-19/GGB - Function created.

void CMenuView::menuItemChanged()
{
  if (!selectedIndexes().empty())
  {
    Wt::WModelIndex selected = *selectedIndexes().begin();
    std::any d = selected.data(Wt::ItemDataRole::User);
    if (d.has_value())
    {
      std::uint16_t menuItem;
      try
      {
        menuItem = std::any_cast<transaction_t>(d);

          // Need to dispatch the signal in some way.

        parent->menuCallback(menuItem);

      }
      catch(...)
      {

      };
    }
    else
    {
      std::cout << "No User Data!" << std::endl;
    }
  }
}
