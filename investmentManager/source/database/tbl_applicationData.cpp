//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_applicationData.cpp
// SUBSYSTEM:           Table used for storing application related data.
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
// OVERVIEW:            The application data table is used for storing data used by the application to access the gnuCash tables.
//                      This data is setup by using various application management functions found under the 'Application Data'
//                      menu functions. The data stored in the table is used for connections within the database and it is not
//                      prudent to store this in configuration files.
//
// HISTORY:             2020-05-09/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/database/tbl_applicationData.h"

  // Wt++ framework header files

#include <Wt/Dbo/Exception.h>
#include <Wt/Dbo/Transaction.h>

  // Miscellaneous library header files

#include <GCL>


namespace database
{
  static std::unordered_map<tbl_applicationData::EApplicationData, std::string> applicationDataMap =
  {
    {tbl_applicationData::ACCOUNT_MEMBERSQUITY, "Account - Members Equity"},
    {tbl_applicationData::ACCOUNT_TAXPAYABLE, "Account - Tax Payable"},
    {tbl_applicationData::DEFAULT_CURRENCY, "Default Currency"}
  };

  /// @brief S
  /// @param[in[ session: The session to use to access the database
  /// @param[in] applicationData: The application data index to access.
  /// @returns The relevant session data as a string.
  /// @throws
  /// @version 2020-05-09/GGB - Function created.

  std::string tbl_applicationData::applicationData(Wt::Dbo::Session &session, EApplicationData applicationData)
  {
    Wt::Dbo::Transaction transaction(session);

    GCL::sqlWriter sqlWriter;

    sqlWriter.select({"Value"}).from("im_applicationData").where("ID", "=", applicationData);
    std::string value = session.query<std::string>(sqlWriter.string());

    return value;

  }

}
