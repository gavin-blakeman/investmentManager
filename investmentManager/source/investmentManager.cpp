//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                investmentManager.cpp
// SUBSYSTEM:           Main Application File
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
// OVERVIEW:						Sub-system for managing the application
//
// HISTORY:             2020-04-19/GGB - File created.
//
//**********************************************************************************************************************************

  // Standard C++ libary header files

#include <exception>
#include <memory>
#include <string>

  // Wt++ library header files

#include <Wt/WServer.h>
#include <Wt/Dbo/FixedSqlConnectionPool.h>
#include <Wt/Dbo/SqlConnectionPool.h>
#include <Wt/Dbo/backend/MySQL.h>

  // Miscellaneous library header files

#include <boost/algorithm/string.hpp>
#include <GCL>

  // investmentManager header files.

#include "include/application.h"
#include "include/configSettings.h"
#include "include/database/session.h"

/// @brief Creates a connection pool for further use. Has 10 connections in the connection pool.
/// @details The configuration required to connect to the database is loaded from the configuration file. See the documentation
///          in configSettings.h.
/// @throws std::runtime_error on incorrect parameters.
/// @throws Wt::Dbo::exception on connection failure.
/// @version 2020-04-19/GGB - Function created.

std::unique_ptr<Wt::Dbo::SqlConnectionPool> createConnectionPool()
{
  std::string hostAddress = configurationSettings->value(DATABASE_HOSTADDRESS).toString().toStdString();
  std::uint16_t portAddress = configurationSettings->value(DATABASE_PORT).toUInt();
  std::string databaseName = configurationSettings->value(DATABASE_DATABASENAME).toString().toStdString();
  std::string userName = configurationSettings->value(DATABASE_USERNAME).toString().toStdString();
  std::string password = configurationSettings->value(DATABASE_PASSWORD).toString().toStdString();

    // Sense check all the configuration settings and exit if problematic.

  if (hostAddress.empty() || databaseName.empty() || userName.empty() || password.empty())
  {
    throw std::runtime_error("Incorrect database configuration details in configuration file.");
  };

  auto connection = std::make_unique<Wt::Dbo::backend::MySQL>(databaseName,
                                                              userName,
                                                              password,
                                                              hostAddress,
                                                              portAddress);
  connection->setProperty("show-queries", "true");
  return std::make_unique<Wt::Dbo::FixedSqlConnectionPool>(std::move(connection), 10);
}


/// @brief main() function for the application.
/// @param[in] argc: The number of arguments on the command line.
/// @param[in] argv: The arguments on the command line.
/// @details The connection pool is created, and then the server/run() function is called. A number of exceptions are caught to
///          allow error reporting to occur.
/// @returns 0 - No error
/// @returns !0 - Error has occurred.
/// @version 2020-04-19/GGB - Function created.

int main(int argc, char **argv)
{
    // Setup the logger

  GCL::logger::CSeverity logSeverity;
  std::string logLevel = configurationSettings->value(APPLICATION_LOGLEVEL, QVariant("NORMAL")).toString().toStdString();
  boost::to_upper(logLevel);

  if (logLevel == "NORMAL")
  {
    logSeverity.fCritical = true;
    logSeverity.fError = true;
    logSeverity.fWarning = true;
    logSeverity.fNotice = false;
    logSeverity.fInfo = false;
    logSeverity.fDebug = false;
    logSeverity.fTrace = false;
  }
  else if (logLevel == "VERBOSE")
  {
    logSeverity.fCritical = true;
    logSeverity.fError = true;
    logSeverity.fWarning = true;
    logSeverity.fNotice = true;
    logSeverity.fInfo = true;
    logSeverity.fDebug = false;
    logSeverity.fTrace = false;
  }
  else if (logLevel == "DEBUG")
  {
    logSeverity.fCritical = true;
    logSeverity.fError = true;
    logSeverity.fWarning = true;
    logSeverity.fNotice = true;
    logSeverity.fInfo = true;
    logSeverity.fDebug = true;
    logSeverity.fTrace = false;
  }
  else if (logLevel == "TRACE")
  {
    logSeverity.fCritical = true;
    logSeverity.fError = true;
    logSeverity.fWarning = true;
    logSeverity.fNotice = true;
    logSeverity.fInfo = true;
    logSeverity.fDebug = true;
    logSeverity.fTrace = true;
  };

  std::string logFile = configurationSettings->value(APPLICATION_LOGFILE, QVariant(QString(""))).toString().toStdString();

  if (!boost::filesystem::is_directory(logFile))
  {
    logFile = "";
  };

  GCL::logger::PLoggerSink fileLogger(new GCL::logger::CFileSink(logFile, "investmentManager"));
  std::dynamic_pointer_cast<GCL::logger::CFileSink>(fileLogger)->setRotationPolicyUse(10);
  fileLogger->setLogLevel(logSeverity);

  try
  {
    std::dynamic_pointer_cast<GCL::logger::CFileSink>(fileLogger)->openLogFile();
  }
  catch(...)
  {
    std::clog << "Error while creating logfile. Does the directory exist?" << std::endl;
  };

  GCL::logger::defaultLogger().addSink(fileLogger);

  logSeverity.fTrace = false;
  GCL::logger::PLoggerSink coutLogger(new GCL::logger::CStreamSink(std::cout));
  coutLogger->setLogLevel(logSeverity);
  GCL::logger::defaultLogger().addSink(coutLogger);

  try
  {
    Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);
    std::unique_ptr<Wt::Dbo::SqlConnectionPool> connectionPool = createConnectionPool();

    server.addEntryPoint(Wt::EntryPointType::Application, std::bind(&createApplication, std::placeholders::_1,
                                                                    connectionPool.get()),
                         "", "css/wt/favicon.ico");
    database::CSession::configureAuthorisation();

    server.run();
  }
  catch (Wt::WServer::Exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch (Wt::Dbo::Exception &e)
  {
    std::cerr << "Dbo exception: " << e.what() << std::endl;
  }
  catch (std::exception &e)
  {
    std::cerr << "exception: " << e.what() << std::endl;
  }
}
