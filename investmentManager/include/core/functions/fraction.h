//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                /core/fraction.h
// SUBSYSTEM:           Fraction functions
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           core
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
// HISTORY:             2020-05-26/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef FRACTION_H
#define FRACTION_H

  // Standard C++ library header files

#include <cstdint>
#include <utility>

  // Miscellaneous library header files

#include <MCL>

namespace core
{
  MCL::fraction_t composeFraction(double, std::uint_least8_t = 4);
}

#endif // FRACTION_H
