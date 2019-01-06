#ifndef GORN_MOD_INSTALLER_MODSMAINWINDOW_H
#define GORN_MOD_INSTALLER_MODSMAINWINDOW_H

#include <QtCore/QArgument>
#include <QtWidgets/QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <src/utils/ModApi.h>
#include "src/utils/Fetcher.h"

class ModsSelection : public QWidget {
Q_OBJECT
public:
    explicit ModsSelection();
private:
    ModApi m_api;
    QListWidget* m_installed_list_widget;
    QListWidget* m_available_list_widget;
    QPushButton* m_install_button;
};

#endif //GORN_MOD_INSTALLER_MODSMAINWINDOW_H
