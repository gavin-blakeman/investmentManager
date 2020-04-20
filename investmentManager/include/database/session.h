//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                session.cpp
// SUBSYSTEM:           Database Session Management
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

#ifndef TBL_SESSION_H
#define TBL_SESSION_H

  // Standard C++ library header files.

#include <cstdint>
#include <memory>

  // Wt framework header files

#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/Login.h>
#include "Wt/Auth/PasswordService.h"
#include <Wt/Auth/Dbo/UserDatabase.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>

  // investmentManager header files

#include "include/database/database"

namespace database
{
  typedef std::uint64_t sqlIndex_t;

  class CSession : public Wt::Dbo::Session
  {
  private:
    std::unique_ptr<Wt::Auth::Dbo::UserDatabase<Wt::Auth::Dbo::AuthInfo<database::tbl_users>>> users_;
    Wt::Auth::Login login_;
    static Wt::Auth::AuthService authService;
    static Wt::Auth::PasswordService passwordService;

    void mapSQLClasses();

  public:
    CSession(Wt::Dbo::SqlConnectionPool *);
    Wt::Auth::AbstractUserDatabase &users();
    Wt::Auth::Login &login() { return login_; }
    std::string const &userID() const { return login_.user().id(); }

    Wt::Dbo::ptr<database::tbl_users> user() const;

    static void configureAuthorisation();
    static const Wt::Auth::AuthService &auth();
    static const Wt::Auth::PasswordService &passwordAuth();
  };

} // namespace database

#endif // TBL_SESSION_H
