#ifndef GORN_MOD_INSTALLER_MODSMAINWINDOW_H
#define GORN_MOD_INSTALLER_MODSMAINWINDOW_H

#include <QtCore/QArgument>
#include <QtWidgets/QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include "src/utils/ModManager.h"

class ModsSelection : public QWidget {
    Q_OBJECT
    ModManager* m_mod_manager;
    QListWidget* m_installed_list_widget;
    QListWidget* m_available_list_widget;
    QPushButton* m_install_button;
    void showEvent(QShowEvent *event) override;
public:
    explicit ModsSelection();
private:

};

#endif //GORN_MOD_INSTALLER_MODSMAINWINDOW_H
