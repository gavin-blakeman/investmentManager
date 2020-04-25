//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_prices
// SUBSYSTEM:           gnuCash prices table
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

#ifndef TBL_PRICES_H
#define TBL_PRICES_H

  // C++ standard library header files

#include <cstdint>
#include <string>

  // Wt++ framework header files

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Types.h>
#include <Wt/WAbstractTableModel.h>
#include <Wt/WGlobal.h>
#include <Wt/WDate.h>

  // Miscellaneous library header files

#include <MCL>

  // investmentManager header files

#include "include/database/databaseDefinitions.h"
#include "include/database/databaseTables.h"

namespace Wt
{
  namespace Dbo
  {
    // Specialise the default traits for the table. This is required as the table does not have a version field and also
    // does not use a surrogate ID field.

    template<>
    struct dbo_traits<database::tbl_prices> : public dbo_default_traits
    {
      typedef std::string IdType;

      static const char *versionField() { return 0; }       // Disable the version field. NO CHANGES TO TABLE STRUCTURE
      static const char *surrogateIdField() { return 0; }   // No surrogate primary key.
      static IdType invalidId() { return std::string(); }
    };


  } // namespace Dbo
} // namespace Wt

namespace database
{



  /// @brief The prices table is a standard gnuCash table. The table structure is not modified for the application. The
  ///        information in the table is however used, and there is also the provision to insert additional information into the
  ///        table for tracking commodity prices.
  /// @note 1. The table structure below is for v2 of the prices table. v3 uses a different structure.

  class tbl_prices
  {
  public:
    std::string guid;           ///< UUID primary key. (Note gnuCash uses this as the primary key) [32]
    std::string commodityGUID;  ///< UUID commodity key [32] -> tbl_commodities
    std::string currencyGUID;   ///< UUID currency key [32] -> tbl_commodities
    Wt::WDate date;             ///< Timestamp
    std::string source;         ///< Source of the price. ('Finance::Quote', 'user:price') [2048]
    std::string type;           ///< Type of price. (transaction, last) [2048]
    //MCL::CFraction value;

    template<class Action>
    void persist(Action & a)
    {
//      Wt::Dbo::id(a, guid, "guid", 32);
//      Wt::Dbo::field(a, commodityGUID, "commodity_guid");
//      Wt::Dbo::field(a, currencyGUID, "currency_guid");
//      Wt::Dbo::field(a, date, "date");
//      Wt::Dbo::field(a, source, "source");
//      Wt::Dbo::field(a, type, "type");
    }
  };

  std::string const SOURCE_FINANCE = "Finance::Quote";
  std::string const SOURCE_USER = "user:price";
  std::string const TYPE_TRANSACTION = "transaction";
  std::string const TYPE_LAST = "last";



} // namespace database

#endif // TBL_PRICES_H
