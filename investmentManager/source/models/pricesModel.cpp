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

#include "include/models/pricesModel.h"

  // Standard C++ library header files

#include <tuple>
#include <utility>

  // Wt++ framework header files

#include <Wt/Dbo/Transaction.h>

  // Miscellaneous library header files

#include <GCL>

namespace models
{
  /// @brief Class constructor. Ensure all variables are initialised correctly.
  /// @throws std::bad_alloc
  /// @version 2020-04-25/GGB - Function created.

  CPricesModel::CPricesModel(Wt::Dbo::Session &sqlSession)
    : Wt::WAbstractTableModel(), session(sqlSession), commodityGUID(), recordCache(), cacheStartIndex(0)
  {
  }

  /// @brief Function called to change the commodity selected by the model.
  /// @param[in] guid: The UUID of the commodity to fetch.
  /// @note 1. A check is made if the UUID is actually changing. If not, the data is not updated.
  /// @throws
  /// @version 2020-04-25/GGB - Function created.

  void CPricesModel::changeCommodity(std::string const &guid)
  {
    if (guid != commodityGUID)
    {
        // GUID is different. Flush existing data and notify the table.

      cacheStartIndex = 0;
      recordCache.clear();
      commodityGUID = guid;
      recordCount = 0;

        // Now load the number of records.

      {
        std::string szSQL = "SELECT COUNT(*) FROM prices WHERE commodity_guid = '" + commodityGUID + "'";

        Wt::Dbo::Transaction transaction { session };

        Wt::Dbo::collection<std::int64_t> recordCountCollection;

        recordCountCollection = session.query<std::int64_t>(szSQL);

        recordCount = static_cast<std::uint64_t>(recordCountCollection.front());

        std::cout << "Record Count: " << recordCount << std::endl;
      };

        // Load the first batch of records up to the maximum number of records per transaction

      readRecords(1);

      reset();
    };
  }

  /// @brief Clears all the data from the model and resets. Memory is not specifically recovered.
  /// @throws None.
  /// @version 2020-04-25/GGB - Function created.

  void CPricesModel::clear()
  {
    commodityGUID.clear();
    cacheStartIndex = 0;
    recordCache.clear();
    recordCount = 0;
  }

  /// @brief Function to fetch data from the model.
  /// @param[in] index:
  /// @param[in] role:
  /// @throws std::runtime_error
  /// @throws std::out_of_range
  /// @version 2020-04-25/GGB - Function created.

  std::any CPricesModel::data(Wt::WModelIndex const &index, Wt::ItemDataRole role) const
  {
    SRecord const *record;
    std::any returnValue;

    switch (role.value())
    {
      case Wt::ItemDataRole::Display:
      {
        try
        {
          record = &recordCache.at(index.row());  // If the record is not in the cache, then this throws.
        }
        catch(std::out_of_range &o)
        {
            // Record not in cache. Load it.

          readRecords(index.row());
          record = &recordCache.at(index.row());  // If the record is not in the cache, then this throws.
        };

          // Note the case below is needed as get<> needs a constexpr.

        switch(index.column())
        {
          case 0:
          {
            returnValue = std::get<0>(*record);
            break;
          };
          case 1:
          {
            returnValue = std::get<1>(*record);
            break;
          };
          case 2:
          {
            returnValue = std::get<2>(*record);
            break;
          };
          case 3:
          {
            double numerator = static_cast<double>(std::get<3>(*record));
            double denominator = static_cast<double>(std::get<4>(*record));
            returnValue = numerator / denominator;
            break;
          };
          default:
          {
            throw std::runtime_error("Invalid column number");
            break;
          }
        }

        break;
      }
    }

    return returnValue;
  }

  /// @brief Reads records from the database into the cache. The data read will be sufficient to include the rowNeeded.
  /// @param[in] rowNeeded: The row that data is needed from. The read process will ensure that this data is read.
  /// @throws
  /// @version 2020-04-25/GGB - Function created.

  void CPricesModel::readRecords(std::uint64_t rowNeeded) const
  {
      // Check if we actually need to read the record.

    if (rowNeeded >= (cacheStartIndex + recordCache.size()))
    {

        // As we want to read in fixed sized 'blocks' of records, lets determine the block to read.
        // Note their are built in bugs here as we assume that we cannot have more than 2^64 records.
        // This is fairly reasonable in 2020, but may not be true in the future.

      std::uint64_t blockStart = (rowNeeded / cacheReadRecords) * cacheReadRecords;
      std::uint64_t blockEnd = blockStart + cacheReadRecords;

      if (blockEnd > (cacheStartIndex + cacheMaximumSize))
      {
          // Need to rebase the cache and discard unneeded data.
      };

        // Read the data

      {
        GCL::sqlwriter::CSQLWriter sqlWriter;

        sqlWriter.
            select({ "prices.date",
                     "prices.source",
                     "prices.type",
                     "prices.value_num",
                     "prices.value_denom"
                   })
            .from("prices")
            .where("prices.commodity_guid", "=", commodityGUID)
            .orderBy({std::make_pair("prices.date", GCL::sqlwriter::ASC)})
            .offset(blockStart)
            .limit(cacheReadRecords);

        Wt::Dbo::Transaction transaction { session };

        Wt::Dbo::collection<std::tuple<Wt::WDate, std::string, std::string, std::int64_t, std::int64_t>> pricesCollection;

        pricesCollection = session.query<std::tuple<Wt::WDate, std::string, std::string, std::int64_t, std::int64_t>>(sqlWriter.string());

        for (auto price: pricesCollection)
        {
          recordCache.insert_or_assign(blockStart++, std::move(price));
        };

      }
    };
  }

  std::any CPricesModel::headerData(int section, Wt::Orientation orientation, Wt::ItemDataRole role) const
  {
    std::any returnValue;

    switch(role.value())
    {
      case Wt::ItemDataRole::Display:
      {
        switch (section)
        {
          case 0:
          {
            returnValue = "Date";
            break;
          };
          case 1:
          {
            returnValue = "Source";
            break;
          };
          case 2:
          {
            returnValue = "Type";
            break;
          };
          case 3:
          {
            returnValue = "Value";
            break;
          };
        };
        break;
      };
    };

    return returnValue;

  }

  /// Returns the number of records in the recordSet.
  /// @returns The number of records to display.
  /// @throws None.
  /// @version 2020-04-25/GGB - Function created.

  int CPricesModel::rowCount(Wt::WModelIndex const &parent) const
  {
    return recordCount;
  }

} // namespace models
