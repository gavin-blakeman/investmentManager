//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                priceManager.cpp
// SUBSYSTEM:           Manage Commodity/Share Prices
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
// HISTORY:             2020-04-22/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/transactionPages/priceManager.h"

  // Standard C++ library header files

#include <tuple>
#include <utility>

  // Wt++ framework header files.

#include <Wt/Dbo/QueryModel.h>
#include <Wt/WAbstractItemModel.h>
#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WGridLayout.h>
#include <Wt/WLabel.h>
#include <Wt/WMessageBox.h>
#include <Wt/WRegExpValidator.h>
#include <Wt/WSelectionBox.h>
#include <Wt/WTableView.h>
#include <Wt/WText.h>
#include <Wt/WToolBar.h>

  // Miscellaneous library header files

#include <boost/algorithm/string.hpp>

  // investmentManager header files

#include <include/database/database>
#include "include/application.h"
#include "include/permissionSystem.h"

namespace transactions
{

  /// @brief Constructor for the class.
  /// @param[in] parent: The parent object.
  /// @version 2020-04-22/GGB - Function created.

  CPriceManager::CPriceManager(CApplication *parent) : CTransactionPage(parent)
  {
  }

  /// @brief Responds to changes to the namespace
  /// @param[in] selectedItem: The currently selected item
  /// @throws
  /// @version 2020-04-24/GGB - Function created.

  void CPriceManager::comboBoxNamespaceChanged(Wt::WString selectedItem)
  {
    Wt::Dbo::collection<std::tuple<std::string, std::string>> commodityCollection;

    selectionBoxCommodity->clear();

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
        selectionBoxCommodity->addItem(std::get<0>(commodity) + " - " + std::get<1>(commodity));
      };
    }
    catch(Wt::Dbo::Exception &e)
    {
      std::cerr << e.what() << std::endl;
    };
  }

  /// @brief Creates the UI for the business unit view transaction.
  /// @throws
  /// @version 2020-04-16/GGB - Function created.

  void CPriceManager::createPage()
  {
    std::unique_ptr<Wt::WPushButton> newButton;
    SRecordPermissions permissions;

    application()->transactionPermissions(TC::MD120, permissions);

    Wt::WContainerWidget *container = application()->getRightContainer();

    std::unique_ptr<Wt::WGridLayout> layout = std::make_unique<Wt::WGridLayout>();

    Wt::WToolBar *toolbar = layout->addWidget(std::make_unique<Wt::WToolBar>(), 0, 0, 1, 2);

      // Create push button.

    newButton = std::make_unique<Wt::WPushButton>("Create");
    newButton->setToolTip("Create a new component record.");
    pushButtonCreate = newButton.get();
    pushButtonCreate->clicked().connect(this, &CPriceManager::pushButtonCreateClicked);
    toolbar->addButton(std::move(newButton));

      // Edit push button.

    newButton = std::make_unique<Wt::WPushButton>("Edit");
    newButton->setEnabled(false);
    newButton->setToolTip("Edit the selected component record");
    pushButtonEdit = newButton.get();
    toolbar->addButton(std::move(newButton));

      // Delete push button

    newButton = std::make_unique<Wt::WPushButton>("Delete");
    newButton->setEnabled(false);
    newButton->setToolTip("Delete an existing component record");
    pushButtonDelete = newButton.get();
    pushButtonDelete->clicked().connect(this, &CPriceManager::pushButtonDeleteClicked);
    toolbar->addButton(std::move(newButton));

      // Upload push button

    newButton = std::make_unique<Wt::WPushButton>("Upload");
    newButton->setEnabled(false);
    newButton->setToolTip("Upload commodity prices");
    pushButtonUpload = newButton.get();
    toolbar->addButton(std::move(newButton));

    toolbar->setOrientation(Wt::Orientation::Horizontal);

    layout->addWidget(std::make_unique<Wt::WLabel>("Namespace"), 1, 0);
    comboBoxNamespace = layout->addWidget(std::make_unique<Wt::WComboBox>(), 2, 0);
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
    comboBoxNamespace->sactivated().connect(this, &CPriceManager::comboBoxNamespaceChanged);

    layout->addWidget(std::make_unique<Wt::WLabel>("Commodity"), 3, 0);

    selectionBoxCommodity = layout->addWidget(std::make_unique<Wt::WSelectionBox>(), 4, 0);
    selectionBoxCommodity->setWidth(400);
    selectionBoxCommodity->sactivated().connect(this, &CPriceManager::selectionBoxCommodityChanged);

    layout->addWidget(std::make_unique<Wt::WLabel>(), 5, 0);    // Spaceholder to allow row stretch

    try
    {
      tableViewPrices = layout->addWidget(std::make_unique<Wt::WTableView>(), 1, 1, 4, 1);
      tableViewPrices->resize(Wt::WLength::Auto, Wt::WLength::Auto);

      queryModelPrices = std::make_shared<models::CPricesModel>(application()->session());
      queryModelPrices->changeCommodity("");

      tableViewPrices->setModel(queryModelPrices);
      tableViewPrices->setAlternatingRowColors(true);
      tableViewPrices->setSelectionMode(Wt::SelectionMode::Single);
      tableViewPrices->setSelectionBehavior(Wt::SelectionBehavior::Rows);
      tableViewPrices->setSortingEnabled(false);
      //tableViewPrices->selectionChanged().connect(this, &CPriceManager::tableViewEquipmentClassChanged);

    }
    catch (std::exception &e)
    {
      std::cerr << "exception: " << e.what() << std::endl;
    }

    layout->setRowStretch(5, 2);
    layout->setColumnStretch(1, 2);

    container->setLayout(std::move(layout));
  }

  /// @brief Responds to the create push button being pressed. Opens the dialog to create.
  /// @throws
  /// @version 2020-04-22/GGB - Function created.

  void CPriceManager::pushButtonCreateClicked()
  {
    //SRecordPermissions dialogUsage{ 1, 1, 1, 1};
    //addChild(std::make_unique<dialogs::CBusinessUnit>(parent_, this, dialogUsage));
  }

  /// @brief Handles the deletion button press.
  /// @throws
  /// @version 2020-04-22/GGB - Function created.

  void CPriceManager::pushButtonDeleteClicked()
  {
    //Wt::WModelIndexSet selectedRow = tableViewComponent->selectedIndexes();    // Only 1 value shoud be returned.

    auto messageBox = addChild(std::make_unique<Wt::WMessageBox>("Confirm Delete",
                                                                 "<p>Delete the Class</p>",
                                                                 Wt::Icon::Information,
                                                                 Wt::StandardButton::Yes | Wt::StandardButton::No));
    messageBox->setModal(true);

    messageBox->buttonClicked().connect([=]
    {
      if (messageBox->buttonResult() == Wt::StandardButton::Yes)
      {
        //Wt::Dbo::ptr<database::tbl_equipmentComponents> toDelete = queryModelComponent->resultRow(selectedRow.begin()->row());

        {
          Wt::Dbo::Transaction transaction{parent_->session()};

          //toDelete.modify()->removed = true;
        };

        refreshTableView();
      };
      removeChild(messageBox);
    });

    messageBox->show();
  }

  /// @brief Function called to refresh the data in the table view after a change.
  /// @throws
  /// @version 2020-04-22/GGB - Function created.

  void CPriceManager::refreshTableView()
  {
    tableViewPrices->refresh();
  }

  /// @brief Updates the query when the selected commodity is changed.
  /// @param[in] selectedItem: The name of the commodity currently selected.
  /// @throws
  /// @version 2020-04-24/GGB - Function created.

  void CPriceManager::selectionBoxCommodityChanged(Wt::WString selectedItem)
  {
    Wt::Dbo::collection<std::string> commodityCollection;

    std::string commodityName(selectedItem.toUTF8());
    std::string commodityGUID;

    commodityName = commodityName.substr(0, commodityName.find("-"));
    boost::trim(commodityName);

    try
    {
      Wt::Dbo::Transaction transaction { application()->session() };
      std::string szSQL = "SELECT commodities.guid " \
                          "FROM commodities " \
                          "WHERE commodities.mnemonic = '" + commodityName + "'";

      commodityCollection = application()->session()
                            .query<std::string>(szSQL);

      commodityGUID = commodityCollection.front();
    }
    catch(Wt::Dbo::Exception &e)
    {
      std::cerr << e.what() << std::endl;
    };

    queryModelPrices->changeCommodity(commodityGUID);
    tableViewPrices->refresh();
  }

} // namespace transactions
