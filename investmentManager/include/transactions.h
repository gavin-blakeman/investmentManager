//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                transactions.h
// SUBSYSTEM:           Constants and definitions for transactions.
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

#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <cstdint>

typedef std::int32_t transaction_t;

namespace TC
{
  transaction_t const AD000   = 1000;
  transaction_t const AD100   = 1100;
  transaction_t const AD110   = 1110;
  transaction_t const AD120   = 1120;
  transaction_t const AD130   = 1130;

  transaction_t const IM000   = 3000;
  transaction_t const IM100   = 3100;
  transaction_t const IM200   = 3200;
  transaction_t const IM300   = 3300;
  transaction_t const IM400   = 3400;
  transaction_t const IM500   = 3500;
  transaction_t const IM510   = 3510;
  transaction_t const IM520   = 3520;

  transaction_t const MS000   = 20000;
  transaction_t const MS001   = 20100;
  transaction_t const MS900   = 20900;
  transaction_t const MS901   = 20910;

  transaction_t const RS000   = 30000;
  transaction_t const RS100   = 30100;
  transaction_t const RS200   = 30200;

  transaction_t const MT000   = 40000;
  transaction_t const MT100   = 40100;
  transaction_t const MT900   = 40900;

  transaction_t const MD000   = 5000;
  transaction_t const MD100   =   5100;
  transaction_t const MD110   =     5110;
  transaction_t const MD120   =     5120;
  transaction_t const MD200   = 5200;

  transaction_t const SM000   = 60000;

  transaction_t const UD000   =   70100;
  transaction_t const CD001   =   70200;
  transaction_t const PH000   =   70300;
  transaction_t const PH100   =     70310;
  transaction_t const PH200   =     70320;
  transaction_t const PH300   =     70330;
  transaction_t const PH400   =     70340;
  transaction_t const BD000   =   70400;
  transaction_t const BD001   =     70410;
  transaction_t const BD002   =     70420;
  transaction_t const AS000   =   70500;
  transaction_t const AS001   =     70510;
  transaction_t const AS002   =     70520;
  transaction_t const AS003   =     70530;
  transaction_t const AS004   =     70540;
  transaction_t const OT000   =   70600;
  transaction_t const OT010   =     70610;
}

#endif // TRANSACTIONS_H
