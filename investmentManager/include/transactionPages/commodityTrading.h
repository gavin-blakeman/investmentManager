//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                transactionPages/commodityTrading.h
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

#ifndef COMMODITYTRADING_H
#define COMMODITYTRADING_H

  // Wt++ framework header files

#include "Wt/WComboBox.h"
#include "Wt/WPushButton.h"
#include "Wt/WTableView.h"

  // investmentManager header files

#include "transactionPage.h"

namespace transactions
{

  class CCommodityTrading : public CTransactionPage
  {
  private:
    Wt::WPushButton *pushButtonBuy = nullptr;
    Wt::WPushButton *pushButtonSell = nullptr;
    Wt::WPushButton *pushButtonSplit = nullptr;
    Wt::WPushButton *pushButtonDividend = nullptr;
    Wt::WComboBox *comboBoxNamespace = nullptr;
    Wt::WComboBox *comboBoxCommodity = nullptr;
    Wt::WTableView *tableViewTransactions = nullptr;

    CCommodityTrading() = delete;
    CCommodityTrading(CCommodityTrading const &) = delete;
    CCommodityTrading(CCommodityTrading const &&) = delete;
    CCommodityTrading operator= (CCommodityTrading const &) = delete;

    void comboBoxNamespaceChanged(Wt::WString);
    void comboBoxCommodityChanged(Wt::WString);


  public:
    CCommodityTrading(CApplication *parent);

    virtual void createPage() override;

    static std::unique_ptr<CTransactionPage> createClass(CApplication *parent)
    {
      return std::make_unique<CCommodityTrading>(parent);
    }
  };

} // namespace transactions

#endif // COMMODITYTRADING_H
