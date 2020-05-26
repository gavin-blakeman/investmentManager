//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                permissionSystem.h
// SUBSYSTEM:           Base class definition for transactions pages
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

#ifndef USERDATA_H
#define USERDATA_H

  // Standard C++ library

#include <cstdint>
#include <unordered_map>
#include <vector>

  // ReliabilityManager header files

#include "menuConstants.h"

typedef std::uint8_t role_t;


struct SRecordPermissions
{
private:
protected:
public:
  std::uint8_t viewRecord   : 1;    /*!< Allows viewing of the data within records. */
  std::uint8_t addRecord    : 1;    /*!< Allows adding new records. This does not automatically allow modification of existing records. */
  std::uint8_t deleteRecord : 1;    /*!< Allows deleting of existing records. */
  std::uint8_t modifyRecord : 1;    /*!< Allows modification of existing records. */

  SRecordPermissions &viewRecords(bool v = true) { viewRecord = v; return *this; }
  SRecordPermissions &createRecords(bool v = true) { addRecord = v; return *this; }
  SRecordPermissions &deleteRecords(bool v) { deleteRecord = v; return *this; }
  SRecordPermissions &modifyRecords(bool v) { modifyRecord = v; return *this; }

  bool viewRecords() const { return viewRecord; }
  bool createRecords() const { return addRecord; }
  bool deleteRecords() const { return deleteRecord; }
  bool modifyRecords() const { return modifyRecord; }
};


class CUserData
{
private:
  std::int32_t userID_;
  std::vector<role_t> userRoles_;
  std::unordered_map<transaction_t, SRecordPermissions> userTransactions_;

  CUserData(CUserData const &) = delete;
  CUserData & operator= (CUserData const &) = delete;

protected:
public:
  CUserData() {}

  std::vector<role_t> const &roles() const { return userRoles_;}
  void transactionPermissions(std::uint32_t, transaction_t, SRecordPermissions &) const;


};

#endif // USERDATA_H
