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

#include "../include/application.h"

  // Standard C++ library header files.

#include <stdexcept>

  // Wt Framework header files.

#include <Wt/WBootstrapTheme.h>
#include <Wt/WBreak.h>
#include <Wt/WGridLayout.h>
#include <Wt/WLabel.h>
#include <Wt/WMenu.h>
#include <Wt/WMenuItem.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WTemplate.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Auth/RegistrationWidget.h>

  // Miscellaneous library header files

#include <boost/lexical_cast.hpp>

  // investmentManager header files

#include <include/database/database>
#include "include/configSettings.h"
#include "include/views/menuView.h"

/// @brief Class constructor.
/// @param[in] env: The environment being used.
/// @param[in] connectionPool: The shared connection pool for database access use.
/// @version 2020-04-19/GGB - Function created.

CApplication::CApplication(Wt::WEnvironment const &env, Wt::Dbo::SqlConnectionPool *connectionPool)
  : Wt::WApplication(env), currentTransactionPage(nullptr), userData_(), sqlSession_(connectionPool)
{
  sqlSession_.login().changed().connect(this, &CApplication::authenticationEvent);

  messageResourceBundle().use(appRoot() + "resources/wt-home", false);
  useStyleSheet("wt.css");
  setCssTheme("polished");

  setTitle(APPLICATION_NAME);

  createUI();
  createLoginUI();
}

/// @brief Responds to the authentication event.
/// @throws
/// @version 2020-04-19/GGB - Function created.

void CApplication::authenticationEvent()
{
  if (sqlSession_.login().loggedIn())
  {
    //std::cout << "UserID: " << sqlSession_.userID() << std::endl;

    menuModel = std::make_shared<models::CMenuModel>(sqlSession_);

    //loadMenuData(sqlSession_);
    //createTransactionMap();

    createAfterLoginUI();
  }
  else
  {
    std::cout << "User logged out" << std::endl;
  }
}

/// @brief Creates the menu view.
/// @throws
/// @version 2020-04-19/GGB - Function created.

std::unique_ptr<Wt::WTreeView> CApplication::createMenuView()
{
  auto treeView = std::make_unique<CMenuView>(this, menuModel);

  menuView = treeView.get();

  return std::move(treeView);
}

/// @brief Creates the UI after a user is logged in.
/// @version 2020-04-19/GGB - Function created.

void CApplication::createAfterLoginUI()
{
    // Remove the login information.

  gridLayout->removeWidget(loginWidget);
  loginWidget = nullptr;

  gridLayout->addWidget(createMenuView(), 0, 0, 2, 1);
  auto nb = std::make_unique<Wt::WHBoxLayout>();
  navigationBar = nb.get();
  gridLayout->addLayout(std::move(nb), 0, 1);

  auto tt = std::make_unique<Wt::WLineEdit>("IP000");
  transactionText = tt.get();
  transactionText->setStyleClass("nav-menu");
  navigationBar->addWidget(std::move(tt));
  auto rightMenu = std::make_unique<Wt::WMenu>();
  rightMenu->setStyleClass("nav-menu");

  auto popupMenu = std::make_unique<Wt::WPopupMenu>();
  popupMenu->setStyleClass("nav-menu");
  popupMenu->addItem("Change Password");
  popupMenu->addSeparator();
  popupMenu->addItem("Logout");

  auto menuItem = std::make_unique<Wt::WMenuItem>("User Settings");
  menuItem->setMenu(std::move(popupMenu));
  menuItem->setStyleClass("nav-menu");

  rightMenu->addItem(std::move(menuItem));

  navigationBar->addWidget(std::move(rightMenu));
}

/// @brief Creates the login UI. This uses the leftContainer and sets up the login screen there.
/// @throws
/// @version 2020-04-19/GGB - Function created.

void CApplication::createLoginUI()
{
  //setTheme(std::make_shared<Wt::WBootstrapTheme>());
  //w->addStyleClass("container");
  //useStyleSheet("css/style.css");

  std::unique_ptr<Wt::Auth::AuthWidget> authWidget = std::make_unique<Wt::Auth::AuthWidget>(database::CSession::auth(),
                                                                                            sqlSession_.users(),
                                                                                            sqlSession_.login());

  authWidget->model()->addPasswordAuth(&database::CSession::passwordAuth());
  authWidget->processEnvironment();
  loginWidget = authWidget.get();

  std::unique_ptr<Wt::Auth::RegistrationModel> regModel = std::make_unique<Wt::Auth::RegistrationModel>(database::CSession::auth(),
                                                               sqlSession_.users(),
                                                               sqlSession_.login());
//  regModel->addPasswordAuth(&database::CSession::passwordAuth());
//  auto regWidget = std::make_unique<Wt::Auth::RegistrationWidget>();
//  regWidget->setModel(std::move(regModel));

//  rightContainer->addWidget(std::move(regWidget));

  gridLayout->addWidget(std::move(authWidget), 0, 0, 2, 1);

  if (sqlSession_.login().loggedIn())
  {
    createAfterLoginUI();
  };

}

/// @brief Function to create the transaction map data.
/// @throws std::bad_alloc
/// @version 2020-04-19/GGB - Function created.
/// @note 1. I tried to do this as an initialiser list, but no joy. There must be an easier way!!!

void CApplication::createTransactionMap()
{

//  transactionPages.emplace(TC::CD001, std::make_pair(std::unique_ptr<transactions::CTransactionPage>(),
//                                                     transactions::CChemicalDataPage::createClass));
}

/// @brief Creates the initial UI. This will be modified as required by the various transactions.
/// @version 2020-04-19/GGB - Function created.

void CApplication::createUI()
{
  root()->setStyleClass("maindiv");

    /* Main Layout is a 1 x 2 layout. */

  gridLayout = root()->setLayout<Wt::WGridLayout>(std::make_unique<Wt::WGridLayout>());

  rightContainer = gridLayout->addWidget(std::make_unique<Wt::WContainerWidget>(), 1, 1);

  gridLayout->setColumnResizable(0);
  gridLayout->setRowStretch(1, 1);
  gridLayout->setColumnStretch(1, 1);
}

/// @brief Function called to empty the right container. This is done as required when the content of the right container needs to
///        change.
/// @param[in] transactionID - The ID number of the transaction to start.
/// @version 2020-04-19/GGB - Function created.

void CApplication::emptyDataContainer()
{
  rightContainer->clear();
}

/// @brief Callback function for menu transactions.
/// @param[in] transactionID - ID of the transaction to start.
/// @version 2020-04-19/GGB - Function created.

void CApplication::menuCallback(transaction_t transactionID)
{
  transactionStorage_t::iterator transactionIterator;

  emptyDataContainer();
  //transactionText->setText(menuMap.find(transactionID)->second.transactionCode);

  transactionIterator = transactionPages.find(transactionID);
  if (transactionIterator != transactionPages.end())
  {
    currentTransactionPage = (*transactionIterator).second.first.get();
    if (!currentTransactionPage)
    {
      (*transactionIterator).second.first = (*transactionIterator).second.second(this);
      currentTransactionPage = (*transactionIterator).second.first.get();
      if (!currentTransactionPage)
      {
        throw std::runtime_error("Unable to create transaction page.");
      };
    };
    currentTransactionPage->createPage();
  };
}

/// @brief Function to determine the user permissions for transactions.
/// @param[in] transactionID: The ID of the transaction to check.
/// @param[out] transactionPermissions: The permissions to associate with the transaction.
/// @throws
/// @version 2020-04-19/GGB - Function created.

void CApplication::transactionPermissions(transaction_t transactionID, SRecordPermissions &transactionPermissions)
{
  try
  {
    std::uint32_t userID = boost::lexical_cast<std::uint32_t>(sqlSession_.login().user().id());
    userData_.transactionPermissions(userID, transactionID, transactionPermissions);
  }
  catch(boost::bad_lexical_cast &e)
  {
    std::cerr << e.what() << std::endl;
  }
}

/// @brief Factory function for creating the application.
/// @param[in] env: The environment values.
/// @param[in] connectionPool: The connection pool to use for a connection.
/// @version  2020-04-19/GGB - Function created.

std::unique_ptr<Wt::WApplication> createApplication(Wt::WEnvironment const &env, Wt::Dbo::SqlConnectionPool *connectionPool)
{
  return std::make_unique<CApplication>(env, connectionPool);
}



