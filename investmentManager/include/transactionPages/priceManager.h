//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                priceManager.h
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

#ifndef PRICEMANAGER_H
#define PRICEUPLOAD_H

  // Standard C++ library header files

#include <memory>

  // Wt++ framework header files


  // Investment Manager header files

#include <include/database/database>
#include "include/models/pricesModel.h"
#include "include/transactionPages/transactionPage.h"

namespace transactions
{

  class CPriceManager : public CTransactionPage
  {
    Wt::WPushButton *pushButtonCreate = nullptr;
    Wt::WPushButton *pushButtonEdit = nullptr;
    Wt::WPushButton *pushButtonDelete = nullptr;
    Wt::WPushButton *pushButtonUpload = nullptr;
    Wt::WComboBox *comboBoxNamespace = nullptr;
    Wt::WSelectionBox *selectionBoxCommodity = nullptr;
    Wt::WTableView *tableViewPrices= nullptr;

    std::shared_ptr<models::CPricesModel> queryModelPrices;

    void pushButtonCreateClicked();
    void pushButtonEditClicked();
    void pushButtonDeleteClicked();
    void pushButtonUploadClicked();

    void comboBoxNamespaceChanged(Wt::WString);
    void selectionBoxCommodityChanged(Wt::WString);

    CPriceManager() = delete;
    CPriceManager(CPriceManager const &) = delete;
    CPriceManager(CPriceManager &&) = delete;
    CPriceManager &operator=(CPriceManager const &) = delete;

  public:
    CPriceManager(CApplication *);

    virtual void createPage() override;

    void refreshTableView();

    static std::unique_ptr<CTransactionPage> createClass(CApplication *parent)
    {
      return std::make_unique<CPriceManager>(parent);
    }

  };

} // namespace transactions

#endif // PRICEMANAGER_H
