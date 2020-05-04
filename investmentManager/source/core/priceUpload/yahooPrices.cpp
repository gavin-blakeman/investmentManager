//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                /core/priceUpload/yahooPrices.h
// SUBSYSTEM:           Classes to upload commodity prices from file.
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           core::priceUpload
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

#include "include/core/priceUpload/yahooPrices.h"

  // Standard C++ library header files

#include <ctime>
#include <exception>
#include <string>

  // Miscellaneous library header files

#include "boost/algorithm/string.hpp"
#include <boost/format.hpp>
#include "boost/lexical_cast.hpp"
#include "boost/filesystem/fstream.hpp"
#include <GCL>

namespace core
{
  namespace priceUpload
  {
    bool CYahooPriceUpload::pluginRegistered =
        CPriceUploadManager::registerPlugin(std::make_tuple(&CYahooPriceUpload::nameFunction,
                                                            &CYahooPriceUpload::validateFunction,
                                                            &CYahooPriceUpload::uploadFileFunction));

    /// @brief Validates a file as a Yahoo prices file.
    /// @param[in] filename: The name of the file to validate.
    /// @returns true - The file is a Yahoo prices file.
    /// @throws
    /// @version 2020-04-26/GGB - Function created.

    bool CYahooPriceUpload::validateFunction(boost::filesystem::path const &filename)
    {
        // The first line of a Yahoo .csv price file has the strings
        // 'Date,Open,High,Low,Close,Adj Close,Volume'
        // Approach is to just check the first line for this string. If it exists, then no issue.

      bool returnValue = false;
      boost::filesystem::ifstream ifs;    // Input file stream.


      if (!boost::filesystem::exists(filename))
      {
        throw std::runtime_error("File not found.");
      }
      else
      {
        ifs.open(filename);

          // Just read the first line.

        std::string szLine;

        std::getline(ifs, szLine);
        boost::trim(szLine);

        if (szLine == "Date,Open,High,Low,Close,Adj Close,Volume")    // Crude - I know.
        {
          returnValue = true;
          INFOMESSAGE(boost::str(boost::format("File %s validated as Yahoo prices file.") % filename));
        };

        ifs.close();
      };

      return returnValue;
    }

    /// @brief Loads the data from the file into a vector of dates and prices.
    /// @param[in] filename: The file to upload.
    /// @returns An optional indicating success with a std::vector.
    /// @throws
    /// @version 2020-04-26/GGB - Function created.

    CPriceUploadManager::parseFunctionReturn_t CYahooPriceUpload::uploadFileFunction(boost::filesystem::path const &filename)
    {
      CPriceUploadManager::pricesVector_t returnVector;
      std::optional<CPriceUploadManager::pricesVector_t> returnValue;
      boost::filesystem::ifstream ifs;  // The input file stream.


      if (!boost::filesystem::exists(filename))
      {
        throw std::runtime_error("File not found.");
      }
      else
      {
        std::string szLine;
        std::uint64_t lineCount = 0;

        ifs.open(filename);

          // Load and discard header.

        std::getline(ifs, szLine);
        lineCount++;

        while (!ifs.eof())
        {
          std::string szClose, szDate, szTemp;
          std::size_t indexStart = 0, indexEnd = 0;

          std::getline(ifs, szLine);
          lineCount++;

          if (!szLine.empty())
          {
              // Decompose the line into the relevant values.
              // Line is in the format "date, open, high, low, close, adj close, volume"
              // We only need date and close.

              // Date

            indexEnd = szLine.find(",", indexStart);
            szDate = szLine.substr(indexStart, indexEnd - indexStart);
            indexStart = indexEnd + 1;

              // open

            indexEnd = szLine.find(",", indexStart);
            indexStart = indexEnd + 1;

              // high

            indexEnd = szLine.find(",", indexStart);
            indexStart = indexEnd + 1;

              // low

            indexEnd = szLine.find(",", indexStart);
            indexStart = indexEnd + 1;

              // close

            indexEnd = szLine.find(",", indexStart);
            szClose = szLine.substr(indexStart, indexEnd - indexStart);

              // Now parse the strings and create the commodity entry.

            try
            {
              std::tm date;
              double value;

              boost::trim(szDate);
              boost::trim(szClose);

                // Date should be in form yyyy-mm-dd.

              indexStart = 0;
              indexEnd = szDate.find("-", indexStart);
              szTemp = szDate.substr(indexStart, indexEnd - indexStart);
              date.tm_year = boost::lexical_cast<std::uint16_t>(szTemp);

              indexStart = indexEnd + 1;
              indexEnd = szDate.find("-", indexStart);
              szTemp = szDate.substr(indexStart, indexEnd - indexStart);
              date.tm_mon = boost::lexical_cast<std::uint16_t>(szTemp);

              indexStart = indexEnd + 1;
              indexEnd = szDate.size();
              szTemp = szDate.substr(indexStart, indexEnd - indexStart);
              date.tm_mday = boost::lexical_cast<std::uint16_t>(szTemp);

              value = boost::lexical_cast<double>(szClose);

              returnVector.emplace_back(std::make_pair(date, value));
            }
            catch(...)
            {
              WARNINGMESSAGE(boost::str(boost::format("Error in line %li. Continuing...") % lineCount));
            };
          };
        };  // while statement

        ifs.close();

        returnValue = std::move(returnVector);
      }

      return returnValue;
    }


  } // namespace priceUpload
} // namespace core
