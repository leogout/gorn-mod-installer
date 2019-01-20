#ifndef GORN_MOD_INSTALLER_MODSMAINWINDOW_H
#define GORN_MOD_INSTALLER_MODSMAINWINDOW_H

#include <QtCore/QArgument>
#include <QtWidgets/QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QLabel>
#include "src/utils/ModManager.h"

class ModsSelection : public QWidget {
    Q_OBJECT
    ModManager* m_mod_manager;
    QListWidget* m_installed_list_widget;
    QProgressBar* m_install_progress;
    QLabel* m_install_label;
    QListWidget* m_available_list_widget;
    QPushButton* m_remove_button;
    QPushButton* m_install_button;
    void showEvent(QShowEvent *event) override;
    void disableButtons();
    void enableButtons();
    void onListAvailable(QStringList list);
    void onListInstalled(QStringList list);
    void onRemoved();
    void onInstalled();
    void onProgress(QString file, int percentage);
    void onRemovePressed();
    void onInstallPressed();
public:
    explicit ModsSelection(ModManager* mod_manager);
private:

};

#endif //GORN_MOD_INSTALLER_MODSMAINWINDOW_H
