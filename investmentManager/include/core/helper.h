//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                /core/helper.h
// SUBSYSTEM:           Helper functions
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:
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
// HISTORY:             2020-05-27/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef HELPER_H
#define HELPER_H

  // Standard C++ library header files

#include <ctime>

  // Miscellaneous library header files.

#include <SCL>

namespace SCL
{
  template<>
  inline std::string any::Manager_external<std::tm>::S_toString(any const *anyp)
  {
    auto ptr = static_cast<std::tm const *>(anyp->dataStorage.heapPointer);
    return std::string();
  }
}

#endif // HELPER_H
