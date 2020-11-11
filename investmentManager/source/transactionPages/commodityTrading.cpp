//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                transactionPages/commodityTrading.cpp
// SUBSYSTEM:           Manage purchase/sale of commodities
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
// HISTORY:             2020-11-11/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/transactionPages/commodityTrading.h"

  // Standard C++ library header files

#include <memory>

  // Wt++ framework header files

#include "Wt/WContainerWidget.h"
#include "Wt/WGridLayout.h"
#include "Wt/WToolBar.h"

  // Miscellaneous library header files

#include "boost/locale.hpp"
#include <GCL>

  // investmentManager header files

#include "include/application.h"

namespace transactions
{

  /// @brief Constructor for the investor contributions page.
  /// @param[in] parent: The application that 'owns' this instance.
  /// @throws
  /// @version 2020-11-11/GGB - Function created.

  CCommodityTrading::CCommodityTrading(CApplication *parent) : CTransactionPage(parent)
  {
  }

  /// @brief        Responds to changes to the namespace
  /// @param[in]    selectedItem: The currently selected item
  /// @throws
  /// @version      2020-11-11/GGB - Function created.

  void CCommodityTrading::comboBoxNamespaceChanged(Wt::WString selectedItem)
  {
    Wt::Dbo::collection<std::tuple<std::string, std::string>> commodityCollection;

    comboBoxCommodity->clear();

    try
    {
      Wt::Dbo::Transaction transaction { application()->session() };

      commodityCollection = application()->session()
                            .query<std::tuple<std::string, std::string>>(
                                "SELECT DISTINCT commodities.mnemonic, commodities.fullname " \
                                "FROM commodities " \
                                "WHERE commodities.namespace=""?"" " \
                                "ORDER BY commodities.mnemonic")
                            .bind(selectedItem);
      for (auto commodity : commodityCollection)
      {
        comboBoxCommodity->addItem(std::get<0>(commodity) + " - " + std::get<1>(commodity));
      };
    }
    catch(Wt::Dbo::Exception &e)
    {
      ERRORMESSAGE(e.what());
    };
  }

  void CCommodityTrading::comboBoxCommodityChanged(Wt::WString)
  {

  }

  /// @brief        Creates the investor contribution page.
  /// @throws
  /// @version      2020-11-11/GGB - Function created.

  void CCommodityTrading::createPage()
  {
    std::unique_ptr<Wt::WPushButton> newButton;
    std::unique_ptr<Wt::WGridLayout> layout = std::make_unique<Wt::WGridLayout>();
    Wt::WText *newText;

    Wt::WContainerWidget *container = application()->getRightContainer();

    Wt::WToolBar *toolbar = layout->addWidget(std::make_unique<Wt::WToolBar>(), 0, 0);

      // Create the push buttons

    newButton = std::make_unique<Wt::WPushButton>("Buy");
    newButton->setEnabled(false);
    newButton->setToolTip("Enter a purchase transaction");
    pushButtonBuy = newButton.get();
    //pushButtonBuy->clicked().connect(this, &CEquipmentModelPage::pushButtonEditClicked);
    toolbar->addButton(std::move(newButton));

    newButton = std::make_unique<Wt::WPushButton>("Sell");
    newButton->setEnabled(false);
    newButton->setToolTip("Enter a sale transaction");
    pushButtonSell = newButton.get();
    //pushButtonSell->clicked().connect(this, &CEquipmentModelPage::pushButtonEditClicked);
    toolbar->addButton(std::move(newButton));

    newButton = std::make_unique<Wt::WPushButton>("Split");
    newButton->setEnabled(false);
    newButton->setToolTip("Enter a split transaction");
    pushButtonSplit = newButton.get();
    //pushButtonSplit->clicked().connect(this, &CEquipmentModelPage::pushButtonEditClicked);
    toolbar->addButton(std::move(newButton));

    newButton = std::make_unique<Wt::WPushButton>("Dividend");
    newButton->setEnabled(false);
    newButton->setToolTip(boost::locale::translate("Enter a dividend").str());
    pushButtonDividend= newButton.get();
    //pushButtonDividend->clicked().connect(this, &CEquipmentModelPage::pushButtonEditClicked);
    toolbar->addButton(std::move(newButton));

    toolbar->setOrientation(Wt::Orientation::Horizontal);

    newText = layout->addWidget(std::make_unique<Wt::WText>("Namespace"), 1, 0);
    newText->setStyleClass("Wt-outset");
    comboBoxNamespace = layout->addWidget(std::make_unique<Wt::WComboBox>(), 1, 1);
    comboBoxNamespace->setNoSelectionEnabled(true);
    comboBoxNamespace->setWidth(50);

    {
      Wt::Dbo::Transaction transaction { application()->session() };

      Wt::Dbo::collection<std::string> namespaceCollection;

      namespaceCollection = application()->session()
                            .query<std::string>("SELECT DISTINCT commodities.namespace " \
                                                "FROM commodities " \
                                                "ORDER BY commodities.namespace");
      for (auto ns : namespaceCollection)
      {
        comboBoxNamespace->addItem(ns);
      };
    };

    newText = layout->addWidget(std::make_unique<Wt::WText>("Commodity"), 2, 0);
    newText->setStyleClass("Wt-outset");
    comboBoxCommodity = layout->addWidget(std::make_unique<Wt::WComboBox>(), 2, 1);

    tableViewTransactions = layout->addWidget(std::make_unique<Wt::WTableView>(), 3, 0, 1, 2);

    comboBoxNamespace->sactivated().connect(this, &CCommodityTrading::comboBoxNamespaceChanged);
    comboBoxCommodity->sactivated().connect(this, &CCommodityTrading::comboBoxCommodityChanged);

    layout->setRowStretch(3, 2);
    layout->setColumnStretch(2, 2);

    container->setLayout(std::move(layout));
  }


} // namespace
