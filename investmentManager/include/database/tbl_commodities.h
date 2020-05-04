//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_commodities
// SUBSYSTEM:           gnuCash Commodities table
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
// OVERVIEW:            The commodities table is organised as a namespace:mnemonic pair. The namespace does not sit in a different
//                      table, so the data is stored multiple times in the table.
//
// HISTORY:             2020-04-19/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef TBL_COMMODITIES_H
#define TBL_COMMODITIES_H

  // C++ standard library header files

#include <cstdint>
#include <optional>
#include <string>

  // Wt++ framework header files

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Types.h>
#include <Wt/Dbo/Session.h>
#include <Wt/WGlobal.h>

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
    struct dbo_traits<database::tbl_commodities> : public dbo_default_traits
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

  /// @brief The commodities table is a standard gnuCash table. The table structure is not modified for the application. The
  ///        information in the table is however used, and there is also the provision to insert additional information into the
  ///        table for tracking further commodities.

  class tbl_commodities
  {
  public:
    std::string guid;         ///< UUID identifying the commodity. (Note gnuCash uses this as the primary key) [32]
    std::string namespc;      ///< Namespace for the quote. This is the exchange (ASX, NYSE etc) [2048]
    std::string mnemonic;     ///< Mnemonic for the commodity. This is the name of the share used for auto-update of quotes. [2048]
    std::string fullname;     ///< Full name of the commodity.
    std::string cusip;        ///< Not used by investmentManager
    std::int32_t fraction;    ///< The fraction used with the commodity
    std::int32_t quoteFlag;   ///< Flag - used for determining if automatic quotes should be used???
    std::string quoteSource;  ///< Not used by investmentManager
    std::string quoteTz;      ///< Not used by investmentManager

    template<class Action>
    void persist(Action & a)
    {
      Wt::Dbo::id(a, guid, "guid", 32);
      Wt::Dbo::field(a, namespc, "namespace");
      Wt::Dbo::field(a, mnemonic, "mnemonic");
      Wt::Dbo::field(a, fullname, "fullname");
    }

  };  // class tbl_commoditites

  std::optional<std::string> commodityGUID(Wt::Dbo::Session &, std::string const &);

} // namespace database

#endif // TBL_COMMODITIES_H
