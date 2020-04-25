//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                investorContributions.h
// SUBSYSTEM:           Investor/Member Review of own contributions
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
// HISTORY:             2020-04-22/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef INVESTORCONTRIBUTIONS_H
#define INVESTORCONTRIBUTIONS_H

#include "transactionPage.h"

namespace transactions
{

  class CInvestorContributions : CTransactionPage
  {
  private:

    CInvestorContributions() = delete;
    CInvestorContributions(CInvestorContributions const &) = delete;
    CInvestorContributions(CInvestorContributions const &&) = delete;

  public:
    CInvestorContributions(CApplication *parent) : CTransactionPage(parent) {}
  };

} // namespace transactions

#endif // INVESTORCONTRIBUTIONS_H
