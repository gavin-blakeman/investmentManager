//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                tbl_prices.cpp
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

#include "include/database/tbl_prices.h"

  // Miscellaneous library header files

#include <GCL>

  // investmentManager header files

#include "include/core/helper.h"
#include "include/core/priceUpload/priceUploadManager.h"

#include "include/database/tbl_commodities.h"

namespace database
{
  namespace tbl_prices
  {
    /* The accounts table has the following default layout;
   *  > guid - varchar(32)
   *  > commodity_guid - varchar(32)
   *  > currency_guid - varchar(32)
   *  > date - timestamp
   *  > source - varchar(2048
   *  > type - varchar(2048)
   *  > value_num - std::int64_t
   *  > value_denom - std::int64_t
   */

    /// @brief Gets the last price for the specified commodity.
    /// @param[in] sesssion: The dbo session to use.
    /// @param[in] commodityGUID: The GUID of the commodity.
    /// @param[in] closingDate: The date to get the price for.
    /// @throws
    /// @version 2020-05-30/GGB - Function created.

    std::optional<money_t> closingPrice(Wt::Dbo::Session &session, std::string const &commodityGUID, std::tm const &closingDate)
    {
      RUNTIME_ASSERT(commodityGUID.size() == 32, "commodityGUID must be 32 characters in size.");

      std::optional<money_t> returnValue;

      GCL::sqlWriter sqlWriter;

      sqlWriter
          .select({"date", "value_num", "value_denom"})
          .from("accounts")
          .where("date", "<=", closingDate)
          .orderBy({{"date", GCL::sqlWriter::DESC}})
          .limit(1);

      try
      {
        Wt::Dbo::Transaction transaction(session);

        std::tuple<double, double> price = session.query<std::tuple<double, double>>(sqlWriter.string());

        returnValue = std::get<0>(price) / std::get<1>(price);
      }
      catch(Wt::Dbo::Exception &e)
      {
        ERRORMESSAGE(e.what());
      };

      return returnValue;
    }

    /// @brief Uploads prices from the specified file. The file parameters are passed to the function.
    /// @param[in] session: The database session to use.
    /// @param[in] commodityCode: The code for the commodity to upload.
    /// @param[in] uploadFilename: The path to the upload location.
    /// @throws
    /// @returns
    /// @version 2020-05-02/GGB - Function created.

    void priceUpload(Wt::Dbo::Session &session, std::string const &commodityCode, boost::filesystem::path const &uploadFilename)
    {
      core::priceUpload::CPriceUploadManager::parseFunctionReturn_t parsedFile;

      parsedFile = core::priceUpload::CPriceUploadManager::parseFile(uploadFilename);

      if (parsedFile)
      {
        // The parsedFile variable nows has a number of values stored. This can now be uploaded to the relevant commodity.

        std::optional<std::string> GUID = commodityGUID(session, commodityCode);
        GCL::sqlWriter sqlWriter;

        sqlWriter.insertInto("prices");

      };
    }

  } // namespace tbl_prices
} // namespace database
