//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                application.cpp
// SUBSYSTEM:           Main Application File
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

#ifndef APPLICATION_H
#define APPLICATION_H

  // Standard C++ header files

#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>

  // Wt Header files.

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WMenu.h>
#include <Wt/WPushButton.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WText.h>
#include <Wt/WTextArea.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/Dbo/FixedSqlConnectionPool.h>

  // investmentManager header files.

#include "models/menuModel.h"
#include "permissionSystem.h"
#include "transactions.h"
#include "database/session.h"
#include "transactionPages/transactionPage.h"

class CApplication : public Wt::WApplication
{
private:
  typedef std::unordered_map<transaction_t,
                             std::pair<std::unique_ptr<transactions::CTransactionPage>,
                                       std::function<std::unique_ptr<transactions::CTransactionPage>(CApplication *)>>> transactionStorage_t;

  transactionStorage_t transactionPages;

  transactions::CTransactionPage *currentTransactionPage = nullptr;

  CUserData userData_;
  std::shared_ptr<models::CMenuModel> menuModel;

  Wt::WGridLayout *gridLayout = nullptr;
  Wt::WContainerWidget *rightContainer = nullptr;

  Wt::WTreeView *menuView = nullptr;
  Wt::WHBoxLayout *navigationBar = nullptr;
  Wt::WLineEdit *transactionText = nullptr;

  Wt::Auth::AuthWidget *loginWidget = nullptr;


  database::CSession sqlSession_;

  void createTransactionMap();
  void createUI();
  void createLoginUI();
  void createAfterLoginUI();
  std::unique_ptr<Wt::WTreeView> createMenuView();
  void emptyDataContainer();
  void authenticationEvent();

protected:
public:
  CApplication(Wt::WEnvironment const &env, Wt::Dbo::SqlConnectionPool *);

  Wt::Dbo::Session &session() { return sqlSession_; }

  void menuCallback(transaction_t);
  Wt::WContainerWidget *getRightContainer() { return rightContainer; }

  void transactionPermissions(transaction_t, SRecordPermissions &);

};

std::unique_ptr<Wt::WApplication> createApplication(Wt::WEnvironment const &, Wt::Dbo::SqlConnectionPool *);

#endif // APPLICATION_H
