//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                /core/fraction.cpp
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

#include "include/core/functions/fraction.h"

  // Standard C++ library header files

#include <cmath>
#include <limits>

  // Miscellaneous library header files

#include <GCL>


namespace fraction
{
  /// @brief composes a fraction from the value that is passed.
  /// @param[in] value: The value to convert to a fraction.
  /// @param[in] decimalDigits: The minimum number of digits after the decimal point to preserve. (Maximum value = 10)
  /// @returns std::pair<numerator, denominator>
  /// @throws GCL::runtime_assert
  /// @version 2020-05-26/GGB - Function created.

  MCL::fraction_t composeFraction(double value, std::uint_least8_t decimalDigits)
  {
    RUNTIME_ASSERT(std::abs(value) <= std::numeric_limits<std::int64_t>::max(), "value >= maximum value stored in fraction");
    RUNTIME_ASSERT(decimalDigits <= 10, "Use decimal digits <= 10");

    std::int64_t n, d;

    n = static_cast<std::int64_t>(std::trunc(value));
    value = std::abs(value);
    value -= std::abs(n);
    value *= 10 ^ decimalDigits;
    d = static_cast<std::int64_t>(std::trunc(value));

    return MCL::fraction_t(n, d);
  }
}
