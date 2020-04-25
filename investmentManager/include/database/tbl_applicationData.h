//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_applicationData
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
// HISTORY:             2020-04-21/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef TBL_APPLICATIONDATA_H
#define TBL_APPLICATIONDATA_H

  // C++ standard library header files

#include <string>

  // Wt framework header files

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>

  // investmentManager header files

#include "include/database/databaseDefinitions.h"

namespace Wt
{
  namespace Dbo
  {
    // Specialise the default traits for the table. This is required as the table does not have a version field and also
    // does not use a surrogate ID field.

    template<>
    struct dbo_traits<database::tbl_applicationData> : public dbo_default_traits
    {
      typedef std::string IdType;

      static const char *versionField() { return 0; }
      static const char *surrogateIdField() { return 0; }
      static IdType invalidId() { return std::string(); }
    };
  } // namespace Dbo
} // namespace Wt

namespace database
{

  class tbl_applicationData
  {
  public:
    std::string token;
    std::string value;

    template<class Action>
    void persist(Action & a)
    {
      Wt::Dbo::id(a, token, "Token", 64);
      Wt::Dbo::field(a, value, "Value");
    }


    std::string const ACCOUNT_MEMBERSQUITY = "Account - Members Equity";
    std::string const ACCOUNT_TAXPAYABLE = "Account - Tax Payable";
  };

} // namespace database

#endif // TBL_APPLICATIONDATA_H
