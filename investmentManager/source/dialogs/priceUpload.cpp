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

#include "include/dialogs/priceUpload.h"

  // Standard C++ library header files.

#include <stdexcept>
#include <string>

  // Wt C++ framework header files.

#include <Wt/WButtonGroup.h>
#include <Wt/WDateEdit.h>
#include <Wt/WEnvironment.h>
#include <Wt/WGridLayout.h>
#include <Wt/WLabel.h>
#include <Wt/WPushButton.h>
#include <Wt/WRadioButton.h>
#include <Wt/WSpinBox.h>
#include <Wt/WStackedWidget.h>

  // Miscellaneous library header files

#include <boost/lexical_cast.hpp>
#include <GCL>

  // investmentManager Header files.

#include <include/database/database>
#include "include/configSettings.h"
#include "include/core/priceUpload/priceUploadManager.h"

namespace dialogs
{

  /// @brief Class constructor.
  /// @param[in] s: The session for the database access.
  /// @param[in] parent: Pointer to the parent object.
  /// @throws std::runtime_error
  /// @throws std::bad_alloc
  /// @version 2020-04-25/GGB - Function created.

  CPriceUpload::CPriceUpload(Wt::Dbo::Session &s, Wt::WWidget *parent) : WDialog(""), session(s), parent_(parent)
  {
    setWindowTitle("Upload Commmodity Prices");

    createUI();
  }

  /// @brief Function called when the dialog is accepted.
  /// @param[in] dialogCode: The value for the dialog code.
  /// @version 2020-04-25/GGB - Function created.

  void CPriceUpload::dialogFinished(Wt::DialogCode dialogCode)
  {
    if (dialogCode == Wt::DialogCode::Accepted)
    {
      std::vector<Wt::WFileDropWidget::File*> uploads = fileDropWidget->uploads();

      for (auto file: uploads)
      {
        boost::filesystem::path filename = file->uploadedFile().clientFileName();
        boost::filesystem::path fn = filename.stem();

        database::tbl_prices::priceUpload(session, filename.string(), file->uploadedFile().spoolFileName());
      };
    };

    removeFromParent();
  }

  /// @brief Creates the UI for the dialog.
  /// @throws
  /// @version 2020-04-25/GGB - Function created.

  void CPriceUpload::createUI()
  {
    Wt::WGridLayout *gridLayout = contents()->setLayout(std::make_unique<Wt::WGridLayout>());

    fileDropWidget = gridLayout->addWidget(std::make_unique<Wt::WFileDropWidget>(), 0, 0);

    fileDropWidget->drop().connect(this, &CPriceUpload::fileDropWidgetDrop);
    fileDropWidget->uploaded().connect(this, &CPriceUpload::fileDropWidgetUploaded);
    fileDropWidget->tooLarge().connect(this, &CPriceUpload::fileDropWidgetTooLarge);
    fileDropWidget->uploadFailed().connect(this, &CPriceUpload::fileDropWidgetUploadFailed);

    contents()->resize(800, Wt::WLength::Auto);

    rejectWhenEscapePressed(true);

    pushButtonUpload = footer()->addNew<Wt::WPushButton>("Upload Files");
    pushButtonUpload->setDefault(true);
    pushButtonUpload->setEnabled(false);
    pushButtonUpload->clicked().connect(this, &Wt::WDialog::accept);      // Accept the dialog

    pushButtonCancel = footer()->addNew<Wt::WPushButton>("Cancel");
    pushButtonCancel->clicked().connect(this, &Wt::WDialog::reject);  // Reject the dialog

    finished().connect(this, &CPriceUpload::dialogFinished);

    show();
  }

  /// @brief Processes the message when a file(s) is dropped in the drop area.
  /// @param[in] files: Vector of the files being dropped.
  /// @throws
  /// @version 2020-04-25/GGB - Function created.

  void CPriceUpload::fileDropWidgetDrop(std::vector<Wt::WFileDropWidget::File *> files)
  {
    std::optional<std::uint16_t> const maxFiles = configurationReader.tagValueUInt16(PRICES_MAXFILESUPLOAD);
    std::uint16_t fileCount = fileDropWidget->uploads().size() - files.size();

    for (std::uint_fast16_t index = 0; index < files.size(); ++index)
    {
      if (fileCount + index >= *maxFiles)
      {
        fileDropWidget->cancelUpload(files[index]);
      }
      else
      {
        Wt::WLabel *block = fileDropWidget->addWidget(std::make_unique<Wt::WLabel>(files[index]->clientFileName()));
        block->setWidth(600);

        block->addStyleClass("upload-block spinner");
      };
    };

    if (fileDropWidget->uploads().size() >= maxFiles)
    {
      fileDropWidget->setAcceptDrops(false);
    };
  }

  /// @brief Processes the message when the file is too large to upload.
  /// @param[in] file: Pointer to the file that is too large.
  /// @param[in] size: The size of the file that is too large.
  /// @throws
  /// @version 2020-04-25/GGB - Function created.

  void CPriceUpload::fileDropWidgetTooLarge(Wt::WFileDropWidget::File *file, std::uint64_t size)
  {
    std::vector<Wt::WFileDropWidget::File*> uploads = fileDropWidget->uploads();

    for (std::uint_fast16_t index = 0; index < uploads.size(); ++index)
    {
      if (uploads[index] == file)
      {
        fileDropWidget->widget(index)->removeStyleClass("spinner");
        fileDropWidget->widget(index)->addStyleClass("failed");
        index = uploads.size();
      };
    };
  }

  /// @brief Processes the message when the file has been uploaded.
  /// @param[in] file: Pointer to the File structure that contains the information.
  /// @throws
  /// @version 2020-04-26/GGB - Function created.

  void CPriceUpload::fileDropWidgetUploaded(Wt::WFileDropWidget::File *file)
  {
    std::vector<Wt::WFileDropWidget::File*> uploads = fileDropWidget->uploads();
    bool fileValid = false;

      // Check if the file is a valid file.

    fileValid = core::priceUpload::CPriceUploadManager::validateFile(file->uploadedFile().spoolFileName());

    for (std::uint_fast16_t index = 0; index < uploads.size(); ++index)
    {
      if (uploads[index] == file)
      {
        if (fileValid)
        {
          fileDropWidget->widget(index)->removeStyleClass("spinner");
          fileDropWidget->widget(index)->addStyleClass("ready");

          pushButtonUpload->setEnabled(true);
        }
        else
        {
          fileDropWidget->widget(index)->removeStyleClass("spinner");
          fileDropWidget->widget(index)->addStyleClass("invalid");
        };
        index = uploads.size();
      };
    };


  }

  void CPriceUpload::fileDropWidgetUploadFailed(Wt::WFileDropWidget::File *file)
  {
    std::vector<Wt::WFileDropWidget::File*> uploads = fileDropWidget->uploads();

    std::size_t idx = 0;
    for (; idx != uploads.size(); ++idx)
    {
      if (uploads[idx] == file)
      {
          break;
      }
    };

    fileDropWidget->widget(idx)->removeStyleClass("spinner");
    fileDropWidget->widget(idx)->addStyleClass("invalid");
  }

} // namespace dialogs
