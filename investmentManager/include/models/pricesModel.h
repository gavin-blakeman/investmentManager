//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                pricesModel
// SUBSYSTEM:           Model for displaying prices.
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
// HISTORY:             2020-04-25/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef PRICESMODEL_H
#define PRICESMODEL_H

  // Standard C++ library header files

#include <map>
#include <optional>
#include <string>

  // Wt++ framework header files

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/Types.h>
#include <Wt/WAbstractTableModel.h>
#include <Wt/WGlobal.h>
#include <Wt/WDate.h>

  // investmentManager header files

#include <include/database/database>
#include "include/database/session.h"

namespace models
{
  class CPricesModel: public Wt::WAbstractTableModel
  {
  private:
    using SRecord = std::tuple<Wt::WDate, std::string, std::string, std::int64_t, std::int64_t>;

    Wt::Dbo::Session &session;
    std::string commodityGUID;
    mutable std::map<std::uint64_t, SRecord> recordCache; ///< Use a map as it can be sparse rather than full.
    mutable std::uint64_t cacheStartIndex;
    std::uint64_t cacheMaximumSize = 16384;       ///< Limit to around 10MB of data.
    std::uint64_t cacheReadRecords = 1024;        ///< Number of records to read at a time.
    std::uint64_t recordCount;                    ///< Number of records in the current recordSet.

    CPricesModel(CPricesModel const &) = delete;
    CPricesModel(CPricesModel &&) = delete;
    CPricesModel &operator =(CPricesModel const &) = delete;

    void readRecords(std::uint64_t) const;

  public:
    CPricesModel(Wt::Dbo::Session &);

    void changeCommodity(std::string const &);

    void clear();

    virtual int columnCount(Wt::WModelIndex const & = Wt::WModelIndex()) const { return 4;}
    virtual int rowCount(Wt::WModelIndex const &parent = Wt::WModelIndex()) const;

    virtual std::any data(Wt::WModelIndex const &index, Wt::ItemDataRole role = Wt::ItemDataRole::Display) const override;
    virtual std::any headerData(int, Wt::Orientation, Wt::ItemDataRole) const override;
  };
}

#endif // PRICESMODEL_H
