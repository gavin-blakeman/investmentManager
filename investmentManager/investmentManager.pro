#-----------------------------------------------------------------------------------------------------------------------------------
#
# PROJECT:            Investment Manager
# FILE:								investmentManager.pro
# SUBSYSTEM:          Project File
# LANGUAGE:						C++
# TARGET OS:          LINUX
# LIBRARY DEPENDANCE:	None.
# NAMESPACE:          N/A
# AUTHOR:							Gavin Blakeman.
# LICENSE:            GPLv2
#
#                     Copyright 2020 Gavin Blakeman.
#                     This file is part of the investmentManager Project
#
#                     investmentManager is free software: you can redistribute it and/or modify it under the terms of the GNU
#                     General Public License as published by the Free Software Foundation, either version 2 of the License, or (at
#                     your option) any later version.
#
#                     investmentManager is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
#                     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
#                     License for more details.
#
#                     You should have received a copy of the GNU General Public License along with investmentManager.  If not, see
#                     <http://www.gnu.org/licenses/>.
#
# OVERVIEW:						Project file for compiling the project
#
# HISTORY:            2020-04-19/GGB - Start Project
#
#-----------------------------------------------------------------------------------------------------------------------------------

TARGET = investmentManager.wt
TEMPLATE = app

QT += core
QT -= gui

CONFIG += console
CONFIG -= app_bundle
CONFIG += object_parallel_to_source

QMAKE_CXXFLAGS += -std=c++17 -static -static-libgcc -DWT_CPP17_ANY_IMPLEMENTATION=std
DEFINES += BOOST_THREAD_USE_LIB QT_GUI_LIB QT_CORE_LIB

#OBJECTS_DIR = "objects"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=  \
    "../GCL" \
    "../MCL" \
    "/home/gavin/Documents/Projects/software/Library/Boost/boost_1_71_0" \
    "../SCL"

SOURCES += \
    source/application.cpp \
    source/database/session.cpp \
    source/models/menuModel.cpp \
    source/permissionSystem.cpp \
    source/views/menuView.cpp \
    source/database/tbl_users.cpp \
    source/configSettings.cpp \
    source/investmentManager.cpp \
    source/transactionPages/investorContributions.cpp \
    source/transactionPages/priceManager.cpp \
    source/database/tbl_prices.cpp \
    source/core/priceUpload/yahooPrices.cpp \
    source/models/pricesModel.cpp

HEADERS += \
    include/application.h \
    include/database/database \
    include/database/databaseDefinitions.h \
    include/database/databaseTables.h \
    include/database/session.h \
    include/transactions.h \
    include/database/tbl_users.h \
    include/transactionPages/transactionPage.h \
    include/models/menuModel.h \
    include/mainMenu.h \
    include/permissionSystem.h \
    include/views/menuView.h \
    include/configSettings.h \
    include/database/tbl_transactions.h \
    include/transactionPages/investorContributions.h \
    include/database/tbl_applicationData.h \
    include/database/tbl_accounts.h \
    include/transactionPages/priceManager.h \
    include/database/tbl_commodities.h \
    include/database/tbl_prices.h \
    include/core/priceUpload/yahooPrices.h \
    include/models/pricesModel.h

LIBS += -L/usr/lib -lwt -lwthttp -lwtdbo -lwtdbomysql
LIBS += -L/usr/local/lib -lboost_system
LIBS += -L/usr/local/lib -lboost_filesystem
LIBS += -L/usr/local/lib -lboost_thread
LIBS += -L/usr/local/lib -lboost_program_options
LIBS += -L../GCL -lGCL

DISTFILES += \
    menu.md \
    developerNotes.md

