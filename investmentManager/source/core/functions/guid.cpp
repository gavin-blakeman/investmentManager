//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                /core/guid.hpp
// SUBSYSTEM:           GUID related functions.
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
// HISTORY:             2020-05-25/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/core/functions/guid.h"

  // Standard C++ library header files

#include <cstdint>

  // Miscellaneous library header files

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <GCL>

namespace core
{
  /// @brief Convert single digit hexadecimal value to a hex character.
  /// @param[in] i: Value to convert.
  /// @returns The corresponding character value.
  /// @throws GCL::runtimeAssert
  /// @version 2020-05-08/GGB - Function created.

  inline char toChar(std::uint_least8_t i)
  {
    RUNTIME_ASSERT(i < 16, "Parameter must be < 16.");

    char returnValue;

    if (i <= 9)
    {
      returnValue = static_cast<char>('0' + i);
    }
    else
    {
      returnValue = static_cast<char>('a' + (i-10));
    };

    return returnValue;
  }

  /// @brief Function to generate a GUID in the correct format for gnuCash.
  /// @returns A std::string containing a 32 characted GUID.
  /// @throws GCL::runtimeAssert.
  /// @version 2020-05-08/GGB - Function created.

  std::string generateGUID()
  {
    std::string returnValue;
    static boost::uuids::random_generator randomGenerator;

    boost::uuids::uuid UUID = randomGenerator();

    returnValue.reserve(32);

    std::size_t i=0;
    for (boost::uuids::uuid::const_iterator it_data = UUID.begin(); it_data!=UUID.end(); ++it_data, ++i)
    {
      const size_t hi = ((*it_data) >> 4) & 0x0F;
      returnValue += toChar(hi);

      const size_t lo = (*it_data) & 0x0F;
      returnValue += toChar(lo);
    };

    return returnValue;
  }

} // namespace core
