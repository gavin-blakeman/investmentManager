//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                models/commodityTransactions.h
// SUBSYSTEM:           Model to manage the commodity transactions.
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           models
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

#ifndef MODEL_COMMODITYTRANSACTIONS_H
#define MODEL_COMMODITYTRANSACTIONS_H
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

  /* The commodity transaction table has columns for:
   *    Date
   *    Transaction type (Buy, Sell, Divident, Split, Merge)
   *    Number of shares (+ or -)
   *    Share Price
   *    Transaction Costs
   *    Cumulative Shares (calculation)
   *    Capital Loss    (If shares have not been sold "---")
   *    STCG            (If shares have not been sold "---")
   *    LTCG            (If shares have not been sold "---")
   *    Taxable         (If shares have not been sold "---")
   *
   *  Also calculate
   *    The current position using the last price.
   *    The current gain/loss
   *    The current MIRR/XIRR
   *
   * To enable this to work correctly, all the share transactions are required to be loaded and processed every time. It may be
   * possible to add an archive flag, IE when a transaction is completed (sold) and does not need to be used, the flag can be
   * set and then the record avoided unless specifically requested.
   */

  class CComodityTransactions: public Wt::WAbstractTableModel
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

    CComodityTransactions() = delete;
    CComodityTransactions(CComodityTransactions const &) = delete;
    CComodityTransactions(CComodityTransactions &&) = delete;
    CComodityTransactions &operator =(CComodityTransactions const &) = delete;

    void readRecords(std::uint64_t) const;

  public:
    CComodityTransactions(Wt::Dbo::Session &);

    void changeCommodity(std::string const &);

    void clear();

    virtual int columnCount(Wt::WModelIndex const & = Wt::WModelIndex()) const { return 4;}
    virtual int rowCount(Wt::WModelIndex const &parent = Wt::WModelIndex()) const;

    virtual std::any data(Wt::WModelIndex const &index, Wt::ItemDataRole role = Wt::ItemDataRole::Display) const override;
    virtual std::any headerData(int, Wt::Orientation, Wt::ItemDataRole) const override;
  };
}

#endif // MODEL_COMMODITYTRANSACTIONS_H
