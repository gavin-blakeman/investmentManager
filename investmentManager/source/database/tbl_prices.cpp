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

#include "include/core/priceUpload/priceUploadManager.h"
#include "include/database/tbl_commodities.h"

namespace database
{
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



    }
  }

} // namespace database
