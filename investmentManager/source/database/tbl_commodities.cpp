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
// HISTORY:             2020-05-02/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/database/tbl_commodities.h"

  // Miscellaneous library header files.

#include <GCL>

namespace database
{
  /// @brief Finds the GUID for the specified commodity. The specified commodity can be a share (stock) or a currency.
  /// @param[in] mnemonic: The mnemonic of the share to find.
  /// @returns A std::optional<std::string> containing the commodity GUID if found.
  /// @throws
  /// @version 2020-05-02/GGB - Function created.

  std::optional<std::string> commodityGUID(Wt::Dbo::Session &session, std::string const &mnemonic)
  {
    std::optional<std::string> returnValue;

    try
    {
      Wt::Dbo::Transaction transaction { session };

      GCL::sqlwriter::CSQLWriter sqlWriter;

      sqlWriter.select({"commodities.guid"}).from("commodities")
          .where({GCL::sqlwriter::parameterTriple("commodities.mnemonic", "=", mnemonic)});

      returnValue = session.query<std::string>(sqlWriter.string());

    }
    catch(Wt::Dbo::Exception &e)
    {
      ERRORMESSAGE(e.what());
    };

    return returnValue;
  }


} // namespace database
