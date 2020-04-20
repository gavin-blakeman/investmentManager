//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                permissionSystem.cpp
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

#include "../include/permissionSystem.h"

/// @brief Returns the transaction permissions for the user and transaction.
/// @param[in] userID: The userID to check the permissions for.
/// @param[in] transactionID: The transaction ID to check the permissions for.
/// @returns A record containing the user permissions for the transaction.
/// @throws
/// @version 2020-04-19/GGB - Function created.

void CUserData::transactionPermissions(std::uint32_t userID, transaction_t transactionID,
                                       SRecordPermissions &transactionPermissions) const
{
  transactionPermissions.viewRecords(true).createRecords(true).deleteRecords(true).modifyRecords(true);
}
