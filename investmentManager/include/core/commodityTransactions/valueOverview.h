//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                core/commodityTransactions/valueOverview.h
// SUBSYSTEM:           Create a value overview (all transactions) for a commodity.
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
// HISTORY:             2020-11-11/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef VALUEOVERVIEW_H
#define VALUEOVERVIEW_H

  // Standard C++ library header files

#include <cstdint>
#include <string>
#include <tuple>
#include <vector>

  // Wt++ framework header files

  // Miscellaneous library header files

#include <ACL>

  // investmentManager header files

#include "include/config.h"


namespace core::commodityTransactions
{

  class CValueOverview
  {
  private:
    struct STransaction
    {
      ACL::TJD date;
      std::uint8_t transactionType;
      shareCount_t shareCount;
      accountingValue_t sharePrice;
      accountingValue_t totalShareValue;
      accountingValue_t transactionCosts;
      shareCount_t cumulativeShares;
      accountingValue_t capitalLoss;
      accountingValue_t STCG;
      accountingValue_t LTCG;
      accountingValue_t taxableValue;
    };

    using transactions = std::vector<STransaction>;


    CValueOverview() = delete;
    CValueOverview(CValueOverview const &) = delete;
    CValueOverview(CValueOverview &&) = delete;

  public:
    CValueOverview(std::string const &);
  };

}

#endif // VALUEOVERVIEW_H
