//
// Created by leogout on 1/6/2019.
//

#ifndef GORN_MOD_INSTALLER_MAINWINDOW_H
#define GORN_MOD_INSTALLER_MAINWINDOW_H

#include <QtCore/QArgument>
#include <QtWidgets/QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QPushButton>
#include <src/utils/ModManager.h>
#include "src/view/ModsSelection.h"
#include "src/view/PlatformSelection.h"
#include "ModsSelection.h"
// @todo reorganize public vs private
class MainWindow : public QWidget {
Q_OBJECT
    QStackedWidget* m_stacked_widget;
    PlatformSelection* m_platform_selection;
    ModsSelection* m_mods_selection;
    void onPlatformSelected();
public:
    explicit MainWindow(); 
};

#endif //GORN_MOD_INSTALLER_MAINWINDOW_H
