//**********************************************************************************************************************************
//
// PROJECT:             Investment Manager
// FILE:                dialogs/priceUpload.h
// SUBSYSTEM:           Upload Commodity/Share Prices
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
// HISTORY:             2020-04-25/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef DIALOG_PRICEUPLOAD_H
#define DIALOG_PRICEUPLOAD_H

  // Standard C++ library header files

#include <cstdint>
#include <memory>
#include <vector>

  // Wt C++ framework header files.

#include <Wt/WComboBox.h>
#include <Wt/WDialog.h>
#include <Wt/WFileDropWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>
#include <Wt/Dbo/Session.h>

  // investmentManager Header files.

#include "include/application.h"
#include "include/permissionSystem.h"
#include "include/database/databaseTables.h"

namespace dialogs
{
  class CPriceUpload : public Wt::WDialog
  {
  private:
    Wt::Dbo::Session &session;
    Wt::WWidget *parent_ = nullptr;

    Wt::WFileDropWidget *fileDropWidget = nullptr;

    Wt::WPushButton *pushButtonCancel = nullptr;
    Wt::WPushButton *pushButtonUpload = nullptr;

    CPriceUpload() = delete;
    CPriceUpload(CPriceUpload const &) = delete;
    CPriceUpload(CPriceUpload &&) = delete;
    CPriceUpload &operator=(CPriceUpload const &) = delete;

    void dialogFinished(Wt::DialogCode);

    void fileDropWidgetDrop(std::vector<Wt::WFileDropWidget::File *> );
    void fileDropWidgetTooLarge(Wt::WFileDropWidget::File *, std::uint64_t);
    void fileDropWidgetUploaded(Wt::WFileDropWidget::File *);
    void fileDropWidgetUploadFailed(Wt::WFileDropWidget::File *file);


  public:
    CPriceUpload(Wt::Dbo::Session &, Wt::WWidget *);

    void createUI();


  };

} // namespace dialogs

#endif // DIALOG_PRICEUPLOAD_H
