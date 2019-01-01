#ifndef GORN_MOD_INSTALLER_MODSMAINWINDOW_H
#define GORN_MOD_INSTALLER_MODSMAINWINDOW_H

#include <QtCore/QArgument>
#include <QtWidgets/QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

class ModsMainWindow : public QWidget {
    Q_OBJECT
public:
    explicit ModsMainWindow();

private:
    QListWidget *m_installed_list_widget;
    QListWidget *m_available_list_widget;
    QPushButton* m_install_button;
    QNetworkAccessManager* m_network_manager;
    QMap<QNetworkReply *, QJsonObject> * m_download_map;
};

#endif //GORN_MOD_INSTALLER_MODSMAINWINDOW_H
